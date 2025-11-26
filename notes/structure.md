# Structure
`Thread BR + ZB Gateway`

## Targets
* ESP3-H2 (RCP)
* ESP32-S3 (Main)

## From Thread BR
* RCP Update
* Web interface
* Auto-start
* Openthread console
* Openthread configuration
* SPI RCP setup

## From ZB Gateway
* Zigbee stack
* Zboss stack
* ZigBee Console

## Radio Co-processor
* Communication -> SPI

## Random Thoughts & Ideas
* Maybe Add in another ieee802.15.4 device as the dedicated ZigBee radio?
### A CC2530 as a RCP or an ESP32-H2 as an NCP.
#### CC2530 RCP
* Connect CC2530 -> UART
* Connect ESP32H2 -> SPI

#### ESP32-H2 NCP
* Connect ZB NCP -> SPI
* Connect OT RCP -> SPI
