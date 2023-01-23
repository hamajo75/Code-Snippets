#!/bin/bash

# arrays
MY_ARRAY=("a" "b")
echo ${#MY_ARRAY[@]}  # get nr. of entries

for entry in ${MY_ARRAY[@]}; do echo "${entry}"; done
for E in ${MY_ARRAY[@]}; do LINE+="${E}"; done
echo ${LINE}

# not in sh
MY_ARRAY=(entry1 entry2 entry3)
echo Print entries in MY_ARRAY: ${MY_ARRAY[@]}
if [[ ! "${MY_ARRAY[*]}" =~ "entry4" ]]; then
  echo "Entry not found." >&2
  exit 1
fi