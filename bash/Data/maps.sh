#!/bin/bash

my_fun() {
  # bash > version 4
  declare -A my_map   # local by default
  my_map["interface"]="interface_value"
  my_map["port"]="port_value"
  my_map["call"]="ls -l"

  # you cannot copy an associative array !!
  for key in "${!my_map[@]}"; do
    my_global_map[$key]=${my_map[$key]}
  done
}

declare -A my_global_map                    # don't forget this!
my_fun
echo "${my_global_map["interface"]}"
echo "${my_global_map["port"]}"
echo "${my_global_map["call"]}"

echo "Executing map entry string"
call_str=("${my_global_map["call"]}")
echo $call_str
call=($call_str)
"${call[@]}"

echo "Executing map entry built from other map entries"
declare -A link2
link2["destination"]="1.2.3.4"
link2["port"]="22"
link2["iperf_call"]="iperf3 \
                     -c ${link2["destination"]} \
                     -p ${link2["port"]} \
                     --connect-timeout 50"

call_str=("${link2["iperf_call"]}")
echo $call_str
call=($call_str)
"${call[@]}"