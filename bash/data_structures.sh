#!/bin/bash

# arrays
MY_ARRAY=("a" "b")
echo ${#MY_ARRAY[@]}  # get nr. of entries

for entry in ${MY_ARRAY[@]}; do echo "${entry}"; done
for E in ${MY_ARRAY[@]}; do LINE+="${E}"; done
echo ${LINE}
