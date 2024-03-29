#!/bin/sh

# loop through all files in folder
for file in *.txt ; do
  echo processing "$file"
done

# read lines from file
station_idx=$(head -n 1 "file.txt")
echo $station_idx

# read whole file into variable
value=`cat file.txt`
echo "$value"

# Monitor changes in a folder:
while inotifywait -e modify /var/log/messages; do
  if tail -n1 /var/log/messages | grep apache; then
    kdialog --msgbox "Blah blah Apache"
  fi
done

# check if file exists
if [[ -e readme.txt ]] ; then
  echo 'The file "readme.txt" exists.'
fi
if [[ ! -e readme.txt ]] ; then
  echo 'The file "readme.txt" does not exist.'
fi