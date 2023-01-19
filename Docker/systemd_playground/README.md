# Create & run docker container
https://github.com/AkihiroSuda/containerized-systemd

`docker build -t systemd_playground -f Dockerfile.ubuntu-20.04 .`
`docker run -it --rm --privileged systemd_playground /bin/bash`

# Switching targets
master: run foo1 & foo2
slave: run foo2 & foo3     (foo2 will continue running)