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

# check for parameter
# comparie set -u
[[ -z $1 ]] && { echo "param missing" 1>&2; exit 1; }  # execute in same shell, redirect to stderr

# trap on error
do_del() {
  echo do_del
  set +o errexit +o errtrace
  echo "error"
  false
  echo "getting here"
}

cleanup_on_error() {
  echo "cleaning up on error"
  do_del
  exit 1
}

set -eE  # same as: `set -o errexit -o errtrace`
trap cleanup_on_error ERR

function do_add() {
  # return 0
  # return 1
  echo "do_add"
  echo "error"
  false
  echo "continue"
}

# Thanks to -E / -o errtrace, this still triggers the trap,
# even though the failure occurs *inside the function*.
do_add

echo "this code is not executed on error"
