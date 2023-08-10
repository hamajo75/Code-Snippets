#!/bin/bash

# enable job control
set -m

# set cleanup trap
trap cleanup_on_stop SIGQUIT SIGINT SIGTERM

cleanup_on_stop() {
  echo stopped
  kill -SIGINT "$pid_a" "$pid_b"
  exit 0
}

# run in the background
ls &
# see all background processes
echo jobs: "$(jobs)"

# bring it back (%n for multiple processes)
fg
# move to background again
  # Ctrl + z puts current process to sleep
# bg

# run multiple commands in background
{ sleep 1; echo finished; } &

my_fun() {
  local v=$1
  for i in {1..3}
  do
    echo sleeping for $v
    sleep 10 &
    pid=$!
    echo started with pid: $pid
    # you need to be waiting in order to stop the background process
    # because it keeps running if this shell is already finished
    # wait $pid_a $pid_b
    wait $pid
  done
}

my_fun a &
echo pid $pid         # my_fun() is run in a sub shell that copies the context of the parent shell, so change made
                      # in my_fun() are not visible here
pid_a=$!
my_fun b &
pid_b=$!

wait $pid_a $pid_b

