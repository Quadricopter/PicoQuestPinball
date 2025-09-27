set(PICO_BOARD pico_w CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_SDK_PATH ../modules/pico-sdk)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(modules/pico-sdk/external/pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(firmware
    firmware/main.c
    firmware/button.c
    firmware/keyboard.c
)

# Add pico-sdk library which aggregates commonly used features
target_link_libraries(firmware
    pico_stdlib
    pico_util
    pico_cyw43_arch_none
    pico_btstack_cyw43
    pico_btstack_classic
)

target_include_directories(firmware PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/firmware
)

pico_enable_stdio_usb(firmware 1)
pico_enable_stdio_uart(firmware 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(firmware)
