#!/bin/sh

# output timestamp
echo "`date '+%Y-%m-%d %H:%M:%S'`  Response OK"

# redirect stdout and stderr
qpidd --check > /dev/null 2>&1

# override output file
cat file.txt > output.txt

# redirect to stderr
cat file.txt > output.txt 1>&2

# append
cat file.txt >> output.txt
# stdout + stderr
cat file.txt >> output.txt 2>&1

cat << EOF >> output.txt
{
  "Object": {
    "key": "value"
  }
}
EOF