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

declare -A link2
link2["destination"]="1.2.3.4"
link2["port"]="22"
cmd="iperf3 \
  -c ${link2["destination"]} \
  -p ${link2["port"]}"

echo $cmd