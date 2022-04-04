#include "pose_openloop.h"
#include <src/Grbl.h>

void pos_openloop_ctrl() {
    // 读出计数器计数的外部step脉冲数
    step_input = StepperInput.GetIntputPulse();
    // 计算出电机设定位置
    motor_pos_set = step_input_offset + (8192 / (int16_t)Microsteps_Type->get()) * step_input / 100;
    // 如果位置不变，开始进行半流模式倒计时
    if (motor_pos_set == motor_pos_set_last) {
        half_current_cnt++;
        if (half_current_cnt >= half_current_time_ms->get()) {
            half_current_cnt = half_current_time_ms->get();
        }
    } else {
        half_current_cnt = 0;
    }
    // 1s时间已到，进入半流模式
    if (half_current_cnt >= open_loop_mode_current_max_ma->get()) {
        Output(motor_pos_set, open_loop_mode_current_max_ma->get() / 2);
    } else {
        Output(motor_pos_set, open_loop_mode_current_max_ma->get());
    }
    // 历史值更新
    motor_pos_set_last = motor_pos_set;
}