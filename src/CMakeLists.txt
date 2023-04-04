# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(vl53l4cd C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(vl53l4cd main.c )

pico_set_program_name(vl53l4cd "vl53l4cd")
pico_set_program_version(vl53l4cd "0.1")

pico_enable_stdio_uart(vl53l4cd 1)
pico_enable_stdio_usb(vl53l4cd 1)

target_sources(vl53l4cd PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/main.c
        ${CMAKE_CURRENT_LIST_DIR}/loop.c
        ${CMAKE_CURRENT_LIST_DIR}/blinker.c
        ${CMAKE_CURRENT_LIST_DIR}/vl53l4cd.c
        )

# Add the standard library to the build
target_link_libraries(vl53l4cd pico_stdlib)

# Add any user requested libraries
target_link_libraries(vl53l4cd
	hardware_timer
	hardware_i2c
)


