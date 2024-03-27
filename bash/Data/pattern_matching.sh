#!/bin/bash

# the matching thing is removed

# from left to right: #
# ## last or longest match
# #  first or shortest match

test="bla:20.16.86.189:13002:hello"

# from left to right
echo ${test##*:}  # 13002
echo ${test#*:}   # 20.16.86.189:13002

# from right to left: %
echo ${test%%:*}  # bla
echo ${test%:*}   # bla:20.16.86.189
