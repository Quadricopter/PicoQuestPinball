# Pico Quest Controller

Bluetooth controller for [Pinball FX VR](https://www.meta.com/fr-fr/experiences/pinball-fx-vr/7255396864545733/), built around a `Raspberry Pi Pico W`.  
![PincoQuestPinball](assets/picoquestpinball.png)  

PicoQuestPinball is a simple *"why not"* / *"proof of concept"*, for **evaluation** and **non-commercial-use**.  
For USB usage, please have a look at incredible [PinscapePico](https://github.com/mjrgh/PinscapePico) project.

# Third-party

[Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk)  
[BlueKitchen's BTstack](https://github.com/bluekitchen/btstack)  
[FreeRTOS](https://github.com/FreeRTOS/FreeRTOS-Kernel)

## Reference

Project is based on [https://mcuapplab.blogspot.com/2023/06/raspberry-pi-pico-w-btstack-ep-4-hid.html](https://mcuapplab.blogspot.com/2023/06/raspberry-pi-pico-w-btstack-ep-4-hid.html)  
Itself based on BTstack HID keyboard demo [https://github.com/bluekitchen/btstack/blob/master/example/hid_keyboard_demo.c](https://github.com/bluekitchen/btstack/blob/master/example/hid_keyboard_demo.c)

## Pinout

`Pinball FR VR` support external keyboard with following mapping :
- Left flipper : ` u ` key
- Right flipper : ` 6 ` key
- Launch ball :  ` 8 ` key
- Menu :  ` i ` key

- Nudge up : ` s ` key ( still didn't understood difference with ` a ` key.. )
- Nudge left : ` d ` key
- Nudge right : ` f ` key
  
Default Pico W GPIO pinout (see [board.h](firmware/board.h) file)
- Left flipper : 2
- Right flipper : 3
- Launch ball : 4
- Menu : 5

## Build

If you don't use `pico-sdk` and/or `FreeRTOS-Kernel` for another project, I suggest you retrieve them in a `modules` subdirectory

```shell
mkdir modules
```

Get [pico-sdk](https://github.com/raspberrypi/pico-sdk) sources  

```shell
cd modules
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
cd ../..
```

Get [FreeRTOS](https://github.com/raspberrypi/FreeRTOS-Kernel) sources

```shell
cd modules
git clone https://github.com/raspberrypi/FreeRTOS-Kernel.git
cd FreeRTOS-Kernel
git submodule update --init
cd ../..
```

### Terminal

`Pico W`

```shell
cmake -S . -B build -DPICO_BOARD=pico_w -DPICO_SDK_PATH=modules/pico-sdk -DFREERTOS_KERNEL_PATH=modules/FreeRTOS-Kernel
cmake --build build
```

`Pico 2 W`

```shell
cmake -S . -B build -DPICO_BOARD=pico2_w -DPICO_SDK_PATH=modules/pico-sdk -DFREERTOS_KERNEL_PATH=modules/FreeRTOS-Kernel
cmake --build build
```

### Visual Studio Code

Edit project local `.vscode/settings.json` file and add following lines :

For  `Pico W`

```json
    "cmake.configureSettings": {
        "PICO_BOARD": "pico_w",
        "PICO_SDK_PATH": "${workspaceFolder}/modules/pico-sdk",
        "FREERTOS_KERNEL_PATH": "${workspaceFolder}/modules/FreeRTOS-Kernel"
    }
```

For `Pico 2 W`

```json
    "cmake.configureSettings": {
        "PICO_BOARD": "pico2_w",
        "PICO_SDK_PATH": "${workspaceFolder}/modules/pico-sdk",
        "FREERTOS_KERNEL_PATH": "${workspaceFolder}/modules/FreeRTOS-Kernel"
    }
```

Press `F7` to build firmware
