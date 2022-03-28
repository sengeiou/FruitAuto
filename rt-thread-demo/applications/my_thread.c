/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-28     ijink       the first version
 */
#include <rtthread.h>


void th_entry(void *parameter)
{
    while (1)
    {
        rt_kprintf("Hello 1...\n");
        rt_thread_mdelay(5000);
    }
}
