#ifndef __MONITOR_H_
#define __MONITOR_H_

#include <XBDRIVE/global.h>

enum class MonitorType : int16_t {
    NONE = 0,
    DATA = 1,
    JSON = 2
};

char* monitor_pos(char* str, size_t size);
char* monitor_vel(char* str, size_t size);
char* monitor_input(char* str, size_t size);
char* monitor_pid(char* str, size_t size);
char* monitor_temp(char* str, size_t size);
char* monitor_vol(char* str, size_t size);
void monitor_once();

#endif