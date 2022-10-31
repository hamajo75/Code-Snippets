FROM ubuntu:21.04

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Vienna
# install dependencies
RUN apt-get update && \
    apt-get install -y g++ clang clang-tools cppcheck build-essential libssl-dev libgtest-dev libgmock-dev doxygen wget \
    libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev \
    gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x valgrind python3-pip && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

ADD ./ /usr/src/work-dir/
WORKDIR /usr/src/work-dir/
CMD ["./tools/docker-run-qa.sh"]