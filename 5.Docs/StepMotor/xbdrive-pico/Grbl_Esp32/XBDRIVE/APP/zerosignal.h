#ifndef __ZEROSIGNAL_H_
#define __ZEROSIGNAL_H_

#include <XBDRIVE/global.h>

// zerosignal Binary Semaphore
extern SemaphoreHandle_t zerosignal_sem;

void zerosignal_init();

#endif