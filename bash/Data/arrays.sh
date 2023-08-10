#!/bin/bash

# arrays
MY_ARRAY=("a" "b")
echo nr of entries: ${#MY_ARRAY[@]}

# overwrite
MY_ARRAY[0]="c"
MY_ARRAY[1]="d"

for entry in "${MY_ARRAY[@]}"; do echo "${entry}"; done
for E in "${MY_ARRAY[@]}"; do LINE+="${E}"; done
echo "${LINE}"

print_elements() {
  local array=("$@")
  echo Print entries in array: "${array[@]}"
  if [[ ! "${array[*]}" =~ "entry4" ]]; then
    echo "Entry not found." >&2
  fi
}

# not in sh
MY_ARRAY=(entry1 entry2 entry3)
print_elements "${MY_ARRAY[@]}"

# convert string to array
arr=("one" "two" "three")
echo "${arr[0]}"