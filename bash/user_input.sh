#!/bin/sh

# read
# -n 1 to get one character at a time, -t 0.1 to set a timeout
read -rsn1 -t 0.1 input                  # so read doesn't hang
if [[ $input = "q" ]]
then
  echo # to get a newline after quitting
  break
fi