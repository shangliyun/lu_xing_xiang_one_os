/**
 ***********************************************************************************************************************
 * Copyright (c)2020, China Mobile Communications Group Co.,Ltd.
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
 * @file        onepos_interface.h
 *
 * @brief       control interface of onepos
 *
 * Date         Author          Notes
 * 2020-07-08   OneOs Team      First Version
 ***********************************************************************************************************************
 */
#include <stdio.h>
#include <string.h>
#include <os_kernel.h>
#include <sys/time.h>
#include "onepos_interface.h"

#define DBG_EXT_TAG "onepos"
#define DBG_EXT_LVL DBG_EXT_DEBUG
#include <os_dbg_ext.h>

static os_uint32_t        onepos_pos_err  = 0;
static os_uint16_t        onepos_interval = ONEPOS_DEFAULT_INTERVAL;
static onepos_serv_sta_t  onepos_sta      = ONEPOS_CLOSING;
static onepos_serv_type_t onepos_type     = (onepos_serv_type_t)ONEPOS_DEFAULT_SEV_TYPE;

static os_timer_t *onepos_timer = OS_NULL;
static os_sem_t *  onepos_sem   = OS_NULL;
static os_sem_t *  onepos_lock  = OS_NULL;
static os_task_t * onepos_task  = OS_NULL;

static onepos_pos_t g_sys_onepos_pos = {
    0,
};

static void onepos_lock_func(void)
{
    if (ONEPOS_RUNING == onepos_get_server_sta())
        os_sem_wait(onepos_lock, OS_IPC_WAITING_FOREVER);
}
static void onepos_unlock_func(void)
{
    if (ONEPOS_RUNING == onepos_get_server_sta())
        os_sem_post(onepos_lock);
}

/**
 ***********************************************************************************************************************
 * @brief           onepos timers call back func
 *
 * @param[in]       parameter       input param(no using)
 ***********************************************************************************************************************
 */
static void onepos_timer_func(void *parameter)
{
    os_sem_post(onepos_sem);
}

/**
 ***********************************************************************************************************************
 * @brief           get onepos server status
 *
 * @return          onepos server is runing or not
 * @retval          ONEPOS_RUNING        onepos server is runing
 * @retval          ONEPOS_CLOSING       onepos server is closed
 ***********************************************************************************************************************
 */
onepos_serv_sta_t onepos_get_server_sta(void)
{
    onepos_serv_sta_t sta = ONEPOS_CLOSING;
    sta                   = onepos_sta;
    return sta;
}
/**
 ***********************************************************************************************************************
 * @brief           set onepos server status
 *
 * @param[in]       sta                 server status to set
                    ONEPOS_RUNING       set server runing
                    ONEPOS_CLOSING      set server closing
 ***********************************************************************************************************************
 */
static os_bool_t onepos_set_server_sta(onepos_serv_sta_t sta)
{
    os_bool_t ret = OS_TRUE;

    if (ONEPOS_CLOSING == sta || (sta > ONEPOS_CLOSING && sta < ONEPOS_MAX_STA))
    {
        onepos_sta = sta;
        if (ONEPOS_WILL_CLOSE != sta)
            onepos_rep_device_sta();
    }
    else
        ret = OS_FALSE;

    return ret;
}

/**
 ***********************************************************************************************************************
 * @brief           get onepos server type
 *
 * @return          onepos server is runing or not
 * @retval          ONEPOS_SIG_RUN        onepos server is circulation
 * @retval          ONEPOS_CIRC_RUN       onepos server is single
 ***********************************************************************************************************************
 */
onepos_serv_type_t onepos_get_server_type(void)
{
    onepos_serv_type_t type = ONEPOS_INVAILD_TYPE;
    type                    = onepos_type;
    return type;
}

/**
 ***********************************************************************************************************************
 * @brief           set onepos server type
 *
 * @param[in]       type                  server type to set
                    ONEPOS_SIG_RUN        onepos server is circulation
                    ONEPOS_CIRC_RUN       onepos server is single
 ***********************************************************************************************************************
 */
os_bool_t onepos_set_server_type(onepos_serv_type_t type)
{
    os_bool_t          ret      = OS_TRUE;
    onepos_serv_type_t sev_type = type;

    if (sev_type > ONEPOS_INVAILD_TYPE && sev_type < ONEPOS_MAX_TYPE)
    {
        if (ONEPOS_CLOSING == onepos_get_server_sta())
        {
            onepos_type = sev_type;
            onepos_rep_device_sta();
        }
        else
        {
            LOG_EXT_I("only support set position server type while the server closing");
            ret = OS_TRUE;
        }
    }
    else
    {
        LOG_EXT_I("set position server type is error,  should be(0/1)");
        ret = OS_FALSE;
    }
    return ret;
}

/**
 ***********************************************************************************************************************
 * @brief           get position error
 *
 * @return           position error
 ***********************************************************************************************************************
 */
os_uint32_t onepos_get_sev_pos_err(void)
{
    return onepos_pos_err;
}

/**
 ***********************************************************************************************************************
 * @brief           set position error
 *
 * @param[in]       pos_err            position error to set
 ***********************************************************************************************************************
 */
