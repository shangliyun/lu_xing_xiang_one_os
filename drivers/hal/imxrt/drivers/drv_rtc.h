/**
 ***********************************************************************************************************************
 * Copyright (c) 2020, China Mobile Communications Group Co.,Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with 
 * the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 * @file        drv_rtc.c
 *
 * @brief       This file implements rtc driver for imxrt.
 *
 * @revision
 * Date         Author          Notes
 * 2020-09-01   OneOS Team      First Version
 ***********************************************************************************************************************
 */

#ifndef DRV_RTC_H__
#define DRV_RTC_H__

#include <os_device.h>
#include "peripherals.h"


#ifdef RTC_PERIPHERAL
struct nxp_rtc_info
{
    SNVS_Type *rtc_base;
    const snvs_hp_rtc_config_t *config;
};
#endif


#ifdef RTC_LP_PERIPHERAL
struct nxp_rtc_lp_info
{
    SNVS_Type *rtc_base;
    const snvs_lp_srtc_config_t *config;
};
#endif

int os_hw_rtc_init(void);

#endif
