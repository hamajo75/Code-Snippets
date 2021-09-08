#!/bin/sh

# run in the background
program &
# bring it back (%n for multiple processes)
fg
# move to background again
  # Ctrl + z puts current process to sleep
  bg

# see all background processes
jobs

# running multiple cmds if previous was successful
command_1 && command_2

# send string to stdin
/my/bash/script <<< 'This string will be sent to stdin.'

# send input to background process with fifo
startIntercomDaemon() {
  mkfifo /tmp/intercom-in
  tail -f /tmp/intercom-in | ./intercom-daemon -u $REMOTE_BROKER_URL > /dev/null &
}

stopIntercomDaemon() {
  echo stop > /tmp_intercom-in
}