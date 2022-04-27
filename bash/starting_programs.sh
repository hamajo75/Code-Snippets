#!/bin/sh

# run kill 0 to kill all background (chhild) processes in case one of the signals
# SIGINT SIGTERM SIGERR SIGEXIT
trap "exit" INT TERM ERR
trap "kill 0" EXIT

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
  mkfifo /tmp/intercom-in > /dev/null 2>&1
  tail -f /tmp/intercom-in | intercom-daemon -u $REMOTE_BROKER_URL --ssl-path=ssl-certs -t > /dev/null &
}

stopIntercomDaemon() {
  echo stop > /tmp_intercom-in  # this might lead to "interrupted system call" error
}

# save process id and kill later
foo &
FOO_PID=$!
kill $FOO_PID

# default variable values
: ${LOCAL_BROKER_URL:-"localhost:5672"}

# open new gnome-terminal in dir and source settings
gnome-terminal --working-directory='/home/jha/Development/mee066-esw-intercom-apps/build_target' \
-- env -i bash --norc --noprofile -c "source /home/jha/Development/Yocto/sdk/environment-setup-cortexa7t2hf-neon-vfpv4-me-linux-gnueabi; exec bash"

# change workdir to folder of this script
cd "$(dirname "$0")"
echo "WORKDIR: ${PWD}"

# collect exit codes
success=0
./cmd1.sh
[[ $? -ne 0 ]] && success=1
./cmd2.sh
[[ $? -ne 0 ]] && success=1

exit $success

# exit on error
if [[ $? -ne 0 ]] ; then
  exit 1
fi

# exit on error (if any commands fail)
set -e