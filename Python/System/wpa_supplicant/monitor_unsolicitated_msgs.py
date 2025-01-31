#!/usr/bin/env python3

import os
import socket
from time import sleep

INTERFACE = "wlan0"  # Change this if using a different interface
WPA_SEND_PATH = f"/var/run/wpa_supplicant/{INTERFACE}"
WPA_RECEIVE_PATH = f"/tmp/wpa_ctrl_{os.getpid()}"  # Unique socket path for this client


def send_and_receive(outmsg, csock, ssock_filename):
    # the return socket object can be used to send the data
    # as long as the address is provided
    csock.sendto(str.encode(outmsg), ssock_filename)

    (bytes, address) = csock.recvfrom(4096)
    inmsg = bytes.decode('utf-8')

    return inmsg


def start_scan():
    if os.path.exists(WPA_RECEIVE_PATH):
        os.remove(WPA_RECEIVE_PATH)

    retsock = socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM)
    retsock.bind(WPA_RECEIVE_PATH)

    print("Starting scan...")
    replyToScan = send_and_receive('SCAN', retsock, WPA_SEND_PATH)
    print(f'SCAN: {replyToScan}')

    sleep(5)

    replyToScanResults = send_and_receive('SCAN_RESULTS', retsock, WPA_SEND_PATH)
    print(f'SCAN_RESULTS: {replyToScanResults}')

    retsock.close()
    os.remove(WPA_RECEIVE_PATH)


def listen_to_wpa_supplicant():
    sock = socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM)

    try:
        # Ensure no leftover socket file exists
        if os.path.exists(WPA_RECEIVE_PATH):
            os.remove(WPA_RECEIVE_PATH)

        # Bind to the client socket
        sock.bind(WPA_RECEIVE_PATH)

        # Connect to wpa_supplicant's control socket
        sock.connect(WPA_SEND_PATH)

        # Attach to receive unsolicited events
        sock.send(b"ATTACH")

        print("Listening for WPA supplicant events...")

        while True:
            data = sock.recv(4096).decode("utf-8").strip()
            if data:
                print(f"Event: {data}")

                if "CTRL-EVENT-BEACON-LOSS" in data:
                    print("Beacon loss detected! Handling event...")

    except KeyboardInterrupt:
        print("\nStopping listener...")

    finally:
        sock.send(b"DETACH")
        sock.close()
        os.remove(WPA_RECEIVE_PATH)


if __name__ == "__main__":
    # start_scan()
    listen_to_wpa_supplicant()
