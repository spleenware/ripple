# ripple
Arduino Firmware for Ripple LoRa mesh

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

# Ver 4 firmware builds (with new key exchange design)

## Adafruit Feather M0

### GPS Tracker Node - 433 to 915MHz (configurable),  (USB-OTG)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleTrackerV4-USB-feather.bin -R 
```
## Seeeduino Xiao

### GPS Tracker Node - 433 to 915MHz (configursble), (USB-OTG)

```shell
~/Library/Arduino15/packages/Seeeduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleTrackerV4-USB-Xiao.bin -R 
```


# Ver 3 firmware builds (with 'commander' Low Power Mode support)

## Seeeduino Xiao

### Sensor Node - 433 to 915MHz (configurable),  (only USB-OTG supported)

```shell
~/Library/Arduino15/packages/Seeeduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleSensor-USB-Xiao.bin -R 
```

## Adafruit Feather M0

### Repeater OR Messenger - 433 to 915MHz (configurable),  (USB-OTG)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleV3-USB-feather.bin -R 
```

## TTGO V1.6 to V2.1 boards

### Messenger - 433 to 915MHz (configurable),  (Bluetooth Classic)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000  RippleV3-Bluetooth-TTGOV2.bin 0x8000 RippleV3-Bluetooth-TTGOV2.partitions.bin 
```

### Repeater OR Messenger - 433 to 915MHz (configurable),  (USB-OTG only)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoU~ART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 RippleV3-USB-TTGOV2.bin 0x8000 RippleV3-USB-TTGOV2.partitions.bin
```

# Ver 2 firmware builds (with 'commander' app support)

## Adafruit Feather M0

### Repeater OR Messenger - 433 to 915MHz (configurable),  (USB-OTG only)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v Ripple-USB.Feather_m0.bin -R 
```

### GPS Tracker Node - 433 to 915MHz (configurable),  (only USB-OTG supported)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleTracker-915-USB.feather_m0.bin -R 
```

### Sensor Node - 433 to 915MHz (configurable),  (only USB-OTG supported)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v RippleSensor-915-USB.feather_m0.bin -R 
```

## Sparkfun Pro RF

### Repeater OR Messenger - 433 to 915MHz (configurable),  (USB-OTG only)

```shell
~/Library/Arduino15/packages/arduino/tools/bossac/1.7.0-arduino3/bossac -i -d --port=cu.usbmodem14101 -U true -i -e -w -v Ripple-USB-Sparkfun-Pro.bin -R 
```

## TTGO/Heltech V1 boards

### Repeater OR Messenger - 433 to 915MHz (configurable),  (USB-OTG only)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-USB.TTGO-V1.bin 0x8000 Ripple-USB.TTGO-V1.partitions.bin 
```

### Messenger - 433 to 915MHz (configurable),  (Bluetooth LE)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-BLE.TTGO-V1.bin 0x8000 Ripple-BLE.TTGO-V1.partitions.bin 
```

## Heltech V2 boards

### Repeater OR Messenger - 433 to 915MHz (configurable),  (USB-OTG only)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-USB-heltech_v2.bin 0x8000 Ripple-USB-heltech_v2.partitions.bin
```

### Messenger - 433 to 915MHz (configurable),  (Bluetooth LE)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-BLE.Heltech-v2.bin 0x8000 Ripple-BLE.Heltech-v2.partitions.bin
```

### Messenger - 433 to 915MHz (configurable),  (Bluetooth Classic)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-915-Bluetooth.heltec_v2_wifi_lora_32.bin 0x8000 Ripple-915-Bluetooth.heltech_v2.partitions.bin
```

## Sparkfun Lora Gateway

### Repeater OR Messenger - 433 to 915MHz (configurable),  (USB-OTG only)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-USB-Sparkfun.bin 0x8000 Ripple-USB-Sparkfun.partitions.bin 
```

### Messenger - 433 to 915MHz (configurable),  (Bluetooth Classic)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-Bluetooth.Sparkfun.bin 0x8000 Ripple-Bluetooth.Sparkfun.partitions.bin 
```

## TTGO V1.6 to V2.1 boards

### Messenger - 433 to 915MHz (configurable),  (Bluetooth Classic)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-Bluetooth.TTGOV2.bin 0x8000 Ripple-Bluetooth.TTGOV2.partitions.bin 
```

### Messenger - 433 to 915MHz (configurable),  (Bluetooth LE)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-BLE.TTGOV2.bin 0x8000 Ripple-BLE.TTGOV2.partitions.bin 
```

### Repeater OR Messenger - 433 to 915MHz (configurable),  (USB-OTG only)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-USB.TTGOV2.bin 0x8000 Ripple-USB.TTGOV2.partitions.bin
```

### GeoPager Node - 433 to 915MHz (configurable), (only USB-OTG supported)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 Ripple-GeoPager-TTGOV2.bin 0x8000 Ripple-GeoPager-TTGOV2.partitions.bin 
```

# Ver 1 firmware builds (no longer supported)

## TTGO ESP32 LORA - 868MHz, for USB-OTG with handset

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_40m.bin 0x10000 Ripple-868-USB.heltec_wifi_lora_32.bin 0x8000 Ripple-868-USB.partitions.bin 
```

## TTGO ESP32 LORA - 915MHz, for USB-OTG with handset

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_40m.bin 0x10000 Ripple-915-USB.heltec_wifi_lora_32.bin 0x8000 Ripple-915-USB.partitions.bin 
```

## TTGO ESP32 LORA - 915MHz, for Bluetooth Classic with handset

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_40m.bin 0x10000 Ripple-915-Bluetooth.heltec_wifi_lora_32.bin 0x8000 Ripple-915-Bluetooth.partitions.bin 
```

## Heltech ESP32 LORA V2 - 433MHz, for USB-OTH with handset

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.ESP32test-ESP32SPP --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-433-USB.heltec_v2.bin 0x8000 Ripple-433-USB.partitions.bin 
```

## Heltech ESP32 LORA V2 - 433MHz, for Bluetooth Classic with handset

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.ESP32test-ESP32SPP --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-433-Bluetooth.heltec_v2.bin 0x8000 Ripple-433-Bluetooth.partitions.bin 
```

# Experimental builds (still with known issues)

## TTGO ESP32 LORA - 915MHz, for Bluetooth LE with handset

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_40m.bin 0x10000 Ripple-915-BLE.heltec_wifi_lora_32.bin 0x8000 Ripple-915-BLE.partitions.bin 
```shell

## Heltech ESP32 LORA V2 - 915MHz, for USB-OTG with handset

````shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 Ripple-915-USB.heltec_v2.bin 0x8000 Ripple-915-USB.heltech_v2.partitions.bin 
```

## GPS Tracker Node - TTGO T-Beam - 433 to 915MHz (configurable),  (only USB-OTG supported)

```shell
~/Library/Arduino15/packages/esp32/tools/esptool_py/2.6.1/esptool --chip esp32 --port /dev/cu.SLAB_USBtoUART --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/partitions/boot_app0.bin 0x1000 ~/Library/Arduino15/packages/esp32/hardware/esp32/1.0.2/tools/sdk/bin/bootloader_dio_80m.bin 0x10000 RippleTracker-915-USB.t-beam.bin 0x8000 RippleTracker-915-USB.t-beam.partitions.bin
```
