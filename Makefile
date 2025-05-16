BOARD ?= pico2 # Change to pico if using pico1

# Directories
SRC_DIR = ./src
TEST_DIR = ./tests
INCLUDE_DIR = ./include
BUILD_DIR = ./build

# Architecture-specific build directories
ARM_BUILD_DIR = $(BUILD_DIR)/arm

# Default target
.PHONY: all
all: firmware

# Create build directories
$(ARM_BUILD_DIR):
	mkdir -p $@

# Build firmware with tests
.PHONY: firmware
firmware: $(ARM_BUILD_DIR)
	cd $(ARM_BUILD_DIR) && \
	cmake -DPICO_BOARD=$(BOARD) \
		-DPICO_SDK_PATH=$(PICO_SDK_PATH) ../.. && \
	make

# Clean everything
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Clean test builds
.PHONY: test_clean
test_clean:
	rm -rf $(ARM_BUILD_DIR)/tests