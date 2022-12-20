#!/bin/sh

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
[[ -z $1 ]] && { echo "param missing" 1>&2; exit 1; }  # execute in same shell, redirect to stderr