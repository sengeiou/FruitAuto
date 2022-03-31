#include "poweron.h"

void powerOnCheck(void)
{
    if (StepperInput.IsEnlable())
    {
        encoder_cnt = CaliTab.get(Encoder.ReadAngleHwCsYORO());
        step_input_offset = encoder_cnt;
        motor_pos_set = encoder_cnt;
        motor_pos_set_last = motor_pos_set;
        encoder_cnt_last = encoder_cnt;
        motor_pos = encoder_cnt;
        motor_pos_last = motor_pos;
        motor_rev_cnt = 0;
    }
    else
    {
        // 线圈电流置0
        CoilA.free();
        CoilB.free();
    }
}
