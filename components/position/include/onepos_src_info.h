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
 * @file        onepos_src_info.h
 *
 * @revision
 * Date         Author          Notes
 * 2020-07-08   OneOs Team      First Version
 ***********************************************************************************************************************
 */
#ifndef __ONEPOS_SRC_INFO_H__
#define __ONEPOS_SRC_INFO_H__

#include <os_types.h>
#include <os_stddef.h>
#include <os_errno.h>
#include "cJSON.h"
#include <mo_api.h>
/**
 ***********************************************************************************************************************
 * @def         ONEPOS_MQTT_VERSION
 *
 * @brief       mqtt protocol version
 *
 * @param       3       3 = version 3.1
 * @param       4       4 = version 3.1.1
 ***********************************************************************************************************************
 */
#define ONEPOS_MQTT_VERSION 4
/**
 ***********************************************************************************************************************
 * @def         ONEPOS_PLATFORM_ADDR
 *
 * @brief       onepos mqtt server address
 ***********************************************************************************************************************
 */
#define ONEPOS_PLATFORM_ADDR "218.201.45.140"
/**
 ***********************************************************************************************************************
 * @def         ONEPOS_PLATFORM_POST
 *
 * @brief       onepos mqtt server port
 ***********************************************************************************************************************
 */
#define ONEPOS_PLATFORM_PORT 11883
/**
 ***********************************************************************************************************************
 * @def         ONEPOS_PLATFORM_COMM_TIMEOUT
 *
 * @brief       Communication timeout with the onepos platform(unit : millsecond)
 ***********************************************************************************************************************
 */
#define ONEPOS_PLATFORM_COMM_TIMEOUT 3000
/**
 ***********************************************************************************************************************
 * @def         ONEPOS_MQTT_COMM_ALIVE_TIME
 * @brief       keep alive time while mqtt communication
 ***********************************************************************************************************************
 */
#define ONEPOS_MQTT_COMM_ALIVE_TIME 50u
/**
 ***********************************************************************************************************************
 * @def         ONEPOS_MQTT_COMM_QOS
 *
 * @brief       Quality of Service while mqtt communication
 *
 * @param       QOS0       At most once
 * @param       QOS1       At least once
 * @param       QOS2       Once and only once
 ***********************************************************************************************************************
 */

/**
 ***********************************************************************************************************************
 * @def         ONEPOS_MIN_INTERVAL
 *
 * @brief       onepos support the minimum interval
 ***********************************************************************************************************************
 */
#define ONEPOS_MIN_INTERVAL 3    // s
#define ONEPOS_MAX_INTERVAL OS_UINT16_MAX

#define ONEPOS_MQTT_COMM_QOS QOS0

#if defined(ONEPOS_DEVICE_ID) && defined(ONEPOS_PASSWORD)
#define ONEPOS_DEVICE_ID_LEN            20
#define ONEPOS_PASSWORD_LEN             32
#define ONEPOS_CLIENT_ID_LEN            ONEPOS_DEVICE_ID_LEN + 15
#define ONEPOS_MQTT_TOPIC_STRLEN 50

/**
 ***********************************************************************************************************************
 * @def         ONEPOS_MQTT_CLIENT_ID_SUFF
 *
 * @brief       MQTT Client ID suffix
 ***********************************************************************************************************************
 */
#define ONEPOS_MQTT_CLIENT_ID_SUFF "@md5@1599644924"

/**
 ***********************************************************************************************************************
 * @def         ONEPOS_MQTT_USER_NAME
 *
 * @brief       MQTT Client User Name
 ***********************************************************************************************************************
 */
#define ONEPOS_MQTT_USER_NAME ONEPOS_DEVICE_ID
/**
 ***********************************************************************************************************************
 * @def         ONEPOS_MQTT_PASSWD
 *
 * @brief       MQTT Client Password
 ***********************************************************************************************************************
 */
#define ONEPOS_MQTT_PASSWD ONEPOS_PASSWORD

/**
 ***********************************************************************************************************************
 * @def         ONEPOS_TOPIC_PRE
 *
 * @brief       onepos position topic prefix
 ***********************************************************************************************************************
 */
#define ONEPOS_TOPIC_PRE "pos/"

/**
 ***********************************************************************************************************************
 * @def         ONEPOS_INFO_PUB_TOPIC_SUFF
 *
 * @brief       onepos position message publish topic suffix(send)
 ***********************************************************************************************************************
 */
#define ONEPOS_INFO_PUB_TOPIC_SUFF "/lbs/post"

/**
 ***********************************************************************************************************************
 * @def         ONEPOS_SUB_TOPIC_SUFF
 *
 * @brief       onepos position result subcribe topic suffix(receive)
 ***********************************************************************************************************************
 */
#define ONEPOS_SUB_TOPIC_SUFF "/lbs/post_reply"

