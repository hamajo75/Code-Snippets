#!/bin/bash

my_fun_set_global() {
  # bash > version 4
  declare -A my_map   # local by default: set -gA for global
  my_map["interface"]="interface_value"
  my_map["port"]="port_value"
  my_map["call"]="ls -l"

  # you cannot copy an associative array !!
  for key in "${!my_map[@]}"; do
    my_global_map[$key]=${my_map[$key]}
  done
}

my_fun_pass_in() {
  eval "declare -A link"=${1#*=}
  echo Calling "${link["iperf_call"]}"
}

declare -A my_global_map                    # don't forget this!
my_fun_set_global
echo "${my_global_map["interface"]}"
echo "${my_global_map["port"]}"
echo "${my_global_map["call"]}"

my_fun_pass_in "$(declare -p my_global_map)"

echo "Executing map entry string"
call_str=("${my_global_map["call"]}")
echo $call_str
call=($call_str)
"${call[@]}"

echo "Executing map entry built from other map entries"
declare -A link2
destination=destination
link2["$destination"]="1.2.3.4"
link2["port"]="22"
link2["iperf_call"]="iperf3 \
                     -c ${link2["destination"]} \
                     -p ${link2["port"]}"

bandwidth=1
link2["iperf_call"]="${link2["iperf_call"]} -u -b ${bandwidth}M --get-server-output"

if [[ -v link2[@] ]]; then
  echo Calling "${link2["iperf_call"]} --connect-timeout 50"
  eval "${link2["iperf_call"]} --connect-timeout 50"
fi

[[ -v link2[@] ]] && my_fun_pass_in "$(declare -p link2)"