/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-28     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "my_thread.h"

rt_thread_t th1_ptr = NULL;

struct rt_thread th2 ;

rt_uint8_t th2_stack[512] = { 0 };

rt_err_t ret;

int main(void)
{
    //线程调度器hook func set
    rt_scheduler_sethook(scheduler_hook);

    //动态创建线程
    //线程1创建
    th1_ptr = rt_thread_create("th_demo1", th_entry, NULL, 1024, 20, 5);
    //线程1创建成功性检查
    if (th1_ptr == RT_NULL)
    {
        LOG_E("rt_thread1 create failed...\n");
        
        return -RT_ENOMEM;
    }
    LOG_D("rt_thread create1 success...\n");
    //线程1启动
    rt_thread_startup(th1_ptr);

    //静态创建线程
    //线程2创建
    ret = rt_thread_init(&th2, "th_demo2", th_entry2, NULL, th2_stack, 512, 15, 5);
    //线程2创建成功性检查
    if (ret < 0)
    {
        LOG_E("rt_thread2 create failed...\n");
        return ret;
    }
    LOG_D("rt_thread create2 success...\n");
    //线程2启动
    rt_thread_startup(&th2);


    return RT_EOK;
}
