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
  sleep 1 &
  pid_a=$!
  echo started with pid: $pid_a
  sleep 1 &
  pid_b=$!
  echo started with pid: $pid_b

}

my_fun

# you need to be waiting in order to stop the background process
# because it keeps running if this shell is already
wait $pid_a $pid_b
