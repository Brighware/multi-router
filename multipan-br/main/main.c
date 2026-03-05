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
#include "esp_coexist.h"
#include "mdns.h"
#include "driver/uart.h"
#include "border_router_launch.h"
#include "esp_br_web.h"
#include "esp_radio_spinel.h"

#include "esp_vfs_dev.h"
#include "esp_vfs_usb_serial_jtag.h"
#include "driver/usb_serial_jtag.h"

#include "esp_ot_br.h"
#include "esp_zigbee_gateway.h"

#define loop() while(1)

/** TODO: Merge `esp_ot_br.c` and `esp_zigbee_gateway.c` in to this file.  */

static const char *ZB_TAG = "ZB_GATEWAY";
static const char *OT_TAG = "OTBR";

/**
* ZigBee Config ****
 */
/* Production configuration app data */
typedef struct zb_app_production_config_s {
    uint16_t version;
    uint16_t manuf_code;
    char manuf_name[16];
} app_production_config_t;


/**
* OpenThread Config ****
 */
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
    TaskHandle_t zbHandle = esp_zigbee_gateway();
    TaskHandle_t otHandle = esp_ot_br();
    loop(){

    }
    vTaskDelete(zbHandle);
    vTaskDelete(otHandle);
}
