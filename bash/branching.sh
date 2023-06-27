#!/bin/bash

# boolean operators: &&, ||


# check for argument
# the space " " before "]" is necessary !
if [ "$1" ]; then
  remote_url=$1
else
  remote_url=172.31.1.83:5671
fi

# check absence of parameter
if [ -z "$1" ]; then
  echo '$1 not present'
fi

echo "external url:" $remote_url

# check if file exists
if [[ -e readme.txt ]] ; then
  echo 'The file "readme.txt" exists.'
else
  echo 'The file "readme.txt" does not exist.'
fi

# check if string is not empty
if [ "$string" ]; then
   echo not empty
fi

# check if string is equal
destination=root@10.64.0.52
if [[ "$destination" == *"@10."* ]]; then
   echo "contains"
fi

# check if string contains substring
str="hello world"
substr="hello"
if [[ $str == *"$substr"* ]];
then
    echo "String contains substring."
else
    echo "String does not contain substring."
fi

# case switch
case $1 in

   start)
      echo starting
      ;;
   stop)
      echo stoping
      ;;
   restart)
      echo restarting
      ;;
   *)
      echo 'dont know this case'
      ;;
esac

# conditionally execute cmd
[[ -n $DEBUG ]] && echo "DEBUG is set"
[[ -z $DEBUG ]] && echo "DEBUG is not set"

# select
select dir in /dir1 /dir2 /dir3
do
  echo You have selected: $dir
  break
done