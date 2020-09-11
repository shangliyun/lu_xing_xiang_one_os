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
 * @file        at_parser.h
 *
 * @brief       AT parser header file
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-17   OneOS Team      First Version
 ***********************************************************************************************************************
 */

#ifndef __AT_PARSER_H__
#define __AT_PARSER_H__

#include "at_resp.h"

#include <os_kernel.h>
#include <os_device.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define ESC_KEY       0x1B
#define BACKSPACE_KEY 0x08
#define DELECT_KEY    0x7F

#ifndef END_MARK_LEN
#define END_MARK_LEN 2
#endif

#ifndef AT_PARSER_TASK_STACK_SIZE
#define AT_PARSER_TASK_STACK_SIZE 2048
#endif

#ifndef AT_PARSER_TASK_PRIORITY
#define AT_PARSER_TASK_PRIORITY (OS_TASK_PRIORITY_MAX / 3 - 1)
#endif

#ifndef AT_PARSER_TASK_TIMESLICE
#define AT_PARSER_TASK_TIMESLICE 5
#endif

struct at_parser;

/**
 ***********************************************************************************************************************
 * @struct      at_parser_urc
 *
 * @brief       URC(Unsolicited Result Code) object
 ***********************************************************************************************************************
 */
typedef struct at_urc
{
    os_slist_node_t list; /* URC object list */

    const char *prefix; /* URC data prefix */
    const char *suffix; /* URC data prefix */
    /* URC data function */
    void (*func)(struct at_parser *parser, const char *data, os_size_t size);
} at_urc_t;

/**
 ***********************************************************************************************************************
 * @struct      at_parser
 *
 * @brief       The object of AT parser
 ***********************************************************************************************************************
 */
typedef struct at_parser
{
    os_slist_node_t list;       /* at parser object manage list  */

    char name[OS_NAME_MAX + 1]; /* The name of AT parser */

    os_device_t *device; /* The device used by AT parser */

    char     *recv_buff;     /* The receive buffer of AT parser */
    os_size_t recv_buff_len; /* The receive buffer length of AT parser */
    os_size_t curr_recv_len; /* The current receive data length of AT parser */

    os_sem_t   rx_sem;    /* The receive notice semaphore of at parser */
    os_mutex_t recv_lock; /* The receive lock of at parser */

    os_size_t end_mark_len;               /* The special end mark length */
    char      end_mark[END_MARK_LEN + 1]; /* The special end mark */

    at_resp_t resp;      /* AT command response object */
    os_bool_t resp_need; /* Whether module response is needed */

    os_slist_node_t urc_list; /* URC handle list , Used to process URC data */

    os_task_t *task; /* AT Parser task*/
} at_parser_t;

os_err_t at_parser_init(at_parser_t *parser, const char *name, os_device_t *device, os_size_t recv_buff_len);
os_err_t at_parser_startup(at_parser_t *parser);
os_err_t at_parser_deinit(at_parser_t *parser);

os_err_t  at_parser_exec_cmd_valist(at_parser_t *parser, const char *cmd_expr, va_list args);
os_err_t  at_parser_exec_cmd(at_parser_t *parser, const char *cmd_expr, ...);
os_size_t at_parser_send(at_parser_t *parser, const char *buf, os_size_t size);
os_size_t at_parser_recv(at_parser_t *parser, char *buf, os_size_t size, os_int32_t timeout);

os_err_t at_parser_set_end_mark(at_parser_t *parser, const char *end_mark, os_size_t end_mark_len);
void     at_parser_set_urc_table(at_parser_t *parser, at_urc_t urc_table[], os_size_t table_size);
os_err_t at_parser_set_resp(at_parser_t *parser, os_size_t buff_size, os_size_t line_num, os_int32_t timeout);
os_err_t at_parser_reset_resp(at_parser_t *parser);

const char *at_parser_get_line(at_parser_t *parser, os_size_t resp_line);
const char *at_parser_get_line_by_kw(at_parser_t *parser, const char *keyword);
os_int32_t  at_parser_get_data_by_line(at_parser_t *parser, os_size_t resp_line, const char *resp_expr, ...);
os_int32_t  at_parser_get_data_by_kw(at_parser_t *parser, const char *keyword, const char *resp_expr, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AT_PARSER_H__ */