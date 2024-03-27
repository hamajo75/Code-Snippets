#!/bin/bash

store_a_cmd_call_in_variable() {
  cmd="echo -e"
  cmd="$cmd Hello World\nnext line"
  #eval "$cmd"
  # no eval necessary:
  $cmd | grep World

  cmd="echo -e"
  cmd="$cmd 'Hello World\nnext line'"         # here you need '' for the linebreak
  output=$(eval "$cmd" | grep World)          # store output in a variable
  echo "$output"
}

store_parts_of_a_command_in_variables() {
  cmd="ls"
  args="-a"
  # execute like this
  $cmd $args
}

# Notes:
# Word splitting happens after variable expansion and command substitution.
# Here's the order of operations:
# 1. Brace expansion (i.e. {a,b} becomes a b)
# 2. Tilde expansion (i.e. ~user becomes the home directory of user)
# 3. Parameter and variable expansion (i.e. $var or ${var})
# 4. Command substitution (i.e. $(command) or `command`
# 5. Word splitting (spaces, tabs, and newlines)
# 6. Pathname expansion

using_eval() {
  # here you need eval (is eval evil?)
  cmd="echo -e 'Hello World\nnext line' | grep World"
  eval "$cmd"
}

store_command_and_params_in_array() {
  cmd=(ls -a)
  "${cmd[@]}"
}

store_a_cmd_call_in_variable
store_parts_of_a_command_in_variables
using_eval
store_command_and_params_in_array