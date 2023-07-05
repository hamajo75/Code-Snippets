#!/bin/bash

start_script() {
    if is_script_running; then
        echo "Script is already running."
    else
        nohup ./"$SCRIPT_NAME" $@ > "${SCRIPT_NAME%.sh}.out" 2>&1 &
        echo "$!" > "$PID_FILE"
        if is_script_running; then
            echo Started "$SCRIPT_NAME."
        else
            echo "Failed to start $SCRIPT_NAME"
            exit 1
        fi
    fi
}

stop_script() {
    if is_script_running; then
        pkill -F "$PID_FILE" > /dev/null 2>&1
        rm "$PID_FILE"
        echo "Stopped $SCRIPT_NAME"
    else
        echo "Script is not running."
    fi
}

is_script_running() {
    if [ -f "$PID_FILE" ]; then
        local pid=$(cat "$PID_FILE")
        if ps -p "$pid" > /dev/null; then
            return 0  # Script is running
        else
            rm "$PID_FILE"  # Remove stale PID file
        fi
    fi
    return 1  # Script is not running
}

CMD=$1
shift 1

SCRIPT_NAME=${1:-"other_script.sh"}
PID_FILE="${SCRIPT_NAME%.sh}.pid"
shift $(($# < 1 ? $# : 1))

case "$CMD" in
    start)
        start_script $@
        ;;
    stop)
        stop_script
        ;;
    status)
        if is_script_running; then
            echo "$SCRIPT_NAME is running."
        else
            echo "$SCRIPT_NAME is not running."
        fi
        ;;
    *)
        echo "Usage: $0 {start|stop|status}"
        exit 1
        ;;
esac

exit 0