/**
 ***********************************************************************************************************************
 * @def         ONEPOS_CONIFG_PUB_TOPIC_SUFF
 *
 * @brief       onepos config message publish topic suffix(send)
 ***********************************************************************************************************************
 */
#define ONEPOS_CONIFG_PUB_TOPIC_SUFF "/config/set_reply"

/**
 ***********************************************************************************************************************
 * @def         ONEPOS_CONFIG_SUB_TOPIC_SUFF
 *
 * @brief       onepos config message subscibe topic suffix(receive)
 ***********************************************************************************************************************
 */
#define ONEPOS_CONFIG_SUB_TOPIC_SUFF "/config/set"

#else
#error "Pls setting the usrname and password in ENV tools."
#endif

/**
 ***********************************************************************************************************************
 * @enum        onepos_conf_err_code_t
 *
 * @brief       onepos config error code
 ***********************************************************************************************************************
 */
typedef enum
{
    ONEPOS_CONFIG_SUCC = 0,
    ONEPOS_CONFIG_FAIL = 10001
} onepos_conf_err_code_t;

/**
 ***********************************************************************************************************************
 * @enum        onepos_comm_err_code_t
 *
 * @brief       onepos Supported Communication Error Code
 ***********************************************************************************************************************
 */
typedef enum
{
    ONEPOS_COMM_SUCC     = 0,
    ONEPOS_NULL_POSITION = 10000,
    ONEPOS_COMM_FAIL     = 10010,
    ONEPOS_OVER_LIMIT    = 11000,
    /* Add others communication error code */
} onepos_comm_err_code_t;

#define ONEPOS_DEV_WAITE_READY_TIME   1000    // ms
#define ONEPOS_WAIT_PUB_MSG_TIMEOUT   500    // ms
#define ONEPOS_WAIT_MQTT_COMM_BUSY    20    // ms
#define ONEPOS_WAIT_DEVICE_INTI_READY 1000    // ms

#define ONEPOS_WAIT_MQTT_READY 2000    // ms
#define ONEPOS_LAT_LON_STR_LEN 30    // bytes

#define ONEPOS_TASK_PRIORITY                25
#define ONEPOS_TASK_TIMESLICE               10
#define ONEPOS_TASK_STACK_SIZE              4096
#define ONEPOS_WAIT_PUB_MSG_TASK_STACK_SIZE 2048

#define ONEPOS_MIN_LAT    0.0f
#define ONEPOS_MAX_LAT    90.0f
#define ONEPOS_MIN_LON    0.0f
#define ONEPOS_MAX_LON    180.0f
#define IS_VAILD_LAT(lat) (lat >= ONEPOS_MIN_LAT && lat <= ONEPOS_MAX_LAT)
#define IS_VAILD_LON(lon) (lon >= ONEPOS_MIN_LON && lon <= ONEPOS_MAX_LON)

#define ONEPOS_WIFI_MAC_STR_LEN (OS_WLAN_BSSID_MAX_LENGTH * 2 + OS_WLAN_BSSID_MAX_LENGTH - 1) /* mac addr len : 17*/
#define ONEPOS_WIFI_RSSI_LEN    4u
#define ONEPOS_WIFI_MSG_FORMAT  "%02x:%02x:%02x:%02x:%02x:%02x,%4d"
#define ONEPOS_WIFI_INFO_LEN    22
#define ONEPOS_CELL_MSG_FORMAT  "%3u,%2u,%10u,%15u,%4d"
#define ONEPOS_CELL_INFO_LEN    38
#define ONEPOS_MSG_SEPARATOR    "|"

/**
 ***********************************************************************************************************************
 * @struct      onepos_pos_t
 *
 * @brief       onepos position result
 ***********************************************************************************************************************
 */
typedef struct
{
    os_uint32_t time;           /* Information acquisition time */
    double      lat_coordinate; /* Latitude coordinate */
    double      lon_coordinate; /* Longitude coordinate */
} onepos_pos_t;

#if defined(ONEPOS_WIFI_POS)
#include "onepos_wifi_loca.h"
#endif

#if defined(ONEPOS_CELL_POS)
#include "onepos_cell_loca.h"
#endif

#ifdef OS_USING_GNSS_POS
#include "nmea_0183.h"
#endif

extern os_bool_t onepos_init(void);
extern void      onepos_deinit(void);
extern os_bool_t onepos_get_dev_sta(void);
extern os_err_t  onepos_mqtt_connect(void);
extern void      onepos_rep_device_sta(void);
extern void      onepos_mqtt_disconnect(void);
extern os_bool_t onepos_mqtt_is_connected(void);
extern os_bool_t onepos_location(onepos_pos_t *pos_src);

#endif /* __ONEPOS_SRC_INFO_H__ */
