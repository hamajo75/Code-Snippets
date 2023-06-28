#!/bin/bash

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

set -o errexit -o errtrace  # same as: `set -eE`
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
