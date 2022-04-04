#include <XBDRIVE/global.h>

HardwareSerial *DEBUG_port = &DEBUE_PORT;

volatile int32_t step_input = 0; //外部控制脉冲输入定时器的值
volatile int32_t step_input_offset = 0; //上电初始外部控制脉冲输入偏移值
volatile int32_t motor_pos_set = 0;  //指令电机位置
volatile int32_t motor_pos_set_last = 0; 
volatile uint8_t dir = 1;         //电机旋转方向
volatile int32_t encoder_cnt = 0; //编码器的读数值
volatile int32_t encoder_cnt_last = 0;
volatile int32_t motor_pos = 0;     //实际电机位置值
volatile int32_t motor_pos_last = 0;
volatile int32_t advance = 0;        //电机控制提前角度
volatile int32_t motor_rev_cnt = 0;  //电机旋转圈数
volatile int32_t motor_pos_err = 0;  //误差值等于指令电机位置值减去实际电机位置值
volatile int32_t pid_iterm = 0;      //PID控制i积分项
volatile int32_t pid_dterm = 0;      //PID控制d微分项
volatile int32_t vector_current = 0; //矢量控制电流大小

volatile int32_t half_current_cnt = 0; //开环模式下半流控制计数值