#!/bin/bash

# the matching thing is removed

# from left to right: #
# ## last or longest match
# #  first or shortest match

test="ajdfljbadlfjaöbajadlfj"

echo ${test##*ba}  # jadlfj
echo ${test#*ba}   # dlfjaöbajadlfj

# from right to left: %
echo ${test%%ba*}  # ajdflj
echo ${test%ba*}   # ajdfljbadlfjaö