os_bool_t onepos_set_pos_err(os_uint32_t pos_err)
{
    onepos_pos_err = pos_err;
    onepos_rep_device_sta();
    return OS_TRUE;
}

/**
 ***********************************************************************************************************************
 * @brief           get position interval of currently used
 *
 * @return          position interval
 ***********************************************************************************************************************
 */
os_uint32_t onepos_get_pos_interval(void)
{
    os_uint16_t interval = 0;
    interval             = onepos_interval;
    return interval;
}

/**
 ***********************************************************************************************************************
 * @brief           set position interval
 *
 * @param[in]       interval            position interval to set
 ***********************************************************************************************************************
 */

os_bool_t onepos_set_pos_interval(os_int32_t interval)
{
    os_tick_t ticks = 0;

    if (ONEPOS_MIN_INTERVAL <= interval && ONEPOS_MAX_INTERVAL >= interval)
    {
        if (interval == onepos_interval)
        {
            LOG_EXT_I("The interval is already is %ds", onepos_interval);
            return OS_TRUE;
        }

        if (ONEPOS_RUNING == onepos_get_server_sta())
        {
            onepos_lock_func();
            onepos_interval = interval;
            onepos_rep_device_sta();
            ticks = OS_TICK_PER_SECOND * onepos_interval;
            os_timer_stop(onepos_timer);
            os_timer_control(onepos_timer, OS_TIMER_CTRL_SET_TIME, &ticks);
            os_timer_start(onepos_timer);
            onepos_unlock_func();
        }
        else
        {
            onepos_interval = interval;
        }
    }
    else
    {
        LOG_EXT_I("set position interval error, should be(%us ~ %us)", ONEPOS_MIN_INTERVAL, OS_UINT16_MAX);
        return OS_FALSE;
    }
    return OS_TRUE;
}

static os_bool_t copy_position(onepos_pos_t *dst_info, onepos_pos_t *src_info)
{
    os_bool_t ret = OS_FALSE;
    if (dst_info && src_info)
    {
        memcpy(dst_info, src_info, sizeof(onepos_pos_t));
        ret = OS_TRUE;
    }
    else
    {
        LOG_EXT_E("wifi_src_info is NULL");
    }

    return ret;
}

void onepos_info_print(onepos_pos_t *src_info)
{
    struct tm TM = {0};

    if (src_info)
    {
        gmtime_r((time_t *)&src_info->time, &TM);
        printf("$OPPOS %04d/%02d/%02d %02d:%02d:%02d %-20lf %-20lf\n",
               TM.tm_year + 1900,
               TM.tm_mon + 1,
               TM.tm_mday,
               TM.tm_hour + 8,
               TM.tm_min,
               TM.tm_sec,
               src_info->lat_coordinate,
               src_info->lon_coordinate);
    }
    else
    {
        LOG_EXT_E("src_info is NULL!");
    }
}

/**
 ***********************************************************************************************************************
 * @brief           onepos server exit
 ***********************************************************************************************************************
 */
static void onepos_exit(void)
{
    onepos_deinit();
    os_sem_destroy(onepos_lock);
    os_timer_destroy(onepos_timer);
    os_sem_destroy(onepos_sem);
    os_task_destroy(onepos_task);
}

/**
 ***********************************************************************************************************************
 * @brief           onepos task function
 *
 * @param[in]       parameter       input param(no using)
 ***********************************************************************************************************************
 */
static void onepos_circ_run_task_func(void *parameter)
{
    const os_uint16_t sem_value = 0;
    onepos_pos_t      curr_pos_info;

    if (!onepos_init())
    {
        LOG_EXT_I("onepos init failed, will exit serv");
        onepos_set_server_sta(ONEPOS_CLOSING);
        onepos_exit();
    }

    /* report once status of device */
    onepos_rep_device_sta();

    while (1)
    {
        /* rec stop cmd, will stop */
        if (ONEPOS_WILL_CLOSE == onepos_get_server_sta())
        {
            onepos_set_server_sta(ONEPOS_CLOSING);
            onepos_exit();
            LOG_EXT_D("exit serv succ");
        }

        memset(&curr_pos_info, 0, sizeof(onepos_pos_t));

        os_sem_wait(onepos_sem, OS_IPC_WAITING_FOREVER);
        os_sem_control(onepos_sem, OS_IPC_CMD_RESET, (void *)&sem_value);
        os_timer_start(onepos_timer);

        LOG_EXT_D("start once position");

        if (onepos_get_dev_sta())
        {
            if (!onepos_mqtt_is_connected())
            {
                onepos_mqtt_disconnect();
                if (OS_EOK != onepos_mqtt_connect())
                {
                    LOG_EXT_I("onepos mqtt re_connect error, will delay %d ms\n", ONEPOS_WAIT_MQTT_READY);
                    os_task_mdelay(ONEPOS_WAIT_MQTT_READY);
                    continue;
                }
            }
            if (onepos_location(&curr_pos_info))
            {
#if defined(ONEPOS_DEVICE_REC_POS_INFO)
                onepos_lock_func();
                copy_position(&g_sys_onepos_pos, &curr_pos_info);
                onepos_unlock_func();
#if defined(ONEPOS_DEBUG)
                onepos_info_print(&curr_pos_info);
#endif
#endif
            }
            else
            {
                onepos_mqtt_disconnect();
                LOG_EXT_E("this location is error!");
            }
        }
        else
        {
            LOG_EXT_E("onepos device is not ready!");
        }
    }
}

