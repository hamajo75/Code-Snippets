#!/bin/bash

# arrays
MY_ARRAY=("a" "b")
echo nr of entries: ${#MY_ARRAY[@]}

# overwrite
MY_ARRAY[0]="c"
MY_ARRAY[1]="d"

for entry in ${MY_ARRAY[@]}; do echo "${entry}"; done
for E in ${MY_ARRAY[@]}; do LINE+="${E}"; done
echo ${LINE}

# not in sh
MY_ARRAY=(entry1 entry2 entry3)
echo Print entries in MY_ARRAY: ${MY_ARRAY[@]}
if [[ ! "${MY_ARRAY[*]}" =~ "entry4" ]]; then
  echo "Entry not found." >&2
fi

# bash > version 4
declare -A my_map
my_map["interface"]="interface_value"
my_map["port"]="port_value"

echo "${my_map["port"]}"