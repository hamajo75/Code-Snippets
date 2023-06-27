#!/bin/bash

foo() {
  while [ "$1" != "" ]; do
      echo $1
    shift
  done
}

dollar_at () {
  echo Nr. of params: $#
  foo "$@"
}

dollar_star () {
  foo "$*"
}

echo "Using \$@"
dollar_at a b c          # pass params as individual function params

echo "Using \$*"
dollar_star a b c        # pass params as one single string

echo Script params: $@
shift 1                  # shift params 1 to the left
echo Script params shifted: $@

# fake return value
get_ssid() {
  echo "MySSID"
}

# handle optional params + extra (e.g. for debugging) params
set_ssid() {
  local ssid1=${1:-"$(get_ssid)"}
  local ssid2=${2:-"$(get_ssid)"}
  shift $(($# < 2 ? $# : 2))

  echo ssid1: $ssid1 ssid2: $ssid2 rest: $@
}

set_ssid ssid1 ssid2 rest a b c