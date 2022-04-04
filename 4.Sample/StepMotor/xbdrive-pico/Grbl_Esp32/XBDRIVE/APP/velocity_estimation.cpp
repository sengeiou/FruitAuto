#include "velocity_estimation.h"
#include <src/Grbl.h>

static int64_t velocity_estimation_cnt_M = 0;
static int64_t velocity_estimation_cnt_T = 0;

void velocity_estimation_calculate() {
    static int64_t motor_pos_delta_sum_M     = 0;
    static int64_t motor_pos_delta_sum_T_abs = 0;
    static int64_t motor_pos_delta_sum_T     = 0;
    static int32_t cnt_M                     = 0;
    static int32_t cnt_T                     = 0;
    // M法
    motor_pos_delta_sum_M += /*motor_pos - motor_pos_last*/ advance;
    if (cnt_M++ == 50) {
        velocity_estimation_cnt_M = motor_pos_delta_sum_M * 10000 / cnt_M;
        motor_pos_delta_sum_M     = 0;
        cnt_M                     = 0;
    }
    // T法
    motor_pos_delta_sum_T_abs += abs(/*motor_pos - motor_pos_last*/ advance);
    motor_pos_delta_sum_T += /*motor_pos - motor_pos_last*/ advance;
    cnt_T++;
    if (motor_pos_delta_sum_T_abs > 500) {
        velocity_estimation_cnt_T = motor_pos_delta_sum_T * 10000 / cnt_T;
        motor_pos_delta_sum_T     = 0;
        motor_pos_delta_sum_T_abs = 0;
        cnt_T                     = 0;
    }
}
int32_t get_vel_M() {
    return velocity_estimation_cnt_M;
}
int32_t get_vel_T() {
    return velocity_estimation_cnt_T;
}
int32_t get_vel() {
    if (velocity_estimation_cnt_T < 5000) {
        return velocity_estimation_cnt_T;
    } else {
        return velocity_estimation_cnt_M;
    }
}

int32_t get_vel_flt() {
    static int32_t recoder = get_vel();
    recoder                = recoder - (recoder / 4) + (get_vel() / 4);
    return recoder;
}