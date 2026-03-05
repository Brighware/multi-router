# Notes for multi-pan_br
## Todo
### Config
* Rename project to `multi-pan_br`
* Update `partitions.csv`
* Update Kconfig.

### Merge files
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

## Events
* netif
* otbr
* zbgw
* nvs flash

## Requirements
* HOST device must be `esp32s3` in order to have dual cores.


## Sources
[esp_ot_br.c](https://github.com/espressif/esp-thread-br/blob/main/examples/basic_thread_border_router/main/esp_ot_br.c)
[esp_zigbee_gateway.c](https://github.com/espressif/esp-zigbee-sdk/blob/main/examples/esp_zigbee_gateway/main/esp_zigbee_gateway.c)
[thread_border_router.c](https://github.com/espressif/esp-thread-br/blob/main/examples/common/thread_border_router/src/border_router_launch.c)
