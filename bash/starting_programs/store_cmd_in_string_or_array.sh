#!/bin/bash

# store a cmd call in variable
cmd="echo -e"
cmd="$cmd Hello World\nnext line"
#eval "$cmd"
# no eval necessary:
$cmd | grep World

# Notes:
# Word splitting happens after variable expansion and command substitution.
# Here's the order of operations:
# 1. Brace expansion (i.e. {a,b} becomes a b)
# 2. Tilde expansion (i.e. ~user becomes the home directory of user)
# 3. Parameter and variable expansion (i.e. $var or ${var})
# 4. Command substitution (i.e. $(command) or `command`
# 5. Word splitting (spaces, tabs, and newlines)
# 6. Pathname expansion

# here you need eval (is eval evil?)
cmd="echo -e 'Hello World\nnext line' | grep World"
eval "$cmd"


# store cmd in an array
cmd=(ls -la)
"${cmd[@]}"
