FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    cmake \
    lcov \
    gcovr \
    pax-utils \
    libgtest-dev \
    libboost-all-dev \
    libqpid-proton-cpp-dev \
    shellcheck \
    cppcheck \
    vim \
    python3-pip \
    ninja-build \
    default-jdk graphviz \
    python3-pip \
    gforth \
    python3 \
    haskell-platform

RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

RUN pip3 install cpplint
# RUN pip3 install dbus-python

RUN git clone https://github.com/catchorg/Catch2.git --depth 1 --branch v3.4.0 && \
    cd Catch2 && \
    cmake -Bbuild -H. -DCMAKE_CXX_STANDARD=17 -DCATCH_BUILD_STATIC_LIBRARY=ON -DBUILD_TESTING=OFF -DCATCH_INSTALL_DOCS=OFF && \
    cmake --build build/ --target install && \
    cd .. && \
    rm -rf Catch2