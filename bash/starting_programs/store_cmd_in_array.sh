#!/bin/bash

# store a cmd call in variable
cmd="ls"
cmd="$cmd -la"
eval "$cmd"

# store cmd in an array
cmd=(ls -la)
"${cmd[@]}"
