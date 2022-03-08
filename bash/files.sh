#!/bin/sh

# loop through all files in folder
for file in *.txt ; do
  mv "$file" "$file.bak"
done

# Monitor changes in a folder:
while inotifywait -e modify /var/log/messages; do
  if tail -n1 /var/log/messages | grep apache; then
    kdialog --msgbox "Blah blah Apache"
  fi
done

# read from file
station_idx=$(head -n 1 "file.txt")
echo $station_idx