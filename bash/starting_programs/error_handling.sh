#!/bin/bash

# the space " " before "]" is necessary !
if [ "$?" -ne 0 ]; then
   echo "command failed"
   exit 1
else
   echo "USB Drives connected"
fi
# The variable $ (echo $?)
# 0 is supposed to mean success, everything else is an error.

# run kill 0 to kill all background (chhild) processes in case one of the signals
# SIGINT SIGTERM SIGERR SIGEXIT
trap "exit" INT TERM ERR
trap "kill 0" EXIT

# exit on error (if any commands fail)
set -e
set +e          # ignore errors (continue)
