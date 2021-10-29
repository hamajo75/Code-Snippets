
form = """#!/bin/sh

if ! command -v generate_cc_source.sh > /dev/null 2>&1; then
  echo "Could not find generate_cc_source.sh. Did you set the PATH variable?" >&2
  exit 1
fi
cd $(dirname $0)

generate_cc_source.sh periodical.alarmAndErrorState.schema.json periodical_alarmAndErrorState.h wimp::alarm_and_error_state AlarmAndErrorState --src-lang=schema"
"""

print(form)

str = "access a string like an array"
print(str[5:])

txt = "hello.my.darling"
x = txt.split(".")

print(x)