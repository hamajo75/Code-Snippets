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

# default variable values
LOCAL_BROKER_URL=${LOCAL_BROKER_URL:-"localhost:5672"}

# open new gnome-terminal in dir and source settings
gnome-terminal --working-directory='/home/jha/Development/mee066-esw-intercom-apps/build_target' \
-- env -i bash --norc --noprofile -c "source /home/jha/Development/Yocto/sdk/environment-setup-cortexa7t2hf-neon-vfpv4-me-linux-gnueabi; exec bash"
