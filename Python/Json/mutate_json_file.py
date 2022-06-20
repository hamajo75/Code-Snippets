#!/usr/bin/env python3

# Usage:
# mutate_json_file.py file <Key> <Value>
# Examples:
# mutate_json_file.py wps.response.changeVideoResolution.json "cameraId" "15fe2c13-cc97-4e72-9a91-d752cae09454"

import sys
import json

with open(sys.argv[1], "r") as read_file:
    data = json.load(read_file)

key = sys.argv[2]
value = sys.argv[3]
print(key)
print(value)

def parse_json_recursively(json_object, key, new_value):
    if type(json_object) is dict and json_object:
        for k in json_object:
            if k == key:
                try:
                    json_object[k] = json.loads(new_value)
                except:
                    json_object[k] = new_value
                print("{}: {}".format(key, json_object[k]))
            parse_json_recursively(json_object[k], key, new_value)

    elif type(json_object) is list and json_object:
        for item in json_object:
            parse_json_recursively(item, key, new_value)

parse_json_recursively(data, key, value)

print(json.dumps(data, indent=2))
