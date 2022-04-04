#include "monitor.h"
#include <XBDRIVE/global.h>
#include <src/Grbl.h>

char* monitor_pos(char* str, size_t size) {
    StaticJsonDocument<1024> doc;
    JsonObject               XBoard = doc.createNestedObject("XBDrive");
    XBoard["code"]                  = 0;
    XBoard["id"]                    = (uint16_t)(ESP.getEfuseMac() >> 32);
    // pos
    JsonObject pos  = XBoard.createNestedObject("pos");
    pos["measured"] = motor_pos;
    pos["setpoint"] = motor_pos_set;

    serializeJson(doc, str, size);

    doc.clear();
    return str;
}

char* monitor_vel(char* str, size_t size) {
    StaticJsonDocument<1024> doc;
    JsonObject               XBoard = doc.createNestedObject("XBDrive");
    XBoard["code"]                  = 1;
    XBoard["id"]                    = (uint16_t)(ESP.getEfuseMac() >> 32);
    // vel
    JsonObject vel = XBoard.createNestedObject("vel");
    vel["vel_M"]   = get_vel_M();
    vel["vel_T"]   = get_vel_T();
    vel["vel"]     = get_vel();
    vel["vel_FLT"] = get_vel_flt();

    serializeJson(doc, str, size);

    doc.clear();
    return str;
}

char* monitor_input(char* str, size_t size) {
    StaticJsonDocument<1024> doc;
    JsonObject               XBoard = doc.createNestedObject("XBDrive");
    XBoard["code"]                  = 2;
    XBoard["id"]                    = (uint16_t)(ESP.getEfuseMac() >> 32);
    // input
    JsonObject input = XBoard.createNestedObject("input");
    input["ENN"]     = StepperInput.IsEnlable() ? "Enalbe" : "Disable";
    input["DIR"]     = StepperInput.IsCCW() ? "CW" : "CCW";
    input["STEP"]    = StepperInput.GetIntputPulse();

    serializeJson(doc, str, size);

    doc.clear();
    return str;
}

char* monitor_pid(char* str, size_t size) {
    StaticJsonDocument<1024> doc;
    JsonObject               XBoard = doc.createNestedObject("XBDrive");
    XBoard["code"]                  = 3;
    XBoard["id"]                    = (uint16_t)(ESP.getEfuseMac() >> 32);
    // pid
    JsonObject pid = XBoard.createNestedObject("pid");
    pid["err"]     = motor_pos_err;
    pid["it"]      = pid_iterm;
    pid["dt"]      = pid_dterm;

    serializeJson(doc, str, size);

    doc.clear();
    return str;
}

char* monitor_temp(char* str, size_t size) {
    StaticJsonDocument<1024> doc;
    JsonObject               XBoard = doc.createNestedObject("XBDrive");
    XBoard["code"]                  = 4;
    XBoard["id"]                    = (uint16_t)(ESP.getEfuseMac() >> 32);
    XBoard["temp"]                  = TempSensor.GetTemp();

    serializeJson(doc, str, size);

    doc.clear();
    return str;
}

char* monitor_vol(char* str, size_t size) {
    StaticJsonDocument<1024> doc;
    JsonObject               XBoard = doc.createNestedObject("XBDrive");
    XBoard["code"]                  = 5;
    XBoard["id"]                    = (uint16_t)(ESP.getEfuseMac() >> 32);
    XBoard["vol"]                   = PowerVoltage.GetVolt();

    serializeJson(doc, str, size);

    doc.clear();
    return str;
}


uint8_t head[2] = { 0x03, 0xfc };
uint8_t tail[2] = { 0xfc, 0x03 };
int32_t tempdata;
uint8_t temparr[4];
char    tempstring[200];

