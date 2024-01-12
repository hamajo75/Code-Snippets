#!/bin/bash

# heredoc (here document) is used to redicert multiple lines of input into a command

file=test_file

cat >> $file << EOF
    ###
    [Network]
    Address=opnet_ip_address/24
    ###
EOF

#sed -i "/###/,/###/d" $file

# # Server IP address
# server_ip="192.168.1.1"

# # Start iperf in client mode, connect to the server, and run a few tests
# iperf << EOF
# c $server_ip
# t 10
# p 5001
# r
# EOF