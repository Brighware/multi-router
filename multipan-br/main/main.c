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

#define HOSTNAME CONFIG_MP_BR_HOSTNAME

static const char *TAG = "MULTIPAN_BR";

static TaskHandle_t zbHandle;

extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");


/* Production configuration app data */
typedef struct zb_app_production_config_s {
    uint16_t version;
    uint16_t manuf_code;
    char manuf_name[16];
} app_production_config_t;


static esp_err_t init_spiffs(void)
{
#if CONFIG_OPENTHREAD_BR_START_WEB
    esp_vfs_spiffs_conf_t web_server_conf = {
        .base_path = "/spiffs", .partition_label = "web_storage", .max_files = 10, .format_if_mount_failed = false};
    ESP_RETURN_ON_ERROR(esp_vfs_spiffs_register(&web_server_conf), TAG, "Failed to mount web storage");
#endif
    return ESP_OK;
}

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

    esp_vfs_eventfd_config_t eventfd_config = {
        .max_fds = max_eventfd,
    };

    esp_openthread_platform_config_t platform_config = {
        .radio_config = ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_OPENTHREAD_DEFAULT_HOST_CONFIG(),
        .port_config = ESP_OPENTHREAD_DEFAULT_PORT_CONFIG(),
    };

    ESP_ERROR_CHECK(esp_vfs_eventfd_register(&eventfd_config));

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(init_spiffs());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(mdns_init());
    ESP_ERROR_CHECK(mdns_hostname_set(HOSTNAME));

    
#if CONFIG_OPENTHREAD_BR_START_WEB
    esp_br_web_start("/spiffs");
#endif

launch_openthread_border_router(&openthread_config, TAG);

}
