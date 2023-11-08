#!/usr/bin/env python3
import argparse
import string

def find_longest_word(filename):
    output = ''

    try:
        with open(filename, 'r') as file:
            for one_line in file:
                # Remove punctuation from the line
                one_line = one_line.translate(str.maketrans('', '', string.punctuation))
                for one_word in one_line.split():
                    if len(one_word) > len(output):
                        output = one_word
    except IOError:
        print(f"Could not read file: {filename}")
        return None

    if output == '':
        print(f"No words found in file: {filename}")
        return None

    return output

parser = argparse.ArgumentParser()
parser.add_argument("filename", help="The name of the file to check")
args = parser.parse_args()

print(find_longest_word(args.filename))