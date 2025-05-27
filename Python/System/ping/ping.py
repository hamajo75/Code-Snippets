#!/usr/bin/env python3

# from ping3 import ping

# response = ping('8.8.8.8')
# if response:
#     print(f"Ping successful, RTT = {response*1000:.2f} ms")
# else:
#     print("Ping failed")

from pythonping import ping

ping('127.0.0.1', verbose=True)