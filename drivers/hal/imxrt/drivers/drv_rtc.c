/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-15     Liuguang     the first version.
 * 2019-04-22     tyustli      add imxrt series support
 *
 */
#include <os_task.h>

#ifdef BSP_USING_RTC

#define LOG_TAG             "drv.rtc"
#include <drv_log.h>

#include "drv_rtc.h"
#include "fsl_snvs_hp.h"
#include <time.h>

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
#error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

static time_t get_timestamp(void)
{
    struct tm tm_new = {0};
    snvs_hp_rtc_datetime_t rtcDate = {0};

    SNVS_HP_RTC_GetDatetime(SNVS, &rtcDate);

    tm_new.tm_sec  = rtcDate.second;
    tm_new.tm_min  = rtcDate.minute;
    tm_new.tm_hour = rtcDate.hour;

    tm_new.tm_mday = rtcDate.day;
    tm_new.tm_mon  = rtcDate.month - 1;
    tm_new.tm_year = rtcDate.year - 1900;

    return mktime(&tm_new);
}

static int set_timestamp(time_t timestamp)
{
    struct tm *p_tm;
    snvs_hp_rtc_datetime_t rtcDate = {0};

    p_tm = localtime(&timestamp);

    rtcDate.second = p_tm->tm_sec ;
    rtcDate.minute = p_tm->tm_min ;
    rtcDate.hour   = p_tm->tm_hour;

    rtcDate.day    = p_tm->tm_mday;
    rtcDate.month  = p_tm->tm_mon  + 1;
    rtcDate.year   = p_tm->tm_year + 1900;

    if (SNVS_HP_RTC_SetDatetime(SNVS, &rtcDate) != kStatus_Success)
    {
        LOG_E("set rtc date time failed\n");
        return -OS_ERROR;
    }

    return OS_EOK;
}

static os_err_t imxrt_hp_rtc_init(os_device_t dev)
{
    snvs_hp_rtc_config_t snvsRtcConfig;

    SNVS_HP_RTC_GetDefaultConfig(&snvsRtcConfig);
    SNVS_HP_RTC_Init(SNVS, &snvsRtcConfig);

    return OS_EOK;
}

static os_err_t imxrt_hp_rtc_open(os_device_t dev, os_uint16_t oflag)
{
    SNVS_HP_RTC_StartTimer(SNVS);

    return OS_EOK;
}

static os_err_t imxrt_hp_rtc_close(os_device_t dev)
{
    SNVS_HP_RTC_StopTimer(SNVS);

    return OS_EOK;
}

static os_size_t imxrt_hp_rtc_read(os_device_t dev, os_off_t pos, void* buffer, os_size_t size)
{
    return OS_EOK;
}

static os_size_t imxrt_hp_rtc_write(os_device_t dev, os_off_t pos, const void* buffer, os_size_t size)
{
    return OS_EOK;
}

static os_err_t imxrt_hp_rtc_control(os_device_t dev, int cmd, void *args)
{
    OS_ASSERT(dev != OS_NULL);

    switch(cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
    {
        *(uint32_t *)args = get_timestamp();
    }
    break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        set_timestamp(*(time_t *)args);
    }
    break;

    default:
        return OS_EINVAL;
    }

    return OS_EOK;
}

static struct os_device device =
{
    .type    = OS_DEVICE_TYPE_RTC,
    .init    = imxrt_hp_rtc_init,
    .open    = imxrt_hp_rtc_open,
    .close   = imxrt_hp_rtc_close,
    .read    = imxrt_hp_rtc_read,
    .write   = imxrt_hp_rtc_write,
    .control = imxrt_hp_rtc_control,
};

int os_hw_rtc_init(void)
{
    os_err_t ret = OS_EOK;

    ret = os_device_register(&device, "rtc", RT_DEVICE_FLAG_RDWR);

    if(ret != OS_EOK)
    {
        LOG_E("rt device register failed %d\n", ret);
        return ret;
    }

    rt_device_open(&device, RT_DEVICE_OFLAG_RDWR);

    return OS_EOK;
}

INIT_DEVICE_EXPORT(os_hw_rtc_init);

#endif /* BSP_USING_RTC */