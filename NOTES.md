# Todo List for multi-pan_br

## Config
* Rename project to `multi-pan_br`
* Update `partitions.csv`
* Update Kconfig.

## Merge files
* Combine `esp_ot_br.h` and `esp_zigbee_gateway.h` in to `multipan-border-router.h`

## RCP
### OpenThread: SPI
* Could change to UART and use pins available on Ethernet header.
### ZigBee: UART
* Uses default UART pins on the `esp32s3`

## Functions
* Disable RCP update.
* Enable ZigBee console
* Enable OpenThread Console

# Requirements
* HOST device must be `esp32s3` in order to have dual cores.

