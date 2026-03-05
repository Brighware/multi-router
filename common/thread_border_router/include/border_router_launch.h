/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 */

#ifndef __BORDER_ROUTER_LAUNCH_H_USED__
#define __BORDER_ROUTER_LAUNCH_H_USED__

#ifdef __cplusplus
extern "C" {
#endif
#include "esp_openthread.h"
#include "esp_openthread_border_router.h"

void launch_openthread_border_router(const esp_openthread_config_t *config,
                                      const char *esp_ot_task_tag);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif