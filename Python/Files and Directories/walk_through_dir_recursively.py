#!/usr/bin/env python3

import os, sys

directory = "whatever"

if not os.path.exists(directory):
  sys.exit("Directory \"" + directory + "\" doesn't exit!")

for dir_path, dirs, files in os.walk(directory, topdown = True):
  for name in files:
    print(os.path.join(dir_path, name))
  for name in dirs:
    print(os.path.join(dir_path, name))
