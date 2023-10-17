#!/bin/bash -e

# the space " " before "]" is necessary !
if [ "$?" -ne 0 ]; then
   echo "command failed"
   exit 1
else
   echo "USB Drives connected"
fi
# The variable $ (echo $?)
# 0 is supposed to mean success, everything else is an error.

# run kill 0 to kill all background (child) processes in case one of the signals
# SIGINT SIGTERM SIGERR SIGEXIT
trap cleanup_on_error INT TERM ERR
trap "cleanup_on_exit" EXIT

cleanup_on_exit() {
  echo "cleaning up on exit..."
}

cleanup_on_error() {
  echo "cleaning up on error..."
}

#false  # trigger the error trap

# exit on error (if any commands fail)
set -e
set +e          # ignore errors (continue)
