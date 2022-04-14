#ifndef __UIACTION_H
#define __UIACTION_H

#include <Arduino.h>
#include "lvgl.h"

//static void event_handler_dropdown(lv_event_t *e);
//static void event_handler_button(lv_event_t *e);
//static void ta_event_cb(lv_event_t *e);
void button_wifisacn_init(void);
void button_wificonnect_init(void);
void lv_example_img(void);
void lv_pwd_init(void);
void dropdown_wifiselect_build(const char *s);
void wifiSSID_dd_add(const char *s, int i);

#endif

