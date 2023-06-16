# simple replace
VAR=1.77.0
echo ${VAR//./_}

# comparison operators
if [[ "string" == "string" ]]; then echo equal; fi
if [[ "string" != "string1" ]]; then echo not equal; fi
if [[ -z "" ]]; then echo empty; fi
if [[ -n "string" ]]; then echo not empty; fi

# uppercase: ^ fist letter, ^^ all, lowercase: ~, ~~
lowercase="abcdefg"
echo ${lowercase^^}
protocol="TCP"
echo ${protocol~~}
