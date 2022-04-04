#include "Grbl.h"
#include <XBDRIVE/global.h>

EnumSetting* controlMode_Type;
enum_opt_t   controlModeTypes = {
    { "POS_CL", int8_t(MotionControlType::position) },  { "POS_OP", int8_t(MotionControlType::position_openloop) },
    { "VEL_CL", int8_t(MotionControlType::velocity) },  { "VEL_OP", int8_t(MotionControlType::velocity_openloop) },
    { "CALI", int8_t(MotionControlType::calibration) }, { "NONE", int8_t(MotionControlType::none) },

};

EnumSetting* Microsteps_Type;
enum_opt_t   MicrostepsTypes = {
    { "1", int16_t(MicrostepsType::full_microsteps) },     { "2", int16_t(MicrostepsType::half_microsteps) },
    { "4", int16_t(MicrostepsType::_4_microsteps) },       { "8", int16_t(MicrostepsType::_8_microsteps) },
    { "16", int16_t(MicrostepsType::_16_microsteps) },     { "32", int16_t(MicrostepsType::_32_microsteps) },
    { "64", int16_t(MicrostepsType::_64_microsteps) },     { "128", int16_t(MicrostepsType::_128_microsteps) },
    { "256", int16_t(MicrostepsType::_256_microsteps) },   { "512", int16_t(MicrostepsType::_512_microsteps) },
    { "1024", int16_t(MicrostepsType::_1024_microsteps) }, { "2048", int16_t(MicrostepsType::_2048_microsteps) },
};

EnumSetting* Monitor_Type;
enum_opt_t   MonitorTypes = {
    { "DATA", int16_t(MonitorType::DATA) },
    { "JSON", int16_t(MonitorType::JSON) },
    { "NONE", int16_t(MonitorType::NONE) },
};

IntSetting* pose_pid_p;
IntSetting* pose_pid_i;
IntSetting* pose_pid_d;

IntSetting* one_full_step_delay_ms;    // 一个全步所需要的时间
IntSetting* motor_full_steps_per_rev;  // 步进电机整步数
IntSetting* half_current_time_ms;      // 自动半流时间

IntSetting* closed_loop_mode_current_max_ma;  // 闭环模式最大电流设置，0.1欧姆采样电阻255对应3.3A电流
IntSetting* open_loop_mode_current_max_ma;    // 开环模式最大电流设置，0.1欧姆采样电阻255对应3.3A电流
IntSetting* calibration_mode_current_max_ma;  // 校准模式电流设置，0.1欧姆采样电阻255对应3.3A电流
IntSetting* lowpass_filtering_a;              // 低通滤波参数变量
IntSetting* lowpass_filtering_b;              // 低通滤波参数变量

IntSetting* monitor_delay;

FlagSetting* monitor_vel_enable;    // M/T法速度报告使能
FlagSetting* monitor_pos_enable;    // 位置报告使能
FlagSetting* monitor_input_enable;  // input报告使能
FlagSetting* monitor_pid_enable;    // pid报告使能
FlagSetting* monitor_temp_enable;   // 温度报告使能
FlagSetting* monitor_vol_enable;    // 电压报告使能

static const char* makename(const char* axisName, const char* tail) {
    char* retval = (char*)malloc(strlen(axisName) + strlen(tail) + 2);

    strcpy(retval, axisName);
    strcat(retval, "/");
    return strcat(retval, tail);
}

static bool checkStartupLine(char* value) {
    if (!value) {  // No POST functionality
        return true;
    }
    if (sys.state != State::Idle) {
        return false;
    }
    return gc_execute_line(value, CLIENT_SERIAL) == Error::Ok;
}

static bool postMotorSetting(char* value) {
    return true;
}

static bool checkSpindleChange(char* val) {
    if (!val) {
        // if not in disable (M5) ...
        if (gc_state.modal.spindle != SpindleState::Disable) {
            gc_state.modal.spindle = SpindleState::Disable;

            grbl_msg_sendf(CLIENT_ALL, MsgLevel::Info, "Spindle turned off with setting change");
        }

        return true;
    }
    return true;
}

// Generates a string like "122" from axisNum 2 and base 120
static const char* makeGrblName(int axisNum, int base) {
    // To omit A,B,C axes:
    // if (axisNum > 2) return NULL;
    char buf[4];
    snprintf(buf, 4, "%d", axisNum + base);
    char* retval = (char*)malloc(strlen(buf));
    return strcpy(retval, buf);
}

