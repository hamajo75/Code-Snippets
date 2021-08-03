  if [ "$1" ]; then
   remote_url=$1
  else
   remote_url=172.31.1.83:5671
  fi

  echo "external url:" $remote_url

  