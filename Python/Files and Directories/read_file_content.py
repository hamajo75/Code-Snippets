#!/usr/bin/env python3

import os

fpath = "file.txt"
with open(fpath, encoding="utf-8") as f:
  try:
      content = f.read()
  except:
      print("Couldn't read file: " + fpath)

print(content)