/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-28     ijink       the first version
 */
#ifndef APPLICATIONS_MY_THREAD_H_
#define APPLICATIONS_MY_THREAD_H_

#ifdef __cplusplus
extern "C"
{
#endif

//线程1执行函数
void th_entry(void *parameter);

//线程2执行函数
void th_entry2(void *parameter);

//线程调度器hook函数
void scheduler_hook(struct rt_thread *from, struct rt_thread *to);


#endif /* APPLICATIONS_MY_THREAD_H_ */
