#ifndef __MULTI_ROUTER_H_USED__
#define __MULTI_ROUTER_H_USED__

#pragma once

#include "multi-router_types.h"

/* OpenThread */
#include "esp_openthread_types.h"


/* ZigBee */
#include "esp_err.h"
#include "esp_zigbee_core.h"
#include "esp_zigbee_console.h"

/* OpenThread Configuration */
#define RCP_FIRMWARE_DIR "/spiffs/ot_rcp"

/* Zigbee Configuration */
#define MAX_CHILDREN                    10          /* the max amount of connected devices */
#define INSTALLCODE_POLICY_ENABLE       false       /* enable the install code policy for security */
#define ESP_ZB_PRIMARY_CHANNEL_MASK     (1l << 13)  /* Zigbee primary channel mask use in the example */
#define ESP_ZB_GATEWAY_ENDPOINT         1           /* Gateway endpoint identifier */
#define APP_PROD_CFG_CURRENT_VERSION    0x0001      /* Production configuration version */
#define RCP_VERSION_MAX_SIZE            80
#define HOST_RESET_PIN_TO_RCP_RESET     CONFIG_PIN_TO_RCP_RESET
#define HOST_BOOT_PIN_TO_RCP_BOOT       CONFIG_PIN_TO_RCP_BOOT
#define HOST_RX_PIN_TO_RCP_TX           CONFIG_PIN_TO_RCP_TX
#define HOST_TX_PIN_TO_RCP_RX           CONFIG_PIN_TO_RCP_RX

/* Custom */
#define MULTIROUTER_OT_RADIO                   OT_RCP_SPI
#define MULTIROUTER_ZB_RADIO                   ZB_RCP_UART

/* Basic manufacturer information */
#define ESP_MANUFACTURER_NAME "\x09""BRIGHWARE"      /* Customized manufacturer name */
#define ESP_MODEL_IDENTIFIER "\x07""WINKHAUS-ZB" /* Customized model identifier */

#define ESP_ZB_ZC_CONFIG()                                                              \
    {                                                                                   \
        .esp_zb_role = ESP_ZB_DEVICE_TYPE_COORDINATOR,                                  \
        .install_code_policy = INSTALLCODE_POLICY_ENABLE,                               \
        .nwk_cfg.zczr_cfg = {                                                           \
            .max_children = MAX_CHILDREN,                                               \
        },                                                                              \
    }

/** DEFAULT RADIO CONFIG   */
#if CONFIG_OPENTHREAD_RADIO_SPINEL_UART
#define ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG()              \
    {                                                      \
        .radio_mode = RADIO_MODE_UART_RCP,                 \
        .radio_uart_config = {                             \
            .port = 1,                                     \
            .uart_config =                                 \
                {                                          \
                    .baud_rate = 460800,                   \
                    .data_bits = UART_DATA_8_BITS,         \
                    .parity = UART_PARITY_DISABLE,         \
                    .stop_bits = UART_STOP_BITS_1,         \
                    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, \
                    .rx_flow_ctrl_thresh = 0,              \
                    .source_clk = UART_SCLK_DEFAULT,       \
                },                                         \
            .rx_pin = CONFIG_PIN_TO_RCP_TX,                \
            .tx_pin = CONFIG_PIN_TO_RCP_RX,                \
        },                                                 \
    }
#else
#define ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG()              \
    {                                                      \
        .radio_mode = RADIO_MODE_SPI_RCP,                  \
        .radio_spi_config = {                              \
            .host_device = SPI2_HOST,                      \
            .dma_channel = 2,                              \
            .spi_interface =                               \
                {                                          \
                    .mosi_io_num = CONFIG_PIN_TO_RCP_MOSI, \
                    .miso_io_num = CONFIG_PIN_TO_RCP_MISO, \
                    .sclk_io_num = CONFIG_PIN_TO_RCP_SCLK, \
                    .quadwp_io_num = -1,                   \
                    .quadhd_io_num = -1,                   \
                },                                         \
            .spi_device =                                  \
                {                                          \
                    .cs_ena_pretrans = 2,                  \
                    .input_delay_ns = 100,                 \
                    .mode = 0,                             \
                    .clock_speed_hz = 2500 * 1000,         \
                    .spics_io_num = CONFIG_PIN_TO_RCP_CS,  \
                    .queue_size = 5,                       \
                },                                         \
                 .intr_pin = CONFIG_PIN_TO_RCP_BOOT,       \
        },                                                 \
    }
#endif // CONFIG_OPENTHREAD_RADIO_SPINEL_UART OR  CONFIG_OPENTHREAD_RADIO_SPINEL_SPI
#if CONFIG_AUTO_UPDATE_RCP

