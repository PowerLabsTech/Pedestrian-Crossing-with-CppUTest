# Pedestrian Crossing with CppUTest

Welcome to the Pedestrian Crossing with CppUTest project! This repository contains the source code for a pedestrian crossing system built using Test-Driven Development (TDD) principles with CppUTest on the Raspberry Pi Pico. It’s part of an article series by Powerlabs demonstrating how to write reliable embedded code, step-by-step.

See the article [here](https://powerlabstech.com/blog/posts/-A-Beginner%E2%80%99s-Guide-to-Setting-Up-CppUTest-?id=10)

## Table of Contents

- [1. Prerequisites](#1-prerequisites)
- [2. Setup Instructions](#2-setup-instructions)
  - [2.1. Clone the Repository](#21-clone-the-repository)
  - [2.2. Install the Dependencies You Need](#22-install-the-dependencies-you-need)
- [3. Directory Structure](#3-directory-structure)
- [4. Running Tests](#4-running-tests)
  - [4.1. Locally](#41-locally)
  - [4.2. Using Docker](#42-using-docker)
- [5. Practice: Extend the Pedestrian Side](#5-practice-extend-the-pedestrian-side)
  - [5.1. Contributing](#51-contributing)
- [6. License](#6-license)
- [7. Acknowledgments](#7-acknowledgments)

---

## 1. Prerequisites

To build and run this project locally, you’ll need:

- **Raspberry Pi Pico**: The target hardware.
- **Pico SDK**: For Pico development (tested with v1.5.1).
- **CppUTest**: For unit testing (v4.0 or later). (Fetched at runtime)
- **CMake**: Build system (v3.12 or higher).
- **GCC ARM Compiler**: For cross-compiling (e.g., `arm-none-eabi-gcc`).
- **Git**: To clone this repo.
- **USB Cable**: To flash the Pico.

You can also build this project with Docker. You'll need:

- **Raspberry Pi Pico**: The target hardware.
- **Docker**: To ensure a consistent development environment across different machines.
- **Git**: To clone this repo.
- **USB Cable**: To flash the Pico.

---

## 2. Setup Instructions

### 2.1. Clone the Repository

```bash
git clone https://github.com/[your-username]/[your-repo-name].git
cd [your-repo-name]
```

### 2.2. Install the Dependencies You Need

#### Pico SDK

- Follow the [official Pico SDK setup guide](https://github.com/raspberrypi/pico-sdk).
- Set the `PICO_SDK_PATH` environment variable:
  ```bash
  export PICO_SDK_PATH=/path/to/pico-sdk
  ```

#### Git

- **For Ubuntu (Linux):**
  ```bash
  sudo apt update
  sudo apt install git
  ```

- **For macOS:**
  ```bash
  brew install git
  ```

- **For Windows:**
  Download and install Git from [git-scm.com](https://git-scm.com/downloads).

Verify Git installation:
```bash
git --version
```

#### CMake

- **For Ubuntu (Linux):**
  ```bash
  sudo apt update
  sudo apt install cmake
  ```

- **For macOS:**
  ```bash
  brew install cmake
  ```

- **For Windows:**
  Download and install CMake from [cmake.org](https://cmake.org/download/).

Verify CMake installation:
```bash
cmake --version
```

#### ARM Toolchain

- Install the ARM GCC toolchain:
  ```bash
  sudo apt install gcc-arm-none-eabi  # Ubuntu/Debian
  brew install arm-none-eabi-gcc      # macOS
  ```

#### Docker

- **For Ubuntu (Linux):**
  ```bash
  sudo apt update
  sudo apt install docker.io
  sudo systemctl start docker
  sudo systemctl enable docker
  sudo usermod -aG docker $USER
  ```

- **For other operating systems** (e.g., macOS or Windows), refer to the [official Docker installation guide](https://docs.docker.com/get-docker/).

After installation, verify Docker by running:

```bash
docker --version
```

---

## 3. Directory Structure

- `ci-cd-tools/`: Dockerfile for CI/CD (optional).
- `include/`: Header files (e.g., `traffic_light.h`).
- `src/`: Source code (e.g., `traffic_light.cpp`).
- `tests/target/`: Tests for the Pico (e.g., `test.cpp`).
- `CMakeLists.txt`: Build configuration.
- `Makefile`: Build targets (`make firmware`, `make clean`).

---

## 4. Running Tests

### 4.1. Locally

- From the repo root (Ensure you have internet access as CppUTest is fetched at runtime):
  ```bash
  make firmware
  ```
- This generates `.uf2` files in `build` for the project and `build/tests/target/trafficlight` for the tests.

#### Flash the Pico

- Hold the BOOTSEL button on your Pico and connect it via USB.
- Copy the `.uf2` file to the Pico (it mounts as a drive):
  ```bash
  cp build/tests/target/trafficlight/trafficlight_test.uf2 /Volumes/RPI-RP2/
  ```
- The Pico reboots and runs the test.
- Test output appears via the Pico’s UART (e.g., use `picocom` at 115200 baud).

### 4.2. Using Docker

#### Building the Docker Image

To build the Docker image using the `Dockerfile` created, run the following command in the terminal from the root directory (You may need internet access):

```bash
docker build -t build-env -f ./ci-cd-tools/Dockerfile .
```

This command will build a Docker image with the name `build-env` using the instructions in the `Dockerfile`.

#### Running the Container

To run the container in interactive mode, use the following command:

```bash
docker create -i -t --entrypoint="/bin/bash" --name build_container build-env
docker start -i build_container
```

Explanation:
- `-i`: Keeps the STDIN open for interaction.
- `-t`: Allocates a pseudo-TTY for a terminal interface.
- `--entrypoint="/bin/bash"`: Overrides the container's entrypoint to start in bash mode.
- `--name build_container`: Gives the container a specific name.
- `build-env`: Name of the Docker image used.

In the Docker environment, cd into `pedestrian_crossing` directory, build the project and flash the Pico.

#### Other Useful Docker Commands

- `docker container rm build_container`: For deleting a container.
- `docker rmi build-env:latest`: For removing the Docker image named `build-env`. Use this command to delete the image if it's no longer needed or to rebuild it.
- `docker cp <container>:<absolute_path_to_file> <destination>`: Run this in a separate terminal for copying a file from the Docker environment to your local system. Note: The Docker container must be running, and the absolute path to the file must be used.
- `docker ps -a`: To list all containers, including those that are stopped.
- `docker images`: To list all Docker images on your system.
- `docker start build_container`: To start the specified container.
- `docker stop build_container`: To stop the specified running container.
- `exit`: To exit the running container.

---

## 5. Practice: Extend the Pedestrian Side

Try the article’s practice section! Add pedestrian LED and buzzer logic.

### 5.1. Contributing

- Fork the repo, create a branch, and submit a pull request.
- Follow TDD: write tests first, then code.

---

## 6. License

MIT License—see `LICENSE` file.

---

## 7. Acknowledgments

- Built with [Pico SDK](https://github.com/raspberrypi/pico-sdk) and [CppUTest](https://github.com/cpputest/cpputest).
- Inspired by real-world pedestrian crossings.

Happy coding and testing!

---