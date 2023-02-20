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

# alternative
help() {
  echo -e \
    "Usage: slave_control_daemon.sh [start|stop|restart|startd|restartd]\n" \
    "\n" \
    "    start | restart: Start interactively\n" \
    "  startd | restartd: Start non-interactively\n" \
    "               stop: Stop slave-control-damon\n"
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

# # alternative: getopt - parse positional parmeters
# # c: argument expected: "-c command"
# while getopts ":rc:a:" o; do
#   case "${o}" in
#     r) # restart
#       restart=1
#       echo "restart"
#       ;;
#     c) # cmd
#       cmd=${OPTARG}
#       echo "cmd"
#       ;;
#     a) # ip addr
#       ip_address=${OPTARG}
#       echo "ip_address"
#       ;;
#     * | ? | :)
#       echo usage
#       exit 0
#       ;;
#   esac
# done
# if [ $OPTIND -eq 1 ]; then echo "usage"; fi
# shift $((OPTIND-1))
