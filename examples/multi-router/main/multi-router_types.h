#pragma once

typedef enum {
  NATIVE = 0,
  SPI,
  UART

} eMultiRouter_Radio;

#define OT_NATIVE   ((eMultiRouter_Radio)NATIVE)
#define OT_RCP_SPI  ((eMultiRouter_Radio)SPI)
#define OT_RCP_UART ((eMultiRouter_Radio)UART)
#define ZB_NATIVE   ((eMultiRouter_Radio)NATIVE)
#define ZB_RCP_SPI  ((eMultiRouter_Radio)SPI)
#define ZB_RCP_UART ((eMultiRouter_Radio)UART)

