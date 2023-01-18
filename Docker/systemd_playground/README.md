# Create & run docker container

`docker build -t foo -f Dockerfile.ubuntu-20.04 .`
`docker run -it --rm --privileged --workdir /usr -e FOO=hello foo /bin/bash`
