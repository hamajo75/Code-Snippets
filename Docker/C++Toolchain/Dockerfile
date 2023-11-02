# Use the Ubuntu as the base image
FROM ubuntu:latest

# Set environment variables to prevent interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Update the package repository and install necessary packages
RUN apt-get update && \
    apt-get install -y && \
    build-essential g++ gdb cmake clang clang-tools libboost-dev && \
    cppcheck valgrind libgmock-dev libgmock-dev && \
    python python3-pip & \
    git wget ssh sudo bash

RUN pip3 install cpplint

# # install cmake 3.20 version
# RUN wget "https://cmake.org/files/v3.20/cmake-3.20.2-linux-x86_64.sh" -q -O /cmake-3.20.2-linux-x86_64.sh
# RUN sh /cmake-3.20.2-linux-x86_64.sh --prefix=/usr/local --skip-license

# Set a working directory
WORKDIR /app

# Clone the GitHub repository
RUN git clone <repository_url>

# Build your C++ application (adjust this according to your project)
RUN cmake . && make

