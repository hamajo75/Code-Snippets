#!/bin/bash

# call: ../sourcing.sh and see what happens

# dirname: get path
echo "`dirname /path/file.txt`"

THIS_DIR=$(dirname $0)          # directory of THIS file relative to the current directory, e.g. ./bash
echo '$0: ' $0                  # ./bash/directories.sh
echo THIS_DIR: $THIS_DIR

# BASH_SOURCE vs. $0
# - BASH_SOURCE is bash specifig, $0 is POSIX
# - BASH_SOURCE might be useful when sourcing other scripts
# a.sh -> source b.sh -> source c.sh ($0 will be a.sh also in the other files)
DIR="$(readlink -f $(dirname ${BASH_SOURCE}))"
echo '${BASH_SOURCE} ' ${BASH_SOURCE}
echo '${DIR} ' ${DIR}           # absolute path of THIS script (also when the script is sourced)