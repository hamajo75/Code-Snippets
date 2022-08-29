
form = """#!/bin/sh

if ! command -v generate_cc_source.sh > /dev/null 2>&1; then
  echo "Could not find generate_cc_source.sh. Did you set the PATH variable?" >&2
  exit 1
fi
cd $(dirname $0)

generate_cc_source.sh periodical.alarmAndErrorState.schema.json periodical_alarmAndErrorState.h wimp::alarm_and_error_state AlarmAndErrorState --src-lang=schema"
"""

def basic():
  print(form)

  str = "access a string like an array"
  print(str[5:])
  str.capitalize()
  if ("access" in str):
    print("contained")

  txt = "hello.my.darling"
  x = txt.split(".")

  print(x)

def find_replace():
  str = "messages/WIMP/A2_LOWER.A3_LOWER.A1_UPPER.DEVICE_DISCONNECTED.GENERAL_ERROR"
  path = str[0:str.rfind("/") + 1]
  array = str[str.rfind("/") + 1:].split(".")
  print (path)
  print (array)
  content = ""
  for file in array[0:-1]:
    with open(path + file) as f:
      try:
        content = content + f.read() + ",\n"
      except:
        print("Couldn't read file: " + path + file)
  with open(path + array[-1]) as f:
    try:
      content = content + f.read() + "\n,"
    except:
      print("Couldn't read file: " + path + file)


  print (content)

if __name__ == "__main__":
  # basic()
  find_replace()
