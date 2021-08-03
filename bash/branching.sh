#!/bin/sh

# check for argument
if [ "$1" ]; then
  remote_url=$1
else
  remote_url=172.31.1.83:5671
fi

echo "external url:" $remote_url

# check if file exists
if [[ -e readme.txt ]] ; then
  echo 'The file "readme.txt" exists.'
else
  echo 'The file "readme.txt" does not exist.'
fi

# check if string is empty
if [ "$string" ]; then
   echo not empty
fi
