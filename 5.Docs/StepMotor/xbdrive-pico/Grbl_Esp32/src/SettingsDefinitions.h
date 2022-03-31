#pragma once

extern EnumSetting* controlMode_Type;
extern EnumSetting* Microsteps_Type;

extern IntSetting* pose_pid_p;
extern IntSetting* pose_pid_i;
extern IntSetting* pose_pid_d;

extern IntSetting* one_full_step_delay_ms;
extern IntSetting* motor_full_steps_per_rev;
extern IntSetting* half_current_time_ms;

extern IntSetting* closed_loop_mode_current_max_ma;
extern IntSetting* open_loop_mode_current_max_ma;
extern IntSetting* calibration_mode_current_max_ma;
extern IntSetting* lowpass_filtering_a;
extern IntSetting* lowpass_filtering_b;

extern IntSetting* monitor_delay;
extern FlagSetting* monitor_vel_enable;    // M/T法速度报告使能
extern FlagSetting* monitor_pos_enable;    // 位置报告使能
extern FlagSetting* monitor_input_enable;  // input报告使能
extern FlagSetting* monitor_pid_enable;    // pid报告使能
extern FlagSetting* monitor_temp_enable;   // 温度报告使能
extern FlagSetting* monitor_vol_enable;    // 电压报告使能

extern EnumSetting* Monitor_Type;

// extern IntSetting *Microsteps;
