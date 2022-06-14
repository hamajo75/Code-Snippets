#!/bin/sh

# "[" is a symbolic link to a program called "test".
# that's why you need a space after "[ ".

# -z STRING is empty
test -z "aaa"  # is equivalent to
[ -z "aaa" ]
echo $?

# a shell if works like this
if
   command-list1
then
   command-list2
else
   command-list3
fi

# then-clause is executed when the command-list1 exit code is 0
# else-clause is executed when the command-list1 exit code is is non-0

# if [ condition ]     - test
# if [[ condition ]]   - test with extended features (not POSIX compatible)
# if ( command )       - command runs in a subshell and sets it's exit code
# if (( command ))     - arithmetic evaluation:  If the value of the expression is non-zero, the return status is 0; 
#                        otherwise the return status is 1. (not POSIX compatible)
