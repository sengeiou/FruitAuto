#pragma once

#include <cstdint>

enum class MotionControlType : int8_t { velocity = 0, position, velocity_openloop, position_openloop, calibration, none};

class MotionControlClass {
public:
    MotionControlType type;
    MotionControlClass();
};

extern MotionControlClass* controlmode;
