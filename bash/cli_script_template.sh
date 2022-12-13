#!/bin/bash

#/ Some help text.
#/
#/ Usage:
#/   General patterns
#/
#/ Example:
#/   Concrete examples
#/

show_help() {
  grep "^#/" $0 | cut -c 4-
  exit 0
}

cmd=$1
shift 1

case $cmd in
  param1)
    handle_param1 $@ ;;
  param2)
    handle_param2 $@ ;;
  param3)
    handle_param3 $@ ;;
  *)
    show_help ;;
esac