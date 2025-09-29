set(PICO_BOARD pico_w CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_SDK_PATH ../modules/pico-sdk)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(modules/pico-sdk/external/pico_sdk_import.cmake)

if (${PICO_BOARD} STREQUAL "pico_w")
  include(modules/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)
elseif (${PICO_BOARD} STREQUAL "pico2_w")
  include(modules/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2350_ARM_NTZ/FreeRTOS_Kernel_import.cmake)
else ()
  message(FATAL_ERROR "Unsupported board ${PICO_BOARD}")
endif()

project(PicoQuestPinball)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(firmware
    firmware/main.c
    firmware/button.c
    firmware/keyboard.c
    firmware/nudge.c
    firmware/lis3dh.c
    firmware/filter.c
    firmware/hid_keyboard_demo.c
)

# Add pico-sdk library which aggregates commonly used features
target_link_libraries(firmware
    pico_stdlib
    pico_util
    pico_cyw43_arch_none
    pico_btstack_cyw43
    pico_btstack_classic
    pico_async_context_freertos
    FreeRTOS-Kernel-Heap4
    hardware_i2c
)

target_include_directories(firmware PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/firmware
)

pico_enable_stdio_usb(firmware 1)
pico_enable_stdio_uart(firmware 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(firmware)