#if defined(CONFIG_ESP_BR_H2_TARGET)
#define ESP_BR_RCP_TARGET_ID ESP32H2_CHIP
#elif defined(CONFIG_ESP_BR_C6_TARGET)
#define ESP_BR_RCP_TARGET_ID ESP32C6_CHIP
#else
#error RCP target type not supported.
#endif
#define ESP_OPENTHREAD_RCP_UPDATE_CONFIG()                                                                   \
    {                                                                                                        \
        .rcp_type = RCP_TYPE_UART, .uart_rx_pin = CONFIG_PIN_TO_RCP_TX, .uart_tx_pin = CONFIG_PIN_TO_RCP_RX, \
        .uart_port = 1, .uart_baudrate = 115200, .reset_pin = CONFIG_PIN_TO_RCP_RESET,                       \
        .boot_pin = CONFIG_PIN_TO_RCP_BOOT, .update_baudrate = 460800,                                       \
        .firmware_dir = "/" CONFIG_RCP_PARTITION_NAME "/ot_rcp", .target_chip = ESP_BR_RCP_TARGET_ID         \
    }
#else
#define ESP_OPENTHREAD_RCP_UPDATE_CONFIG() \
    {                                      \
        0                                  \
    }
#endif
#if CONFIG_OPENTHREAD_CONSOLE_TYPE_UART
#define ESP_OPENTHREAD_DEFAULT_HOST_CONFIG()                   \
    {                                                          \
        .host_connection_mode = HOST_CONNECTION_MODE_CLI_UART, \
        .host_uart_config = {                                  \
            .port = 0,                                         \
            .uart_config =                                     \
                {                                              \
                    .baud_rate = 115200,                       \
                    .data_bits = UART_DATA_8_BITS,             \
                    .parity = UART_PARITY_DISABLE,             \
                    .stop_bits = UART_STOP_BITS_1,             \
                    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,     \
                    .rx_flow_ctrl_thresh = 0,                  \
                    .source_clk = UART_SCLK_DEFAULT,           \
                },                                             \
            .rx_pin = UART_PIN_NO_CHANGE,                      \
            .tx_pin = UART_PIN_NO_CHANGE,                      \
        },                                                     \
    }
#elif CONFIG_OPENTHREAD_CONSOLE_TYPE_USB_SERIAL_JTAG
#define ESP_OPENTHREAD_DEFAULT_HOST_CONFIG()                        \
    {                                                               \
        .host_connection_mode = HOST_CONNECTION_MODE_CLI_USB,       \
        .host_usb_config = USB_SERIAL_JTAG_DRIVER_CONFIG_DEFAULT(), \
    }
#endif

#define ESP_OPENTHREAD_DEFAULT_PORT_CONFIG()                                            \
    {                                                                                   \
        .storage_partition_name = "nvs", .netif_queue_size = 10, .task_queue_size = 10, \
    }

#if CONFIG_EXTERNAL_COEX_ENABLE
#if CONFIG_EXTERNAL_COEX_WIRE_TYPE == EXTERNAL_COEXIST_WIRE_1
#define ESP_OPENTHREAD_DEFAULT_EXTERNAL_COEX_CONFIG() \
    {                                                 \
        .request = CONFIG_EXTERNAL_COEX_REQUEST_PIN,  \
    }
#elif CONFIG_EXTERNAL_COEX_WIRE_TYPE == EXTERNAL_COEXIST_WIRE_2
#define ESP_OPENTHREAD_DEFAULT_EXTERNAL_COEX_CONFIG()                                         \
    {                                                                                         \
        .request = CONFIG_EXTERNAL_COEX_REQUEST_PIN, .grant = CONFIG_EXTERNAL_COEX_GRANT_PIN, \
    }
#elif CONFIG_EXTERNAL_COEX_WIRE_TYPE == EXTERNAL_COEXIST_WIRE_3
#define ESP_OPENTHREAD_DEFAULT_EXTERNAL_COEX_CONFIG()                                               \
    {                                                                                               \
        .request = CONFIG_EXTERNAL_COEX_REQUEST_PIN, .priority = CONFIG_EXTERNAL_COEX_PRIORITY_PIN, \
        .grant = CONFIG_EXTERNAL_COEX_GRANT_PIN,                                                    \
    }
#elif CONFIG_EXTERNAL_COEX_WIRE_TYPE == EXTERNAL_COEXIST_WIRE_4
#define ESP_OPENTHREAD_DEFAULT_EXTERNAL_COEX_CONFIG()                                               \
    {                                                                                               \
        .request = CONFIG_EXTERNAL_COEX_REQUEST_PIN, .priority = CONFIG_EXTERNAL_COEX_PRIORITY_PIN, \
        .grant = CONFIG_EXTERNAL_COEX_GRANT_PIN, .tx_line = CONFIG_EXTERNAL_COEX_TX_LINE_PIN,       \
    }
#endif
#endif // CONFIG_EXTERNAL_COEX_ENABLE

#define ESP_ZB_DEFAULT_RADIO_CONFIG   ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG
#define ZB_RADIO_MODE_UART_RCP        RADIO_MODE_UART_RCP
#define ZB_RADIO_MODE_NATIVE          RADIO_MODE_SPI_RCP
#define ESP_ZB_RCP_UPDATE CONFIG      ESP_OPENTHREAD_RCP_UPDATE_CONFIG


#define ESP_ZB_DEFAULT_HOST_CONFIG()                            \
    {                                                           \
        .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,   \
    }
#endif /* __MULTI-ROUTER_H_USED__ */
