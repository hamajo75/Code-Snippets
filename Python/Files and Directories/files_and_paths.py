#!/usr/bin/env python3

import os

# get path from full filepath
print(os.path.dirname("/usr/bin/config.json"))

# get filename from full filapath
print(os.path.basename("/usr/bin/config.json"))