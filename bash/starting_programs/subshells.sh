#!/bin/bash

# subshells
var=shell
(
  var=subshell
  echo $var modified the variable, but only in the subshell
) # each cmd is started in a new shell with copy of environment
echo $var was not modified

# run command detached from this shell
nohup sleep 3