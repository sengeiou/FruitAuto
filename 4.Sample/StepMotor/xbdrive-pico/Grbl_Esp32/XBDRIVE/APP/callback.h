#ifndef __CALLBACK_H_
#define __CALLBACK_H_

#include <XBDRIVE/global.h>

void IRAM_ATTR ControlerLoop_callback(void);
void           ENN_IRQHandler(void);
bool switchControlMode_callback(char *val);
bool switchMicrosteps_callback(char *val);
bool switchMonitortype_callback(char* val);
bool setPose_kp_callback(char *val);
bool setPose_ki_callback(char *val);
bool setPose_kd_callback(char *val);
#endif