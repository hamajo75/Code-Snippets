#!/bin/bash

echo "script started"
sleep 2
>&2 echo "script finished with error"
exit 1