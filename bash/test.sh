#!/bin/sh

# "[" is a symbolic link to a program called "test".
# that's why you need a space after "[ ".

# -z STRING is empty
test -z "aaa"  # is equivalent to
[ -z "aaa" ]
echo $?