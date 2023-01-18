#!/bin/bash
sleep infinity & PID=$!
trap "kill $PID" INT TERM

echo ------- starting foo$1 -------
wait $PID
echo ------- exited foo$1 -------
