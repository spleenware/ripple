# Ripple
This project is an IOT LoRa mesh, typically for closed systems either involving sensors and/or users with dedicated pagers or companion Android devices.

## Devices and Roles

Here are links to the currently supported devices:
* <a href="https://www.digitspace.com/products/wireless-iot/lpwan/lora/lora32-v2-1-esp32-oled-0-96inch-ble-wifi-wireless-module-ip5306-915mhz?0304c1269e4c81b4" target="_blank">TTGO LoRa32 V2</a>
* <a href="https://heltec.org/project/wifi-lora-32/" target="_blank">Heltec LoRa32 V2</a>
* <a href="https://www.adafruit.com/product/3178" target="_blank">Adafruit Feather LoRa</a>
* <a href="https://www.seeedstudio.com/Seeeduino-XIAO-Arduino-Microcontroller-SAMD21-Cortex-M0+-p-4426.html" target="_blank">Seeed Xiao</a>

There are a number of firmwares now supported for a variety of development boards. Not all combinations are supported, however. Below is a matrix of the boards and firmwares currently supported:

|   | TTGO V2 | Heltec V2 | Adafruit Feather LoRa | Seeed Xiao + RFM95 | Seeed Xiao + SX1262 | T-Beam v1.1 |
| ------------- | ------ | ----- | ----- | ----- | ----- | -------- |
| Pager/Messenger (USB-OTG) |  Yes | Yes | Yes | Yes | Yes | Yes |
| Pager/Messenger (Bluetooth) |  Yes | Yes | - | - | - | Yes |
| Repeater |  Yes | Yes |  - |  - | - | - |
| Sensor |  Yes | Yes |  Yes |  Yes | Yes | - |
| GPS Tracker | Yes | Yes | Yes | Yes | Yes | Yes |
| QWERTY Pager |  Yes | Yes | - | - | - | - |
| Tactical (Bluetooth) |  Yes | Yes | - | - | - | - |
| GeoPager | Yes | - | - | - | Yes | - |

Users of the Ripple Messenger Android app connect a device either over USB-OTG cable or Bluetooth, using one of the 'Pager/Messenger' firmware targets. This is also the case for the admin monitoring a sensor mesh using the Ripple Commander app.

Users of the Ripple Tactical Android app connect a device with one of the Tactical firmware targets, with only Bluetooth currently supported.

The 'QWERTY pager' firmware is for the stand-alone pager devices which don't require a companion Android. These are for text messaging among other QWERTY pagers and/or users with the Ripple Messenger app. These can also work with the Repeater devices.

The Sensor and GPS Tracker devices are initially connected over USB-OTG, to an Android device running Ripple Commander app, for just the configuration, but then operate on their own afterwards. The Commander app then monitors them using a Pager/Messenger flashed device (either over USB or Bluetooth).

There is a firmware for a sland-alone pager with GPS, called GeoPager. This has been superceded by the Ripple Tactical app + firmware.

## ESP Targets (flashing)

