#!/bin/sh



# Load and run shUnit2.
: ${SHUNIT2_PATH:-.}
. $SHUNIT2_PATH/shunit2


# run specific test
# test-script.sh -- testOne testTwo otherFunction