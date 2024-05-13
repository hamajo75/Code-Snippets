#!/bin/bash

docker pull structurizr/lite
docker run -it --rm -p 8080:8080 -v /home/joe/Development/Structurizr/:/usr/local/structurizr structurizr/lite

