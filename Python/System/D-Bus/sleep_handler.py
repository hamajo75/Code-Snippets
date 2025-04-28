import dbus
import dbus.mainloop.glib
from gi.repository import GLib

def handle_sleep_signal(sleeping):
    if sleeping:
        print("System is going to sleep...")
    else:
        print("System just woke up!")

def main():
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    bus = dbus.SystemBus()

    bus.add_signal_receiver(
        handle_sleep_signal,
        dbus_interface="org.freedesktop.login1.Manager",
        signal_name="PrepareForSleep"
    )

    loop = GLib.MainLoop()
    loop.run()

if __name__ == "__main__":
    main()
