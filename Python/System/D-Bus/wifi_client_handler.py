#!/usr/bin/env python3

import dbus
import dbus.mainloop.glib
from gi.repository import GLib
import subprocess
import time
from dataclasses import dataclass
import logging
import sys
import argparse
import signal


# D-Bus Interfaces for wpa_supplicant: https://w1.fi/wpa_supplicant/devel/dbus.html
WPA_SUPPLICANT = "fi.w1.wpa_supplicant1"
WPA_SUPPLICANT_OBJECT_PATH = "/fi/w1/wpa_supplicant1"
WPA_SUPPLICANT_BSS = "fi.w1.wpa_supplicant1.BSS"
WPA_SUPPLICANT_INTERFACE = "fi.w1.wpa_supplicant1.Interface"
DBUS_PROPERTIES = "org.freedesktop.DBus.Properties"

WPA_SUPPLICANT_CONFIG_FILE = "/data/etc/wpa_supplicant_sta.conf"
HOSTAPD_CONFIG_FILE = "/data/etc/hostapd.conf"
last_channel_nr = 3


logging.basicConfig()
log = logging.getLogger("wifi_client_handler")
log.setLevel(logging.INFO)


@dataclass
class ExecutionResult:
    code: int
    stdout: str
    stderr: str


def run_cmd(cmd: str) -> ExecutionResult:
    process_completed = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    code = process_completed.returncode
    stdout = process_completed.stdout.strip()
    stderr = process_completed.stderr.strip()
    return ExecutionResult(code, stdout, stderr)


def get_channel_nr() -> int:
    bus = dbus.SystemBus()
    proxy = bus.get_object(WPA_SUPPLICANT, WPA_SUPPLICANT_OBJECT_PATH)
    wpas_interface = dbus.Interface(proxy, WPA_SUPPLICANT)
    path = wpas_interface.GetInterface("wlan0")
    wifi_if_proxy = bus.get_object(WPA_SUPPLICANT, path)
    properties_if = dbus.Interface(wifi_if_proxy, DBUS_PROPERTIES)
    bss_paths = properties_if.Get(WPA_SUPPLICANT_INTERFACE, "BSSs")

    for bss_path in bss_paths:
        bss_proxy = bus.get_object(WPA_SUPPLICANT, bss_path)
        bss_properties = dbus.Interface(bss_proxy, DBUS_PROPERTIES)
        properties = bss_properties.GetAll(WPA_SUPPLICANT_BSS)

        frequency = properties.get("Frequency", 0)
        return frequency_to_channel_2_4ghz(frequency), frequency
    return None, None


def frequency_to_channel_2_4ghz(freq):
    if 2412 <= freq <= 2484:  # 2.4 GHz band
        return (freq - 2407) // 5
    return None


def properties_changed(properties):
    if "State" in properties:
        log.debug("State changed: %s" % (properties["State"]))

        if (properties["State"] == "disconnected"):
            log.debug("Disconnected from the network. Trying to reconnect...")
            connect()
        if (properties["State"] == "inactive"):
            log.debug("Inactive state. Trying to connect...")
            connect()


def scan_done(success):
    global last_channel_nr
    log.debug("Scan done: success=%s" % success)
    try:
        new_channel_nr, frequency = get_channel_nr()
    except Exception:
        return

    if last_channel_nr == new_channel_nr:
        return

    if frequency is not None:
        log.info(f"Scan done: Switching to channel {new_channel_nr}, frequency {frequency}")
        result = run_cmd(f"hostapd_cli chan_switch 1 {frequency} bandwidth=20 center_freq1={frequency}")
        if "FAIL" in result.stdout:
            log.error(f"Cannot switch channel. {result.stdout} {result.stderr}")
        else:
            last_channel_nr = new_channel_nr


def disconnect():
    log.info("Disconnecting from AP.")
    run_cmd("wpa_cli -i wlan0 disconnect")


def connect():
    log.info("Connecting to AP.")
    result = run_cmd("wpa_cli -i wlan0 reconfigure")
    if result.code != 0:
        log.error("Cannot connect to AP.")

    result = run_cmd("wpa_cli enable_network 0")
    if result.code != 0:
        log.error("Cannot connect to AP.")


def wait_for_wpa_supplicant():
    log.info("Waiting for wpa_supplicant...")
    while True:
        result = run_cmd("wpa_cli status")
        if result.code == 0:
            log.info("wpa_supplicant is running.")
            break
        else:
            time.sleep(1)


def init_dbus():
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    bus = dbus.SystemBus()

    bus.add_signal_receiver(
        properties_changed,
        signal_name="PropertiesChanged",
        dbus_interface=WPA_SUPPLICANT_INTERFACE,
    )
    bus.add_signal_receiver(
        scan_done,
        dbus_interface=WPA_SUPPLICANT_INTERFACE,
        signal_name="ScanDone"
    )


def parse_arguments():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description="""Handle Wifi Client connection to Mobile Router.
    1. On start tries to connect to the Wifi AP defined in
       the wpa_supplicant config file.
    2. Listens for D-Bus events (mainly \"scan_done\") from wpa_supplicant
       and switches the hostapd channel to the currently used channel.""")

    parser.add_argument("-d", "--debug-log", action="store_true", help="Enable Debug logging.")
    return parser.parse_args()


def handle_signal(sig, _frame):
    if sig in (signal.SIGINT, signal.SIGTERM):
        log.info(f"Received signal {signal.Signals(sig).name}. Exiting.")
        disconnect()
        sys.exit(0)


def listen_for_wpa_supplicant_events():
    log.info("Listening for events from wpa_supplicant...")
    GLib.MainLoop().run()


def main():
    signal.signal(signal.SIGINT, handle_signal)
    signal.signal(signal.SIGTERM, handle_signal)

    args = parse_arguments()
    if args.debug_log:
        log.setLevel(logging.DEBUG)

    wait_for_wpa_supplicant()
    init_dbus()
    connect()   # will automatically trigger a scan
    listen_for_wpa_supplicant_events()


if __name__ == "__main__":
    main()