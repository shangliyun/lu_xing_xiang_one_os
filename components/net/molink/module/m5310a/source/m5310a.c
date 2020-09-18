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
 * @file        m5310a.c
 *
 * @brief       m5310-a factory mode api
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-25   OneOS Team      First Version
 ***********************************************************************************************************************
 */

#include "m5310a.h"

#include <stdlib.h>
#include <string.h>

#define DBG_EXT_TAG "m5310a"
#define DBG_EXT_LVL LOG_LVL_INFO
#include <os_dbg_ext.h>

#ifdef MOLINK_USING_M5310A

#ifdef M5310A_USING_GENERAL_OPS
static const struct mo_general_ops gs_general_ops = {
    .at_test             = m5310a_at_test,
    .get_imei            = m5310a_get_imei,
    .get_imsi            = m5310a_get_imsi,
    .get_iccid           = m5310a_get_iccid,
    .get_cfun            = m5310a_get_cfun,
    .set_cfun            = m5310a_set_cfun,
    .clear_stored_earfcn = m5310a_clear_stored_earfcn,
    .get_app_version     = m5310a_get_app_version,
};
#endif /* M5310A_USING_GENERAL_OPS */

#ifdef M5310A_USING_NETSERV_OPS
static const struct mo_netserv_ops gs_netserv_ops = {
    .set_attach     = m5310a_set_attach,
    .get_attach     = m5310a_get_attach,
    .set_reg        = m5310a_set_reg,
    .get_reg        = m5310a_get_reg,
    .set_cgact      = m5310a_set_cgact,
    .get_cgact      = m5310a_get_cgact,
    .get_csq        = m5310a_get_csq,
    .get_radio      = m5310a_get_radio,
    .get_ipaddr     = m5310a_get_ipaddr,
    .ping           = m5310a_ping,
};
#endif /* M5310A_USING_NETSERV_OPS */

#ifdef M5310A_USING_NETCONN_OPS
extern void m5310a_netconn_init(mo_m5310a_t *module);

static const struct mo_netconn_ops gs_netconn_ops = {
    .create        = m5310a_netconn_create,
    .destroy       = m5310a_netconn_destroy,
    .gethostbyname = m5310a_netconn_gethostbyname,
    .connect       = m5310a_netconn_connect,
    .send          = m5310a_netconn_send,
    .get_info      = m5310a_netconn_get_info,
};
#endif /* M5310A_USING_NETCONN_OPS */

#ifdef M5310A_USING_ONENET_NB_OPS
static const mo_onenet_ops_t gs_onenet_ops = {
    .onenetnb_create      = m5310_onenetnb_create,
    .onenetnb_createex    = m5310_onenetnb_createex,
    .onenetnb_addobj      = m5310_onenetnb_addobj,
    .onenetnb_discoverrsp = m5310_onenetnb_discoverrsp,
    .onenetnb_nmi         = m5310_onenetnb_set_nmi,
    .onenetnb_open        = m5310_onenetnb_open,
    .onenetnb_notify      = m5310_onenetnb_notify,
    .onenetnb_update      = m5310_onenetnb_update,
    .onenetnb_get_write   = m5310_onenetnb_get_write,
    .onenetnb_writersp    = m5310_onenetnb_writersp,
#ifdef OS_USING_SHELL
    .onenetnb_all         = m5310_onenetnb_all,
#endif
};
#endif /* M5310A_USING_ONENET_OPS */

mo_object_t *module_m5310a_create(const char *name, os_device_t *device, os_size_t recv_len)
{
    mo_m5310a_t *module = (mo_m5310a_t *)malloc(sizeof(mo_m5310a_t));

    os_err_t result = mo_object_init(&(module->parent), name, device, recv_len);
    if (result != OS_EOK)
    {
        goto __exit;
    }

#ifdef M5310A_USING_GENERAL_OPS
    module->parent.ops_table[MODULE_OPS_GENERAL] = &gs_general_ops;
#endif /* M5310A_USING_GENERAL_OPS */

#ifdef M5310A_USING_NETSERV_OPS
    module->parent.ops_table[MODULE_OPS_NETSERV] = &gs_netserv_ops;
#endif /* M5310A_USING_NETSERV_OPS */

#ifdef M5310A_USING_NETCONN_OPS
    module->parent.ops_table[MODULE_OPS_NETCONN] = &gs_netconn_ops;
    m5310a_netconn_init(module);

    os_mutex_init(&module->netconn_lock, name, OS_IPC_FLAG_FIFO, OS_TRUE);
#endif /* M5310A_USING_NETCONN_OPS */

#ifdef M5310A_USING_ONENET_NB_OPS
    module->parent.ops_table[MODULE_OPS_ONENET_NB] = &gs_onenet_ops;
#endif /* M5310A_USING_ONENET_NB_OPS */

__exit:
    if (result != OS_EOK)
    {
        free(module);

        return OS_NULL;
    }

    return &(module->parent);
}

os_err_t module_m5310a_destroy(mo_object_t *self)
{
    mo_m5310a_t *module = os_container_of(self, mo_m5310a_t, parent);

#ifdef M5310A_USING_NETCONN_OPS
    os_mutex_deinit(&module->netconn_lock);
#endif /* M5310A_USING_NETCONN_OPS */

    mo_object_deinit(self);

    free(module);

    return OS_EOK;
}

#ifdef M5310A_AUTO_CREATE
#include <serial.h>

static struct serial_configure uart_config = OS_SERIAL_CONFIG_DEFAULT;

int m5310_auto_create(void)
{
    os_device_t *device = os_device_find(M5310A_DEVICE_NAME);

    if (OS_NULL == device)
    {
        LOG_EXT_E("Auto create failed, Can not find M5310A interface device %s!", M5310A_DEVICE_NAME);
        return OS_ERROR;
    }

    uart_config.baud_rate = M5310A_DEVICE_RATE;

    os_device_control(device, OS_DEVICE_CTRL_CONFIG, &uart_config);

    mo_object_t *module = module_m5310a_create(M5310A_NAME, device, M5310A_RECV_BUFF_LEN);

    if (OS_NULL == module)
    {
        LOG_EXT_E("Auto create failed, Can not create %s module object!", M5310A_NAME);
        return OS_ERROR;
    }

    LOG_EXT_I("Auto create %s module object success!", M5310A_NAME);
    return OS_EOK;
}
OS_CMPOENT_INIT(m5310_auto_create);

#endif /* M5310A_AUTO_CREATE */

#endif /* MOLINK_USING_M5310A */
