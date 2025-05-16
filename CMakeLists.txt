# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

# Specify the target board 
if (NOT DEFINED PICO_BOARD)
    set(PICO_BOARD pico)
endif()

# Import Pico SDK
include("$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake")
project(pedestrian_crossing C CXX ASM)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Set up variables for directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

FILE(GLOB src src/*.cpp)

# Tell CMake where to find the executable source file
add_executable(${CMAKE_PROJECT_NAME}
    ${src}
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
                           ${CMAKE_CURRENT_LIST_DIR}    
                           ${CMAKE_CURRENT_SOURCE_DIR}/include
                           )

target_link_libraries(${CMAKE_PROJECT_NAME}
                        pico_stdlib
                        hardware_gpio)

# Include tests directory as subdirectory
add_subdirectory(tests/target/trafficlight)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

# Print memory usage after build
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")