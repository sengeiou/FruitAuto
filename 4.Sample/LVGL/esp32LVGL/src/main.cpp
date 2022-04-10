#include <lvgl.h>
#include <TFT_eSPI.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "mytask.h"

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

/*Change to your screen resolution*/
static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

hw_timer_t *timer = NULL;
const int Timeout = 50; // ms

#if USE_LV_LOG != 0
/* Serial debugging */
void my_print(lv_log_level_t level, const char * file, uint32_t line, const char * dsc)
{

    Serial.printf("%s@%d->%s\r\n", file, line, dsc);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
   uint32_t w = (area->x2 - area->x1 + 1);
   uint32_t h = (area->y2 - area->y1 + 1);

   tft.startWrite();
   tft.setAddrWindow(area->x1, area->y1, w, h);
   tft.pushColors((uint16_t *)&color_p->full, w * h, true);
   tft.endWrite();

   lv_disp_flush_ready(disp);
}

void IRAM_ATTR onTimer()
{
   
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
   uint16_t touchX, touchY;

   bool touched = tft.getTouch(&touchX, &touchY, 600);

   if (!touched)
   {
      data->state = LV_INDEV_STATE_REL;
   }
   else
   {
      data->state = LV_INDEV_STATE_PR;
      /*Set the coordinates*/
      data->point.x = touchX;
      data->point.y = touchY;

      Serial.print("Data x ");
      Serial.println(touchX);

      Serial.print("Data y ");
      Serial.println(touchY);
   }
}


void setup()
{
   Serial.begin(115200); /* prepare for possible serial debug */
   Serial.println("Hello Arduino! (V8.2.X)");
   Serial.println("I am LVGL_Arduino");

   lv_init();
   
#if USE_LV_LOG != 0
   lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif
   tft.begin();        /* TFT init */
   tft.setRotation(1); /* Landscape orientation, flipped */

   /*Set the touchscreen calibration data,
     the actual data for your display can be aquired using
     the Generic -> Touch_calibrate example from the TFT_eSPI library*/
   uint16_t calData[5] = {442, 3414, 336, 3425, 3};
   tft.setTouch(calData);

   lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

   /*Initialize the display*/
   static lv_disp_drv_t disp_drv;
   lv_disp_drv_init(&disp_drv);
   /*Change the following line to your display resolution*/
   disp_drv.hor_res = screenWidth;
   disp_drv.ver_res = screenHeight;
   disp_drv.flush_cb = my_disp_flush;
   disp_drv.draw_buf = &draw_buf;
   lv_disp_drv_register(&disp_drv);

   /*Initialize the (dummy) input device driver*/
   static lv_indev_drv_t indev_drv;
   lv_indev_drv_init(&indev_drv);
   indev_drv.type = LV_INDEV_TYPE_POINTER;
   indev_drv.read_cb = my_touchpad_read;
   lv_indev_drv_register(&indev_drv);

   /* Create simple label */
   // lv_obj_t *label = lv_label_create(lv_scr_act());
   // lv_label_set_text(label, "Hello Arduino! (V8.2.0)");
   // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
   //  lv_obj2_t *button = create
   //lv_example_textarea_2();
   Serial.println("Setup done");
   
   xTaskCreatePinnedToCore(
       taskOne //任务函数
       ,
       "Task1" /* 任务名字 没啥用，就是描述*/
       ,
       40960 /*堆栈大小，单位为字节*/
       ,
       NULL /*作为任务输入传递的参数*/
       ,
       1 // /*任务的优先级*/Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
       ,
       NULL, ARDUINO_RUNNING_CORE); //指定运行任务的CPU
}

void loop()
{
   lv_task_handler(); /* LVGL 工作函数 */
   lv_tick_inc(5);
   delay(5);
}
