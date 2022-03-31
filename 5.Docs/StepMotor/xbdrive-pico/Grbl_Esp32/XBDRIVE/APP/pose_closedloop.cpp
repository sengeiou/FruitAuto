#include "pose_closedloop.h"
#include <src/Grbl.h>

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void         pos_closedloop_ctrl() {
    BaseType_t xHigherPriorityTaskWoken = pdFAIL;
    // 读出编码器的角度位置值
    portENTER_CRITICAL_ISR(&timerMux);
    encoder_cnt = CaliTab.get(Encoder.ReadAngleHwCsYORO());
    portEXIT_CRITICAL_ISR(&timerMux);
    esp_task_wdt_reset();
    // 读出计数器计数的外部step脉冲数
    step_input = StepperInput.GetIntputPulse();
    // 计算出电机设定位置
    motor_pos_set = step_input_offset + (8192 / (int16_t)Microsteps_Type->get()) * step_input / 100;
    // 编码器溢出处理
    if (encoder_cnt - encoder_cnt_last > (ENCODER_CNT_PER_REV / 2)) {
        motor_rev_cnt--;
        xSemaphoreGiveFromISR(zerosignal_sem, &xHigherPriorityTaskWoken);
    } else if (encoder_cnt - encoder_cnt_last < -(ENCODER_CNT_PER_REV / 2)) {
        motor_rev_cnt++;
        xSemaphoreGiveFromISR(zerosignal_sem, &xHigherPriorityTaskWoken);
    }
    // 计算出当前电机实际位置
    motor_pos = encoder_cnt + ENCODER_CNT_PER_REV * motor_rev_cnt;
    // 计算位置误差
    motor_pos_err = motor_pos_set - motor_pos;
    // 误差限幅
    if (motor_pos_err > (ENCODER_CNT_PER_REV * 0.1)) {
        motor_pos_err = (ENCODER_CNT_PER_REV * 0.1);
        LED.set(HIGH);
    } else if (motor_pos_err < -(ENCODER_CNT_PER_REV * 0.1)) {
        motor_pos_err = -(ENCODER_CNT_PER_REV * 0.1);
        LED.set(HIGH);
    } else {
        LED.set(LOW);
    }
    // 积分项计算
    pid_iterm += pose_pid_i->get() * motor_pos_err / 32;
    // 积分限幅
    if (pid_iterm > CLOSED_LOOP_MODE_CURRENT_SUM_MAX) {
        pid_iterm = CLOSED_LOOP_MODE_CURRENT_SUM_MAX;
    } else if (pid_iterm < -CLOSED_LOOP_MODE_CURRENT_SUM_MAX) {
        pid_iterm = -CLOSED_LOOP_MODE_CURRENT_SUM_MAX;
    }
    // 微分项计算
    pid_dterm =
        lowpass_filtering_a->get() * pid_dterm / 128 - lowpass_filtering_b->get() * pose_pid_d->get() * (motor_pos - motor_pos_last) / 8;
    // PID三项计算值
    // 13 = 3300/255
    vector_current = (pose_pid_p->get() * motor_pos_err + pid_iterm + pid_dterm) / 128 * 13;
    //
    advance = motor_pos - motor_pos_last;
    // 更新历史值
    encoder_cnt_last = encoder_cnt;
    motor_pos_last   = motor_pos;
    // 以当前位置为基础，计算下一步的目标位置
    int32_t theta = encoder_cnt;
    if (vector_current > 0) {
        theta += ((ENCODER_CNT_PER_REV / motor_full_steps_per_rev->get()) + advance);  //电流矢量等于1.8度加上前馈角
    } else if (vector_current < 0) {
        theta -= ((ENCODER_CNT_PER_REV / motor_full_steps_per_rev->get()) - advance);
        vector_current = -vector_current;
    }
    // 电流矢量最大值限制
    if (vector_current > closed_loop_mode_current_max_ma->get()) {
        vector_current = closed_loop_mode_current_max_ma->get();
    }
    Output(theta, vector_current);
}