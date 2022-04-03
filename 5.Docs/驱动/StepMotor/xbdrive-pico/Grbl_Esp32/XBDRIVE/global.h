#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <Arduino.h>
#include <ArduinoJson.h>

#include <XBDRIVE/MotorCtrl/CaliTab.h>
#include <XBDRIVE/MotorCtrl/stepper_controller.h>
#include <XBDRIVE/MotorCtrl/stepper_input.h>
#include <XBDRIVE/MotorCtrl/OperationalMode.h>
#include <XBDRIVE/SLB/SinCosLUT.h>
#include <XBDRIVE/SLB/mymath.h>
#include <XBDRIVE/MotorCtrl/tempSensor.h>
#include <XBDRIVE/MotorCtrl/PowerVoltage.h>
#include <XBDRIVE/HDL/hdl.h>
#include <XBDRIVE/APP/move.h>
#include <XBDRIVE/APP/monitor.h>
#include <XBDRIVE/APP/calibration.h>
#include <XBDRIVE/APP/poweron.h>
#include <XBDRIVE/APP/callback.h>
#include <XBDRIVE/APP/zerosignal.h>
#include <XBDRIVE/APP/pose_closedloop.h>
#include <XBDRIVE/APP/pose_openloop.h>
#include <XBDRIVE/APP/velocity_estimation.h>
#include <XBDRIVE/MotorCtrl/ControlMode.h>
#include <XBDRIVE/MotorCtrl/Microsteps.h>

extern HardwareSerial* DEBUG_port;

extern volatile int32_t step_input;         //外部控制脉冲输入定时器的值
extern volatile int32_t step_input_offset;  //上电初始外部控制脉冲输入偏移值
extern volatile int32_t motor_pos_set;      //指令电机位置
extern volatile int32_t motor_pos_set_last;
extern volatile uint8_t dir;          //电机旋转方向
extern volatile int32_t encoder_cnt;  //编码器的读数值
extern volatile int32_t encoder_cnt_last;
extern volatile int32_t motor_pos;  //实际电机位置值
extern volatile int32_t motor_pos_last;
extern volatile int32_t advance;         //电机控制提前角度
extern volatile int32_t motor_rev_cnt;   //电机旋转圈数
extern volatile int32_t motor_pos_err;   //误差值等于指令电机位置值减去实际电机位置值
extern volatile int32_t pid_iterm;       //PID控制i积分项
extern volatile int32_t pid_dterm;       //PID控制d微分项
extern volatile int32_t vector_current;  //矢量控制电流大小

extern volatile int32_t half_current_cnt;  //开环模式下半流控制计数值

#endif
