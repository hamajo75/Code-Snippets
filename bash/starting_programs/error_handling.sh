#!/bin/bash -e

# check for parameter
# comparie set -u
[[ -z $1 ]] && { echo "param missing" 1>&2; exit 1; }  # execute in same shell, redirect to stderr

# trap on error
do_del() {
  echo do_del
}

cleanup_on_error() {
  echo "cleaning up on error"
  do_del
  echo "exit 1"
  exit 1
}

set -o errexit -o errtrace  # same as: `set -eE`
trap cleanup_on_error ERR

do_add() {
  echo "do_add"
  echo "error"
  false
  echo "we don't get here"
}

# Thanks to -E / -o errtrace, this still triggers the trap,
# even though the failure occurs *inside the function*.
do_add

echo "this code is not executed on error"

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