There is a very handy flashing tool you can install for flashing the firmware binaries to any of the ESP32 targets. Just install the ESPHome Flasher tool from [here](https://github.com/esphome/esphome-flasher/releases).

It has a graphical interface, and you only need select the main .bin file (eg. RippleV3-Bluetooth-TTGOV2.bin), not the -partitions.bin file, select the serial port, and click the 'Flash ESP'.

NOTE: when flashing the TTGO V2 boards, you must remove the micro SD card from the slot! (for some reason this interferes with the USB serial)

## Flashing with Arduino tools - Pre-requisites

You will need to install the Arduino IDE and add support for at least one of the following Boards:
 1. Adafruit Feather M0
 2. Seeeduino M0 family
 3. TTGO WiFi Lora 32, v1 to v2 (ESP32)
 4. Heltech WiFi Lora 32  (ESP32)
 5. Sparkfun Lora Gateway (ESP32)
 6. SParkfun Pro RF
 
For help on getting ESP32 support installed see this article: https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/

Checkout the firmware bin(ary) images to your local machine, and from the command-line, use one of the following command incantations to flash the firmware to your board (NOTE: each command is ONE line only!):

# QWERTY Pager/Messenger

## TTGO V1.6 to V2.1 boards

### for M5 Stack keyboard

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoU~ART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 RippleQwerty-TTGOV2.bin 0x8000 RippleQwerty-TTGOV2.partitions.bin 
```

### for Blackberry Q10 keyboard and Lilygo I2C module

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 /~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 /~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 RippleQwerty-TTGOV2-BB.bin 0x8000 RippleQwerty-TTGOV2-BB.partitions.bin
```

### for Blackberry Q10 keyboard and Lilygo I2C module, and external OLED display (0x3D I2C)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 RippleQwerty-TTGOV2-BB-3D.bin 0x8000 RippleQwerty-TTGOV2-BB-3D.partitions.bin
```

# Ver 5 firmware builds

## Adafruit Feather M0

### Messenger Node - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleV5-USB-feather.bin -R 
```
### GPS Tracker Node - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleTrackerV5-Feather.bin -R 
```
## Heltech V2 boards

### GPS Tracker Node - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 RippleTrackerV5-HeltecV2.bin 0x8000 RippleTrackerV5-HeltecV2.partitions.bin 
```

# Ver 4 firmware builds (with new key exchange design)

## Seeeduino Xiao

### GPS Tracker Node - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/Seeeduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleTrackerV4-USB-Xiao.bin -R 
```
### Sensor Node - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/Seeeduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleSensorV4-USB-Xiao.bin -R 
```

### Messenger (USB-OTG) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/Seeeduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleV4-USB-Xiao.bin -R 
```

## TTGO V2

### Dedicated Repeater (with Post Office support) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 RippleRepeater-TTGOV2.bin 0x8000 RippleRepeater-TTGOV2.partitions.bin
```

## Heltech V2 boards

### Messenger (USB-OTG only) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_qio_80m.bin 0x10000  Ripple-USB-heltech_v2.bin 0x8000 Ripple-USB-heltech_v2.partitions.bin 
```
### Messenger (Bluetooth Classic) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-Bluetooth-heltech_v2.bin 0x8000 Ripple-Bluetooth-heltech_v2.partitions.bin
```

### Dedicated Repeater (with Post Office support) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 RippleRepeater-heltec_v2.bin 0x8000 RippleRepeater-heltec_v2.partitions.bin
```

## TTGO T-Beam v1.1 boards

### GPS Tracker Node - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 RippleTrackerV5-TBeam.bin 0x8000 RippleTrackerV5-TBeam.partitions.bin
```

# Ver 3 firmware builds (with 'commander' Low Power Mode support)

## Adafruit Feather M0

### Messenger (USB-OTG) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleV3-USB-feather.bin -R 
```

## TTGO V1.6 to V2.1 boards

### Messenger (Bluetooth Classic) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000  RippleV3-Bluetooth-TTGOV2.bin 0x8000 RippleV3-Bluetooth-TTGOV2.partitions.bin 
```

### Messenger (USB-OTG) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoU~ART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 RippleV3-USB-TTGOV2.bin 0x8000 RippleV3-USB-TTGOV2.partitions.bin
```

# Ver 2 firmware builds (with 'commander' app support)

## Adafruit Feather M0

### Messenger (USB-OTG) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v Ripple-USB.Feather_m0.bin -R 
```

### GPS Tracker Node - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleTracker-915-USB.feather_m0.bin -R 
```

### Sensor Node - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleSensor-915-USB.feather_m0.bin -R 
```

## Sparkfun Pro RF

### Messenger (USB-OTG) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0-arduino3/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v Ripple-USB-Sparkfun-Pro.bin -R 
```

## TTGO/Heltech V1 boards

### Messenger (USB-OTG) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-USB.TTGO-V1.bin 0x8000 Ripple-USB.TTGO-V1.partitions.bin 
```

### Messenger (Bluetooth LE) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-BLE.TTGO-V1.bin 0x8000 Ripple-BLE.TTGO-V1.partitions.bin 
```

## Sparkfun Lora Gateway

### Messenger (USB-OTG) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-USB-Sparkfun.bin 0x8000 Ripple-USB-Sparkfun.partitions.bin 
```

### Messenger (Bluetooth Classic) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-Bluetooth.Sparkfun.bin 0x8000 Ripple-Bluetooth.Sparkfun.partitions.bin 
```

## TTGO V1.6 to V2.1 boards

### Messenger (Bluetooth Classic) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-Bluetooth.TTGOV2.bin 0x8000 Ripple-Bluetooth.TTGOV2.partitions.bin 
```

### Messenger (Bluetooth LE) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-BLE.TTGOV2.bin 0x8000 Ripple-BLE.TTGOV2.partitions.bin 
```

### Messenger (USB-OTG) - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-USB.TTGOV2.bin 0x8000 Ripple-USB.TTGOV2.partitions.bin
```

### GeoPager Node - 433 to 915MHz (configurable)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-GeoPager-TTGOV2.bin 0x8000 Ripple-GeoPager-TTGOV2.partitions.bin 
```
