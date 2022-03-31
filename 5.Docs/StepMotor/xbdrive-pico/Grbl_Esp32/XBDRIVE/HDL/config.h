#ifndef __CONFIG_H_
#define __CONFIG_H_

#define DEBUE_PORT Serial

#define BAUDRATE 115200

#define ENCODER_CNT_PER_REV 16384L              // 编码器分辨率
#define FLASH_BASS_ADDRESS 0x08008000UL         // FLASH起始地址
#define EN_ACTIVE_LEVEL LOW                     // EN有效电平
#define DIR_ACTIVE_LEVEL HIGH                   // DIR有效电平
#define SET1_SET2_CL_CAL_PULL LL_GPIO_PULL_DOWN // SET1/SET2/CL/CAL引脚上下拉 LL_GPIO_PULL_UP LL_GPIO_PULL_DOWN
#define STEP_INPUT_COUNTER_RELOAD_VAL 64999L    // step输入脉冲计数器自动重装值
#define CLOSED_LOOP_MODE_CURRENT_SUM_MAX 12800L // 积分项目饱和限制

#define ENABLE HIGH
#define DISABLE LOW

#define DIR_FORWARD_LEVEL LOW
#define ENN_ENABLE_LEVEL LOW

#endif