/**
 ***********************************************************************************************************************
 * @brief           onepos server circularly run function of task
 ***********************************************************************************************************************
 */
static void onepos_circ_run_init(void)
{
    if (OS_NULL != os_task_find("ONEPOS"))
    {
        LOG_EXT_I("Pls start server after last server stop.");
        return;
    }

    onepos_task = os_task_create("ONEPOS",
                                 onepos_circ_run_task_func,
                                 OS_NULL,
                                 ONEPOS_TASK_STACK_SIZE,
                                 ONEPOS_TASK_PRIORITY,
                                 ONEPOS_TASK_TIMESLICE);

    onepos_sem = os_sem_create("onepos_sem", 1, OS_IPC_FLAG_FIFO);
    if (onepos_sem == OS_NULL)
    {
        LOG_EXT_D(DBG_EXT_TAG, "create semaphore failed.\n");
        return;
    }

    onepos_lock = os_sem_create("onepos_lock", 1, OS_IPC_FLAG_FIFO);
    if (onepos_lock == OS_NULL)
    {
        LOG_EXT_D(DBG_EXT_TAG, "creat semaphore failed.\n");
        return;
    }

    onepos_timer = os_timer_create("onepos_timer",
                                   onepos_timer_func,
                                   OS_NULL,
                                   (OS_TICK_PER_SECOND * onepos_get_pos_interval()),
                                   OS_TIMER_FLAG_ONE_SHOT);

    if (onepos_timer == OS_NULL)
    {
        LOG_EXT_D(DBG_EXT_TAG, "create timer failed.\n");
        return;
    }

    /* start server */
    if (onepos_task != OS_NULL)
    {
        onepos_set_server_sta(ONEPOS_RUNING);

        /* start timer for period timing */
        os_timer_start(onepos_timer);
        os_task_startup(onepos_task);
    }
}

/**
 ***********************************************************************************************************************
 * @brief           onepos run once
 ***********************************************************************************************************************
 */
static void onepos_single_run(void)
{
    onepos_pos_t curr_pos_info;
    onepos_set_server_sta(ONEPOS_SIG_RUNING);

    memset(&curr_pos_info, 0, sizeof(onepos_pos_t));

    if (!onepos_init())
    {
        LOG_EXT_I("onepos init failed, will return");
        goto exit_sevr;
    }

    /* report once status of device */
    onepos_rep_device_sta();

    /* check device status */
    if (onepos_get_dev_sta())
    {
        if (onepos_mqtt_is_connected())
        {
            if (onepos_location(&curr_pos_info))
            {
#if defined(ONEPOS_DEVICE_REC_POS_INFO)
                copy_position(&g_sys_onepos_pos, &curr_pos_info);
#ifdef ONEPOS_DEBUG
                onepos_info_print(&curr_pos_info);
#endif
#endif
            }
            else
            {
                LOG_EXT_E("this location is error!");
            }
        }
        else
        {
            LOG_EXT_E("onepos mqtt is not connect!");
        }
    }
    else
    {
        LOG_EXT_E("onepos device is not ready!");
    }

exit_sevr:
    onepos_set_server_sta(ONEPOS_CLOSING);
    onepos_deinit();

    return;
}

/**
 ***********************************************************************************************************************
 * @brief           start onepos server
 ***********************************************************************************************************************
 */
void onepos_start_server(void)
{
    if (ONEPOS_CLOSING == onepos_get_server_sta())
    {
        if (ONEPOS_SIG_RUN == onepos_get_server_type())
        {
            onepos_single_run();
        }
        else
        {
            onepos_circ_run_init();
        }
    }
}

/**
 ***********************************************************************************************************************
 * @brief           stop onepos server
 ***********************************************************************************************************************
 */
void onepos_stop_server(void)
{
    if (ONEPOS_RUNING == onepos_get_server_sta())
        onepos_set_server_sta(ONEPOS_WILL_CLOSE);
}

/**
 ***********************************************************************************************************************
 * @brief           get the lateset position of system
 *
 * @param[in]       src_info        save position data
 *
 * @return          os_bool_t       get position succ or fail
 * @retval          OS_FALSE        get failed
 * @retval          OS_TRUE         get successful
 ***********************************************************************************************************************
 */
os_bool_t onepos_get_latest_position(onepos_pos_t *src_info)
{
    os_bool_t         ret  = OS_FALSE;

    if (src_info)
    {
        onepos_lock_func();
        ret = copy_position(src_info, &g_sys_onepos_pos);
        onepos_unlock_func();
    }
    else
    {
        LOG_EXT_E("src_info is NULL!");
        ret = OS_FALSE;
    }

    return ret;
}
