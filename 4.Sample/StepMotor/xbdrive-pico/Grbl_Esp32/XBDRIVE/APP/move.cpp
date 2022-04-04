#include "move.h"
#include <src/Grbl.h>

// 矢量控制
void Output(int32_t theta, int32_t effort) {
    int32_t vector_coil_A;
    int32_t vector_coil_B;
    int16_t sin_angle;
    int16_t cos_angle;
    int16_t angle;
    int16_t angle_halfpi;
    int16_t phase_multiplier = 1250;  //电机跑一圈共50个电相位角/4
    // angle_1 = myMod(phase_multiplier * theta / 100, 4096); //编码器读出的机械角转换为电相位角
    angle = (phase_multiplier * theta / 100) % sinTabLen;
    if (angle < 0) {
        angle = angle + 4096;
    }
    // 后移1/4周期
    angle_halfpi = angle + 1024;
    // 溢出处理
    if (angle_halfpi > sinTabLen) {
        angle_halfpi -= sinTabLen;
    }
    // 查找表值被放大了1024倍
    sin_angle     = _sin[angle];
    cos_angle     = _sin[angle_halfpi];
    vector_coil_A = (int32_t)(effort * 256 * sin_angle / 1024 / 3300);  //电机A相的矢量分解电流
    vector_coil_B = (int32_t)(effort * 256 * cos_angle / 1024 / 3300);  //电机B相的矢量分解电流
    // vector_coil_A = effort * sin_angle / 1024;               //电机A相的矢量分解电流
    // vector_coil_B = effort * cos_angle / 1024;               //电机B相的矢量分解电流
    if (vector_coil_A >= 0) {
        CoilA.set(HIGH, LOW, vector_coil_A);
    } else {
        CoilA.set(LOW, HIGH, -vector_coil_A);
    }
    if (vector_coil_B >= 0) {
        CoilB.set(HIGH, LOW, vector_coil_B);
    } else {
        CoilB.set(LOW, HIGH, -vector_coil_B);
    }
}

// 单步运动
void OneStep(void) {
    static int32_t stepnumber = 0;  //电机走的整步步数
    if (dir) {
        stepnumber += 1;
    } else {
        stepnumber -= 1;
    }
    Output((1.0 * ENCODER_CNT_PER_REV / motor_full_steps_per_rev->get()) * stepnumber, calibration_mode_current_max_ma->get());
    delay(one_full_step_delay_ms->get());
}