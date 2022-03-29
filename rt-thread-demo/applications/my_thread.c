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

//线程1执行函数
void th_entry(void *parameter)
{
    while (1)
    {
        rt_kprintf("Hello 1...\n");
        rt_thread_mdelay(5000);
    }
}

//线程2执行函数
void th_entry2(void *parameter)
{
    while (1)
    {
        rt_kprintf("Hello 2...\n");
        rt_thread_mdelay(2000);
    }
}

//线程调度器hook函数
void scheduler_hook(struct rt_thread *from, struct rt_thread *to){
    rt_kprintf("from:%s ---> to:%s\n", from->name, to->name);
}
