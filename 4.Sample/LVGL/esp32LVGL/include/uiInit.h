#ifndef __UI_INIT_H
#define __UI_INIT_H
#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>

/*Change to your screen resolution*/
static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void my_ui_init();

#endif
