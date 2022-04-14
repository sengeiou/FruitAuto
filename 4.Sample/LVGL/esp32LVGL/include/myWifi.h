#ifndef __MYWIFI_H
#define __MYWIFI_H
#include <WiFi.h>

void wifiConnect(char *wifi_ssid, char *pwd);
void wifiInit(lv_obj_t *d);
void wifiLoad();

#endif
