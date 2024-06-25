#!/usr/bin/python3
import dbus

bus = dbus.SystemBus()

# See https://people.freedesktop.org/~lkundrak/nm-docs/spec.html

# A server provides a service via OBJECTS. 
# A proxy object "stands for" a remote object in the server.
# A function called on the proxy will actually be called on the remote object.
proxy_eth0 = bus.get_object('org.freedesktop.NetworkManager',
                       '/org/freedesktop/NetworkManager/Devices/eth0')

# getProperties is a standard interface method. 
properties = proxy_eth0.getProperties(dbus_interface='org.freedesktop.NetworkManager.Device')

# You can also create an Interface object. 
eth0_dev_iface = dbus.Interface(proxy_eth0,
    dbus_interface='org.freedesktop.NetworkManager.Devices')
properties = eth0_dev_iface.getProperties()

print(properties)