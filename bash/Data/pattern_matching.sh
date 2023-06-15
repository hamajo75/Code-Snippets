#!/bin/bash

# the matching thing is removed

# from left to right: #
# ## last or longest match
# #  first or shortest match

test="20.16.86.189:13002"

echo ${test##*:}  # jadlfj
echo ${test#*:}   # dlfjaöbajadlfj

# from right to left: %
echo ${test%%:*}  # ajdflj
echo ${test%:*}   # ajdfljbadlfjaö
