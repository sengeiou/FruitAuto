/*
  Grbl.cpp - Initialization and main loop for Grbl
  Part of Grbl
  Copyright (c) 2014-2016 Sungeun K. Jeon for Gnea Research LLC

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

#include "Grbl.h"
#include <WiFi.h>

#include <XBDRIVE/XBDrive.h>

class XBDrive;

void grbl_init() {
#ifdef USE_I2S_OUT
    i2s_out_init();  // The I2S out must be initialized before it can access the expanded GPIO port
#endif
    WiFi.persistent(false);
    WiFi.disconnect(true);
    WiFi.enableSTA(false);
    WiFi.enableAP(false);
    WiFi.mode(WIFI_OFF);
    client_init();  // Setup serial baud rate and interrupts
    grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "XBDrive Ver %s Date %s", VERSION, VERSION_BUILD);  // print grbl_esp32 verion info
    grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "Compiled with ESP32 SDK:%s", ESP.getSdkVersion());           // print the SDK version
    settings_init();  // Load Grbl settings from non-volatile storage
    //
#ifdef ENABLE_WIFI
    WebUI::wifi_config.begin();
#endif
#ifdef ENABLE_BLUETOOTH
    WebUI::bt_config.begin();
#endif
    WebUI::inputBuffer.begin();
    //
    Serial.begin(115200);
    xbdrive.setup();
}

void run_once() {
    // Reset Grbl primary systems.
    client_reset_read_buffer(CLIENT_ALL);

    report_init_message(CLIENT_ALL);
    // Start Grbl main loop. Processes program inputs and executes them.
    // This can exit on a system abort condition, in which case run_once()
    // is re-executed by an enclosing loop.
    protocol_main_loop();
}
