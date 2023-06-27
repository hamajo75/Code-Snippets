#!/bin/bash

# apt install jq
# try online https://jqplay.org/

# Filter data
## get value of a key
jq .quiz.sport json_parsing_test.json

## get array entry
jq .quiz.sport.q1.options[1] json_parsing_test.json
jq .quiz.sport.q1.options[1:4] json_parsing_test.json  # not including #4

## | pipe output of filter n to filter n+1

# Create json files
rm -f file.json > /dev/null 2>&1
jq -n --arg ts "2023-06-16T06:38:32.000Z" '{"startedAt":$ts}' > file.json

# Add to existing file
add_key_to_json_file() {
  key=$1
  value=$2
  file=$3
  echo "$(jq --arg key "$key" --arg value "$value" '. += {($key): $value}' $file)" > $file
}

key=links
value=LINK1
file=file.json
add_key_to_json_file $key $value $file
add_key_to_json_file new_key value $file
