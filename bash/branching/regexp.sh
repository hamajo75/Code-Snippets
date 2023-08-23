#!/bin/bash

value=+23.5

if [[ "$value" == ?([+-])+([0-9])?([.]+([0-9])) ]]; then
  echo $value is "VALID"
elif [[ "$value" == "INVALID" ]]; then
  echo $value is "INVALID"
else
  echo "Illegal value"
fi