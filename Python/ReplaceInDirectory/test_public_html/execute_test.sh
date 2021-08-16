#!/bin/sh

rm -r data
cp -r data_original data

python3 ../ReplaceInDirectory/replaceInDirectory.py data replace.csv
