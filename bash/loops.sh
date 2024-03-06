#!/bin/bash

# while [[ -e wait.txt ]] ; do
#   sleep 3 # "sleep" for three seconds
# done
# echo

for i in {1..3} ; do
  echo "$i"
done

echo 

iterations=3
for i in $(seq 1 ${iterations}); do  # this also works in sh
  echo "$i"
done

echo

# while true; do
#    # do something

#    # -n 1 to get one character at a time, -t 0.1 to set a timeout
#    read -n 1 -t 0.1 input                  # so read doesn't hang
#    if [[ $input = "q" ]]
#    then
#       echo # to get a newline after quitting
#       break
#    fi
# done

cmd="scp -i ~/.ssh/mee066/mee066-ssh-developer-key"
arg_proxy="-o ProxyJump=intercom-wifi"

source=/home/jha/Development/Viza/mee066-esw-camera-daemon/camera_daemon
destination=root@192.168.201.2:/usr/lib/python3.8/site-packages/camera_daemon

subfolders=(workplace onvif amqp_messaging)
files=(workplace_control.py discovery.py intercom_handler.py)

# loop over array elements ${ files[@] }  [@] ... all elements
for file in "${files[@]}"; do
  echo $file
done

echo 

# loop over indices: ${!files[@]}
for index in "${!files[@]}"; do
  echo $cmd $arg_proxy \
    $source/${subfolders[index]}/${files[index]} \
    $destination/${subfolders[index]}
done
