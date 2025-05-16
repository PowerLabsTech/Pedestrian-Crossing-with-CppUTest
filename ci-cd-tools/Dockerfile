# Fetch ubuntu image
FROM ubuntu:22.04

# Install python on image
RUN apt-get update && apt-get install -y \
    gcc-arm-none-eabi \
    cmake \
    build-essential \
    autoconf \
    automake \
    libtool \
    git \
    wget \
    python3 \
    python3-dev \
    python3-pip \
    libusb-1.0-0-dev

# Set up environment variable
ENV PICO_SDK_PATH=/root/pico/pico-sdk

# Clone the Pico SDK from git
RUN mkdir -p ${PICO_SDK_PATH} \
    && git clone https://github.com/raspberrypi/pico-sdk.git ${PICO_SDK_PATH} \
    && cd ${PICO_SDK_PATH} \
    && git submodule update --init

# Build and install picotool
RUN cd ${PICO_SDK_PATH}/.. \
    && git clone https://github.com/raspberrypi/picotool.git \
    && cd picotool \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && make install

WORKDIR /root/home

RUN mkdir /root/home/pedestrian_crossing

# Copy the project source code
COPY ./src /root/home/pedestrian_crossing/src
COPY ./include /root/home/pedestrian_crossing/include
COPY ./tests /root/home/pedestrian_crossing/tests
COPY ./Makefile /root/home/pedestrian_crossing/
COPY ./CMakeLists.txt /root/home/pedestrian_crossing/
COPY ./README.md /root/home/pedestrian_crossing/

# Execute script
ENTRYPOINT ["make", "firmware", "-C", "/root/home/pedestrian_crossing/"]