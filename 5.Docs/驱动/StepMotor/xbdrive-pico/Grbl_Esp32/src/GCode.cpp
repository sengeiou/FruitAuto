/*
  GCode.cpp - rs274/ngc parser.
  Part of Grbl

  Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud

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

// Allow iteration over CoordIndex values
CoordIndex& operator++(CoordIndex& i) {
    i = static_cast<CoordIndex>(static_cast<uint8_t>(i) + 1);
    return i;
}

// NOTE: Max line number is defined by the g-code standard to be 99999. It seems to be an
// arbitrary value, and some GUIs may require more. So we increased it based on a max safe
// value when converting a float (7.2 digit precision)s to an integer.
static const int32_t MaxLineNumber = 10000000;
static const uint8_t MaxToolNumber = 255;  // Limited by max unsigned 8-bit value

// Declare gc extern struct
parser_state_t gc_state;
parser_block_t gc_block;

#define FAIL(status) return (status);

// Edit GCode line in-place, removing whitespace and comments and
// converting to uppercase
void collapseGCode(char* line) {
    // parenPtr, if non-NULL, is the address of the character after (
    char* parenPtr = NULL;
    // outPtr is the address where newly-processed characters will be placed.
    // outPtr is alway less than or equal to inPtr.
    char* outPtr = line;
    char  c;
    for (char* inPtr = line; (c = *inPtr) != '\0'; inPtr++) {
        if (isspace(c)) {
            continue;
        }
        switch (c) {
            case ')':
                if (parenPtr) {
                    // Terminate comment by replacing ) with NUL
                    *inPtr = '\0';
                    report_gcode_comment(parenPtr);
                    parenPtr = NULL;
                }
                // Strip out ) that does not follow a (
                break;
            case '(':
                // Start the comment at the character after (
                parenPtr = inPtr + 1;
                break;
            case ';':
                // NOTE: ';' comment to EOL is a LinuxCNC definition. Not NIST.
#ifdef REPORT_SEMICOLON_COMMENTS
                report_gcode_comment(inPtr + 1);
#endif
                *outPtr = '\0';
                return;
            case '%':
                // TODO: Install '%' feature
                // Program start-end percent sign NOT SUPPORTED.
                // NOTE: This maybe installed to tell Grbl when a program is running vs manual input,
                // where, during a program, the system auto-cycle start will continue to execute
                // everything until the next '%' sign. This will help fix resuming issues with certain
                // functions that empty the planner buffer to execute its task on-time.
                break;
            case '\r':
                // In case one sneaks in
                break;
            default:
                if (!parenPtr) {
                    *outPtr++ = toupper(c);  // make upper case
                }
        }
    }
    // On loop exit, *inPtr is '\0'
    if (parenPtr) {
        // Handle unterminated ( comments
        report_gcode_comment(parenPtr);
    }
    *outPtr = '\0';
}

// Executes one line of NUL-terminated G-Code.
// The line may contain whitespace and comments, which are first removed,
// and lower case characters, which are converted to upper case.
// In this function, all units and positions are converted and
// exported to grbl's internal functions in terms of (mm, mm/min) and absolute machine
// coordinates, respectively.
Error gc_execute_line(char* line, uint8_t client) {
    return Error::Ok;
}

/*
  Not supported:

  - Canned cycles
  - Tool radius compensation
  - A,B,C-axes
  - Evaluation of expressions
  - Variables
  - Override control (TBD)
  - Tool changes
  - Switches

   (*) Indicates optional parameter, enabled through config.h and re-compile
   group 0 = {G92.2, G92.3} (Non modal: Cancel and re-enable G92 offsets)
   group 1 = {G81 - G89} (Motion modes: Canned cycles)
   group 4 = {M1} (Optional stop, ignored)
   group 6 = {M6} (Tool change)
   group 7 = {G41, G42} cutter radius compensation (G40 is supported)
   group 8 = {G43} tool length offset (G43.1/G49 are supported)
   group 8 = {M7*} enable mist coolant (* Compile-option)
   group 9 = {M48, M49} enable/disable feed and speed override switches
   group 10 = {G98, G99} return mode canned cycles
   group 13 = {G61.1, G64} path control mode (G61 is supported)
*/
