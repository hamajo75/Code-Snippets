# simple replace
VAR=1.77.0
echo ${VAR//./_}

# comparison operators
"string" == "string"
"string" != "string"
-z ""  # true if string length == 0
-n "1" # true if string length > 0

# uppercase: ^ fist letter, ^^ all, lowercase: ~, ~~
echo ${$interface^^}