void make_coordinate(CoordIndex index, const char* name) {
    float coord_data[MAX_N_AXIS] = { 0.0 };
    auto  coord                  = new Coordinates(name);
    coords[index]                = coord;
    if (!coord->load()) {
        coords[index]->setDefault();
    }
}

// bool temp(char * val)
// {
//     Serial.printf("temp(char * val)\r\n");
//     return true;
// }

void make_settings() {
    Setting::init();

    // Spindle Settings
    controlMode_Type = new EnumSetting(
        NULL, EXTENDED, WG, NULL, "ControlMode/Type", static_cast<int8_t>(DEFAULT_CONTROLMODE), &controlModeTypes, switchControlMode_callback);
    Microsteps_Type = new EnumSetting(
        NULL, EXTENDED, WG, NULL, "Microsteps", static_cast<int8_t>(DEFAULT_MICROSTEPS), &MicrostepsTypes, switchMicrosteps_callback);
    pose_pid_p = new IntSetting(GRBL, WG, "200", "PosePID/Kp", DEFAULT_POSE_PID_P, 0, 1000);
    pose_pid_i = new IntSetting(GRBL, WG, "201", "PosePID/Ki", DEFAULT_POSE_PID_I, 0, 1000);
    pose_pid_d = new IntSetting(GRBL, WG, "202", "PosePID/Kd", DEFAULT_POSE_PID_D, 0, 1000);

    one_full_step_delay_ms   = new IntSetting(GRBL, WG, "203", "OneFullStepDelay/ms", DEFAULT_ONE_FULL_STEP_DELAY_MS, 0, 10000);
    motor_full_steps_per_rev = new IntSetting(GRBL, WG, "204", "MotorFullSteps/rev", DEFAULT_MOTOR_FULL_STEPS_PER_REV, 0, 10000);
    half_current_time_ms     = new IntSetting(GRBL, WG, "205", "HalfCurrentTime/ms", DEFAULT_HALF_CURRENT_MAX_MS, 0, 10000);

    closed_loop_mode_current_max_ma =
        new IntSetting(GRBL, WG, "206", "ClosedLoopModeMaxCurrent/mA", DEFAULT_CLOSED_LOOP_MODE_CURRENT_MAX_MA, 0, 3300);
    open_loop_mode_current_max_ma =
        new IntSetting(GRBL, WG, "207", "OpenLoopModeMaxCurrent/mA", DEFAULT_OPEN_LOOP_MODE_CURRENT_MAX_MA, 0, 3300);
    calibration_mode_current_max_ma =
        new IntSetting(GRBL, WG, "208", "CalibrationModeCurrent/mA", DEFAULT_CALIBRATION_MODE_CURRENT_MAX_MA, 0, 3300);
    lowpass_filtering_a = new IntSetting(GRBL, WG, "209", "LowpassFilter/A", DEFAULT_LOWPASS_FILTERING_A, 1, 1000);
    lowpass_filtering_b = new IntSetting(GRBL, WG, "210", "LowpassFilter/B", DEFAULT_LOWPASS_FILTERING_B, 1, 1000);

    // monitor
    Monitor_Type = new EnumSetting(
        NULL, EXTENDED, WG, NULL, "MonitorType", static_cast<int8_t>(DEFAULT_MONITORTYPE), &MonitorTypes, switchMonitortype_callback);
    monitor_delay        = new IntSetting(GRBL, WG, "220", "Monitor/Delay_ms", DEFAULT_MONITOR_DELAY_MS, 1, 1000);
    monitor_vel_enable   = new FlagSetting(GRBL, WG, "221", "Monitor/Velocity", DEFAULT_MONITOR_VEL_ENABLE);
    monitor_pos_enable   = new FlagSetting(GRBL, WG, "222", "Monitor/Position", DEFAULT_MONITOR_POS_ENABLE);
    monitor_input_enable = new FlagSetting(GRBL, WG, "223", "Monitor/Input", DEFAULT_MONITOR_INPUT_ENABLE);
    monitor_pid_enable   = new FlagSetting(GRBL, WG, "224", "Monitor/Pid", DEFAULT_MONITOR_PID_ENABLE);
    monitor_temp_enable  = new FlagSetting(GRBL, WG, "225", "Monitor/Temperature", DEFAULT_MONITOR_TEMP_ENABLE);
    monitor_vol_enable   = new FlagSetting(GRBL, WG, "226", "Monitor/voltage", DEFAULT_MONITOR_VOL_ENABLE);
}
