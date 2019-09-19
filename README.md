# ripple
Arduino Firmware for Ripple LoRa mesh

## Pre-requisites

You will need to install the Arduino IDE and add support for the following Boards:
 1. Adafruit Feather M0 .   -OR-
 2. Heltech WiFi Lora 32 (part of the ESP32 family)
 
Checkout the firmware bin(ary) images to your local machine, and from the command-line, use one of the following command incantations to flash the firmware to your board:

## Heltech ESP32 LORA V2 - 915MHz, for USB-OTG with handset

~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-915-USB.heltec_v2.bin 0x8000 Ripple-915-USB.heltech_v2.partitions.bin 


## Heltech ESP32 LORA V2 - 915MHz, for Bluetooth with handset

~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-915-Bluetooth.heltec_v2_wifi_lora_32.bin 0x8000 Ripple-915-Bluetooth.heltech_v2.partitions.bin 

## TTGO ESP32 LORA - 915MHz, for USB-OTG with handset

~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_40m.bin 0x10000 Ripple-915-USB.heltec_wifi_lora_32.bin 0x8000 Ripple-915-USB.partitions.bin 


## TTGO ESP32 LORA - 915MHz, for Bluetooth with handset

~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_40m.bin 0x10000 Ripple-915-Bluetooth.heltec_wifi_lora_32.bin 0x8000 Ripple-915-Bluetooth.partitions.bin 

## Adafruit Feather M0 - 915MHz,  (only USB-OTG supported)

~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v Ripple-915-USB.feather_m0.bin -R 
