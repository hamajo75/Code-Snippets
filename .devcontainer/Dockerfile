FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    cmake \
    lcov \
    gcovr \
    libgtest-dev \
    libboost-all-dev \
    libqpid-proton-cpp-dev \
    clangd \
    shellcheck \
    cppcheck \
    vim \
    python3-pip

RUN pip3 install cpplint

RUN git clone https://github.com/catchorg/Catch2.git --depth 1 --branch v3.4.0 && \
    cd Catch2 && \
    cmake -Bbuild -H. -DCMAKE_CXX_STANDARD=17 -DCATCH_BUILD_STATIC_LIBRARY=ON -DBUILD_TESTING=OFF -DCATCH_INSTALL_DOCS=OFF && \
    cmake --build build/ --target install && \
    cd .. && \
    rm -rf Catch2