void monitor_once() {
    switch ((int16_t)Monitor_Type->get()) {
        case (int16_t)MonitorType::DATA:
            DEBUG_port->write(head, 2);
            if (monitor_vel_enable->get()) {
                tempdata = get_vel();
                temparr[0]   = 0x000000ff & (tempdata);
                temparr[1]   = 0x000000ff & (tempdata >> 8);
                temparr[2]   = 0x000000ff & (tempdata >> 16);
                temparr[3]   = 0x000000ff & (tempdata >> 24);
                DEBUG_port->write(temparr, 4);
            }
            if (monitor_pos_enable->get()) {
                tempdata = motor_pos;
                temparr[0]   = 0x000000ff & (tempdata);
                temparr[1]   = 0x000000ff & (tempdata >> 8);
                temparr[2]   = 0x000000ff & (tempdata >> 16);
                temparr[3]   = 0x000000ff & (tempdata >> 24);
                DEBUG_port->write(temparr, 4);
            }
            if (monitor_input_enable->get()) {
                tempdata = motor_pos_set;
                temparr[0]   = 0x000000ff & (tempdata);
                temparr[1]   = 0x000000ff & (tempdata >> 8);
                temparr[2]   = 0x000000ff & (tempdata >> 16);
                temparr[3]   = 0x000000ff & (tempdata >> 24);
                DEBUG_port->write(temparr, 4);
            }
            if (monitor_pid_enable->get()) {
                tempdata = motor_pos_err;
                temparr[0]   = 0x000000ff & (tempdata);
                temparr[1]   = 0x000000ff & (tempdata >> 8);
                temparr[2]   = 0x000000ff & (tempdata >> 16);
                temparr[3]   = 0x000000ff & (tempdata >> 24);
                DEBUG_port->write(temparr, 4);
                tempdata = pid_iterm;
                temparr[0]   = 0x000000ff & (tempdata);
                temparr[1]   = 0x000000ff & (tempdata >> 8);
                temparr[2]   = 0x000000ff & (tempdata >> 16);
                temparr[3]   = 0x000000ff & (tempdata >> 24);
                DEBUG_port->write(temparr, 4);
                tempdata = pid_dterm;
                temparr[0]   = 0x000000ff & (tempdata);
                temparr[1]   = 0x000000ff & (tempdata >> 8);
                temparr[2]   = 0x000000ff & (tempdata >> 16);
                temparr[3]   = 0x000000ff & (tempdata >> 24);
                DEBUG_port->write(temparr, 4);
            }
            if (monitor_temp_enable->get()) {
                tempdata = (int32_t)TempSensor.GetTemp();
                temparr[0]   = 0x000000ff & (tempdata);
                temparr[1]   = 0x000000ff & (tempdata >> 8);
                temparr[2]   = 0x000000ff & (tempdata >> 16);
                temparr[3]   = 0x000000ff & (tempdata >> 24);
                DEBUG_port->write(temparr, 4);
            }
            if (monitor_vol_enable->get()) {
                tempdata = (int32_t)PowerVoltage.GetVolt();
                temparr[0]   = 0x000000ff & (tempdata);
                temparr[1]   = 0x000000ff & (tempdata >> 8);
                temparr[2]   = 0x000000ff & (tempdata >> 16);
                temparr[3]   = 0x000000ff & (tempdata >> 24);
                DEBUG_port->write(temparr, 4);
            }
            DEBUG_port->write(tail, 2);
            break;
        case (int16_t)MonitorType::JSON:
            if (monitor_vel_enable->get()) {
                DEBUG_port->println(monitor_vel(tempstring, 200));
            }
            if (monitor_pos_enable->get()) {
                DEBUG_port->println(monitor_pos(tempstring, 200));
            }
            if (monitor_input_enable->get()) {
                DEBUG_port->println(monitor_input(tempstring, 200));
            }
            if (monitor_pid_enable->get()) {
                DEBUG_port->println(monitor_pid(tempstring, 200));
            }
            if (monitor_temp_enable->get()) {
                DEBUG_port->println(monitor_temp(tempstring, 200));
            }
            if (monitor_vol_enable->get()) {
                DEBUG_port->println(monitor_vol(tempstring, 200));
            }
            break;
    }
}
