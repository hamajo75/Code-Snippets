#!/bin/bash

# default value
: ${UTILS_PATH:=.}
# Note: the ":" in front allows you to write UTILS_PATH=${UTILS_PATH:=.} shorter.
#. $UTILS_PATH/utils.sh

#config_file=not_default_value
#config_file=${config_file:=default_value}
#config_file=${UTILS_PATH:-default_value}      # if UTILS_PATH is null it still is after this line

# config_file=prefix_${1:-default_value}_postfix
# echo $config_file

echo "${var}"
echo "Substitute the value of var."

echo "${var:-word}"
echo "If var is null or unset, word is substituted for var. The value of var does not change."

echo "${var:=word}"
echo "If var is null or unset, var is set to the value of word."

echo "${var:?message}"
echo "If var is null or unset, message is printed to standard error. This checks that variables are set correctly."

echo "${var:+word}"
echo "If var is set, word is substituted for var. The value of var does not change."
# param=${1:+--wplc-data-file=config/$1.json}
# echo ${param}
