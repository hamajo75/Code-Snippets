#!/usr/bin/env python3

import sys
import argparse
import re

# simple verison
print(sys.argv)
print(sys.argv[1])

def parse_args():
    parser = argparse.ArgumentParser()

    parser.add_argument(
        "function_call",
        help="function call e.g. switch_to_sim_slot(1, 1)",
        type=str,
    )

    return parser.parse_args()

# call: ./cmd_line_args.py "hello(nice, world!)"
def hello(a, b):
    print(f"Hello {a} {b}")

def main():
    args = parse_args()
    match = re.match(r'(\w+)\((.*)\)', args.function_call)

    function = None
    parameters = None
    if match:
        function = match.group(1)
        parameters = match.group(2)
        parameters = tuple(param.strip() for param in parameters.split(",") if param)

    func = globals()[function]
    if parameters:
        func(*parameters)
    else:
        func()

if __name__ == "__main__":
    main()