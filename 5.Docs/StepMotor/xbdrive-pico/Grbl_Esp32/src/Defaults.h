#pragma once

/*
  Defaults.h - defaults settings configuration file
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

	2018 -	Bart Dring This file was modifed for use on the ESP32
					CPU. Do not use this with Grbl for atMega328P

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* The defaults.h file serves as a central default settings selector for different machine
   types, from DIY CNC mills to CNC conversions of off-the-shelf machines. The settings
   files listed here are supplied by users, so your results may vary. However, this should
   give you a good starting point as you get to know your machine and tweak the settings for
   your nefarious needs.
   NOTE: Ensure one and only one of these DEFAULTS_XXX values is defined in config.h */

/*
    All of these settings check to see if they have been defined already
    before defining them. This allows to to easily set them eslewhere.
    You only need to set ones that are important or unique to your
    machine. The rest will be pulled from here.
    */

// ==================  pin defaults ========================

// Here is a place to default pins to UNDEFINED_PIN.
// This can eliminate checking to see if the pin is defined because
// the overridden pinMode and digitalWrite functions will deal with it.

#ifndef SDCARD_DET_PIN
#    define SDCARD_DET_PIN UNDEFINED_PIN
#endif

// ================ User Digital I/O ==============================

#ifndef USER_DIGITAL_PIN_0
#    define USER_DIGITAL_PIN_0 UNDEFINED_PIN
#endif

#ifndef USER_DIGITAL_PIN_1
#    define USER_DIGITAL_PIN_1 UNDEFINED_PIN
#endif

#ifndef USER_DIGITAL_PIN_2
#    define USER_DIGITAL_PIN_2 UNDEFINED_PIN
#endif

#ifndef USER_DIGITAL_PIN_3
#    define USER_DIGITAL_PIN_3 UNDEFINED_PIN
#endif

// ================ User Analog I/O ==============================

#ifndef USER_ANALOG_PIN_0
#    define USER_ANALOG_PIN_0 UNDEFINED_PIN
#endif

#ifndef USER_ANALOG_PIN_1
#    define USER_ANALOG_PIN_1 UNDEFINED_PIN
#endif

#ifndef USER_ANALOG_PIN_2
#    define USER_ANALOG_PIN_2 UNDEFINED_PIN
#endif

#ifndef USER_ANALOG_PIN_3
#    define USER_ANALOG_PIN_3 UNDEFINED_PIN
#endif

#ifndef PROBE_PIN
#    define PROBE_PIN UNDEFINED_PIN
#endif

#ifndef USER_ANALOG_PIN_0_FREQ
#    define USER_ANALOG_PIN_0_FREQ 5000
#endif
#ifndef USER_ANALOG_PIN_1_FREQ
#    define USER_ANALOG_PIN_1_FREQ 5000
#endif
#ifndef USER_ANALOG_PIN_2_FREQ
#    define USER_ANALOG_PIN_2_FREQ 5000
#endif
#ifndef USER_ANALOG_PIN_3_FREQ
#    define USER_ANALOG_PIN_3_FREQ 5000
#endif

//

#ifndef DEFAULT_POSE_PID_P
#    define DEFAULT_POSE_PID_P 30
#endif

#ifndef DEFAULT_POSE_PID_I
#    define DEFAULT_POSE_PID_I 5
#endif

#ifndef DEFAULT_POSE_PID_D
#    define DEFAULT_POSE_PID_D 100
#endif

#ifndef DEFAULT_ONE_FULL_STEP_DELAY_MS
#    define DEFAULT_ONE_FULL_STEP_DELAY_MS 1
#endif

#ifndef DEFAULT_MOTOR_FULL_STEPS_PER_REV
#    define DEFAULT_MOTOR_FULL_STEPS_PER_REV 200
#endif

#ifndef DEFAULT_HALF_CURRENT_MAX_MS
#    define DEFAULT_HALF_CURRENT_MAX_MS 1000L
#endif

#ifndef DEFAULT_CLOSED_LOOP_MODE_CURRENT_MAX_MA
#    define DEFAULT_CLOSED_LOOP_MODE_CURRENT_MAX_MA 1300L
#endif

#ifndef DEFAULT_OPEN_LOOP_MODE_CURRENT_MAX_MA
#    define DEFAULT_OPEN_LOOP_MODE_CURRENT_MAX_MA 1300L
#endif

#ifndef DEFAULT_CALIBRATION_MODE_CURRENT_MAX_MA
#    define DEFAULT_CALIBRATION_MODE_CURRENT_MAX_MA 650L
#endif

#ifndef DEFAULT_LOWPASS_FILTERING_A
#    define DEFAULT_LOWPASS_FILTERING_A 110L
#endif

#ifndef DEFAULT_LOWPASS_FILTERING_B
#    define DEFAULT_LOWPASS_FILTERING_B 10L
#endif

#ifndef DEFAULT_CONTROLMODE
#    define DEFAULT_CONTROLMODE MotionControlType::position
#endif

#ifndef DEFAULT_MICROSTEPS
#    define DEFAULT_MICROSTEPS MicrostepsType::_16_microsteps
#endif

#ifndef DEFAULT_MONITORTYPE
#    define DEFAULT_MONITORTYPE MonitorType::NONE
#endif

#ifndef DEFAULT_MONITOR_DELAY_MS
#    define DEFAULT_MONITOR_DELAY_MS 10
#endif

#ifndef DEFAULT_MONITOR_VEL_ENABLE
#    define DEFAULT_MONITOR_VEL_ENABLE false
#endif

#ifndef DEFAULT_MONITOR_POS_ENABLE
#    define DEFAULT_MONITOR_POS_ENABLE false
#endif

#ifndef DEFAULT_MONITOR_INPUT_ENABLE
#    define DEFAULT_MONITOR_INPUT_ENABLE false
#endif

#ifndef DEFAULT_MONITOR_PID_ENABLE
#    define DEFAULT_MONITOR_PID_ENABLE false
#endif

#ifndef DEFAULT_MONITOR_TEMP_ENABLE
#    define DEFAULT_MONITOR_TEMP_ENABLE false
#endif

#ifndef DEFAULT_MONITOR_VOL_ENABLE
#    define DEFAULT_MONITOR_VOL_ENABLE false
#endif
