#!/bin/bash

# send string to stdin
# /my/bash/script <<< 'This string will be sent to stdin.'

# send input to background process with fifo
# startIntercomDaemon() {
#   mkfifo /tmp/intercom-in > /dev/null 2>&1
#   tail -f /tmp/intercom-in | intercom-daemon -u $REMOTE_BROKER_URL --ssl-path=ssl-certs -t > /dev/null &
# }

# stopIntercomDaemon() {
#   echo stop > /tmp_intercom-in  # this might lead to "interrupted system call" error
# }

# save process id and kill later
# foo &
# FOO_PID=$!
# kill $FOO_PID

open_new_gnome-terminal_in_dir_and_source_settings() {
  gnome-terminal --working-directory='/home/jha/Development/mee066-esw-intercom-apps/build_target' \
  -- env -i bash --norc --noprofile -c "source /home/jha/Development/Yocto/sdk/environment-setup-cortexa7t2hf-neon-vfpv4-me-linux-gnueabi; exec bash"
}

# change workdir to folder of this script
cd "$(dirname "$0")"
echo "WORKDIR: ${PWD}"

collect_exit_codes() {
  success=0
  ./cmd1.sh
  [[ $? -ne 0 ]] && success=1
  ./cmd2.sh
  [[ $? -ne 0 ]] && success=1

  exit $success
}

# exit on error
if [[ $? -ne 0 ]] ; then
  exit 1
fi

# exit on error (if any commands fail)
set -e
set +e          # ignore errors (continue)

# Wait for a process to end by process ID
# param1: PID
# param2: timeout (default 20s)
# return: success if process does not run
wait_for_pid_end() {
  [ -z "${1}" ] && return 1

  local timeout=${2:-20}
  kill -0 $1 > /dev/null 2>&1 || return 0

  for N in $(seq 1 ${timeout}); do
    kill -0 $1 > /dev/null 2>&1 || return 0
    sleep 1
  done

  kill -0 $1 > /dev/null 2>&1 && return 1
}

# Wait for a process to end
# param1: process name
# param2: timeout (default 20s)
# return: success if process does not run
wait_for_end() {
  [ -z "${1}" ] && return 1

  local timeout=${2:-20}
  pidof $1 > /dev/null 2>&1 || return 0

  for N in $(seq 1 ${timeout}); do
    pidof $1 > /dev/null 2>&1 || return 0
    sleep 1
  done

  pidof $1 > /dev/null 2>&1 && return 1
}

