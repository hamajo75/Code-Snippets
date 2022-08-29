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