/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-07     RT-Thread    first version
 */

#include <rtthread.h>
#include <board.h>
#include <rtdevice.h>
#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define PWM_DEV_NAME        "pwm3"  /* PWM设备名称 */
#define PWM_DEV_CHANNEL     1       /* PWM通道 */
#define LED_PIN_NUM 7
struct rt_device_pwm *pwm_dev;      /* PWM设备句柄 */
rt_uint32_t period, pulse;
static int pwm_led_sample();
int main(void)
{
    //MX_TIM3_Init();
    int count = 1;

    pwm_led_sample();

    while (count++)
    {
        //rt_pwm_enable(device, channel)
        LOG_D("Hello RT-Thread!");
        rt_thread_mdelay(100000);
    }

    return RT_EOK;
}

struct rt_device_pwm *pwm_dev;      /* PWM设备句柄 */
static int pwm_led_sample()
{
    rt_uint32_t period, pulse, dir;
    period = 500000;    /* 周期为0.5ms，单位为纳秒ns */
    dir = 1;            /* PWM脉冲宽度值的增减方向 */
    pulse = 0;          /* PWM脉冲宽度值，单位为纳秒ns */
    /* 设置LED引脚脚模式为输出 */
    rt_pin_mode(LED_PIN_NUM, PIN_MODE_OUTPUT);
    /* 拉高LED引脚 */
    rt_pin_write(LED_PIN_NUM, PIN_LOW);

    /* 查找设备 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }
    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);

    while (1)
    {
        rt_thread_mdelay(5);
        if (dir)
        {
            pulse += 500;      /* 从0值开始每次增加5000ns */
        }
        else
        {
            pulse -= 500;      /* 从最大值开始每次减少5000ns */
        }
        if (pulse >= period)
        {
            dir = 0;
        }
        if (0 == pulse)
        {
            dir = 1;
        }
        /* 设置PWM周期和脉冲宽度 */
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pwm_led_sample, pwm sample);
