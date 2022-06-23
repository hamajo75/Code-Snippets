#!/bin/bash

while [[ -e wait.txt ]] ; do
  sleep 3 # "sleep" for three seconds
done

for i in {1..3} ; do
  echo "$i"
done

iterations=3
for i in $(seq 1 ${iterations}); do  # this also works in sh
  echo "$i"
done

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
