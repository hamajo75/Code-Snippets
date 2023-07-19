#!/bin/bash

# enable job control
set -m

# run in the background
ls &
# see all background processes
echo jobs: $(jobs)

# bring it back (%n for multiple processes)
fg
# move to background again
  # Ctrl + z puts current process to sleep
# bg

# run multiple commands in background
{ sleep 1; echo finished; } &

my_fun() {
  sleeper=$1
  sleep 5;
  echo the $sleeper has awoken
}

my_fun a &
pid_a=$!

echo starting next
my_fun b
pid_b=$!

wait $pid_a $pid_b

echo FIN
