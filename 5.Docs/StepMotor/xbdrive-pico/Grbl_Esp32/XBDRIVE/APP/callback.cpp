#include "callback.h"
#include <src/Grbl.h>

void IRAM_ATTR ControlerLoop_callback(void) {

    //if (en_mode == ENABLE)
    if (ENABLE) {
        esp_task_wdt_reset();
        // 闭环模式
        if (controlMode_Type->get() == (int)MotionControlType::position) {
            pos_closedloop_ctrl();
            velocity_estimation_calculate();
        }
        // 开环模式
        else if (controlMode_Type->get() == (int)MotionControlType::position_openloop) {
            pos_openloop_ctrl();
        }
    }
}

void ENN_IRQHandler(void) {
    if (StepperInput.IsEnlable() == true) {
        // 编码器初始化
        encoder_cnt      = CaliTab.get(Encoder.ReadAngleHwCsYORO());
        encoder_cnt_last = encoder_cnt;
        // 位置设定值初始化
        motor_pos_set      = encoder_cnt;
        motor_pos_set_last = encoder_cnt;
        // 位置值初始化
        motor_pos      = encoder_cnt;
        motor_pos_last = encoder_cnt;
        // 位置偏移初始化
        step_input_offset = encoder_cnt;
        // 圈数初始化
        motor_rev_cnt = 0;
    } else {
        CoilA.free();
        CoilB.free();
    }
}

bool switchControlMode_callback(char* val) {
    if (!val) {
        switch (controlMode_Type->get()) {
            case (int)(MotionControlType::position):
                Serial.printf("current mode: position\r\n");
                break;
            case (int)(MotionControlType::position_openloop):
                Serial.printf("current mode: position_openloop\r\n");
                break;
            case (int)(MotionControlType::velocity):
                Serial.printf("current mode: velocity\r\n");
                break;
            case (int)(MotionControlType::velocity_openloop):
                Serial.printf("current mode: velocity_openloop\r\n");
                break;
            case (int)(MotionControlType::calibration):
                Serial.printf("current mode: calibration\r\n");
                EncoderCalibrating();
                break;
            case (int)(MotionControlType::none):
                Serial.printf("current mode: none\r\n");
                break;
        }
    }

    return true;
}

bool switchMicrosteps_callback(char* val) {
    if (!val) {
        Serial.printf("mcrosteps: %s, %d\r\n", Microsteps_Type->getStringValue(), (int16_t)Microsteps_Type->get());
    }

    return true;
}

bool switchMonitortype_callback(char* val) {
    if (!val) {
        Serial.printf("monitor: %s, %d\r\n", Monitor_Type->getStringValue(), (int16_t)Monitor_Type->get());
    }

    return true;
}
