#include <stdio.h>

#include <fcntl.h>
#include <string.h>
#include "esp_check.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_openthread.h"
#include "esp_openthread_border_router.h"
#include "esp_openthread_types.h"

#include "esp_ot_ota_commands.h"
#include "esp_ot_wifi_cmd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_vfs_eventfd.h"
#include "esp_spiffs.h"
#include "esp_wifi.h"
#include "esp_zigbee_type.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_rcp_update.h"
#include "mdns.h"
#include "driver/uart.h"
#include "border_router_launch.h"
#include "esp_br_web.h"
#include "esp_radio_spinel.h"

#include "esp_vfs_dev.h"
#include "esp_vfs_usb_serial_jtag.h"
#include "driver/usb_serial_jtag.h"

#include "multi_pan_br.h"


#define ZB_TASK_PRIORITY 5
#define ZB_TASK_SIZE 4096


static const char *ZB_TAG = "ZB_GATEWAY";
static const char *OT_TAG = "OTBR";
static const char *HOSTNAME = "multi-pan BR";

static TaskHandle_t zbHandle;

extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");


/* Production configuration app data */
typedef struct zb_app_production_config_s {
    uint16_t version;
    uint16_t manuf_code;
    char manuf_name[16];
} app_production_config_t;

/*******************************************************************************
************************* ZigBee Config ****************************************
*****************************************************************************/


 /**********************************ZIGBEE**END****************************/

 

/*******************************************************************************
************************* OpenThread Config ***********************************
*****************************************************************************/


/**********************************OPENTHREAD**END****************************/

/*****************************************************************************/
/**
 *  @fn         void app_main( void )
 *  @brief      Program entry-point
 *  @param      None
 *  @retval     None
 *  @par
 *
 *  @note Main Loop
 *****************************************************************************/
void app_main (void )
{
    // Used eventfds:
    // * netif
    // * task queue
    // * border router
    // * zigbee gateway
    size_t max_eventfd = (e_EventList)_NUM_OF_EVENTS;

#if CONFIG_OPENTHREAD_RADIO_SPINEL_SPI
    // * SpiSpinelInterface (The Spi Spinel Interface needs an eventfd.)
    max_eventfd++;
#endif
#if CONFIG_OPENTHREAD_RADIO_TREL
    // * TREL reception (The Thread Radio Encapsulation Link needs an eventfd for reception.)
    max_eventfd++;
#endif

    esp_vfs_eventfd_config_t eventfd_config = {
        .max_fds = max_eventfd,
    };

}
