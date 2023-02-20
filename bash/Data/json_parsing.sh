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