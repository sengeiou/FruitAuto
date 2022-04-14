#include <lvgl.h>
#include <TFT_eSPI.h>
#include "uiInit.h"
#include "mytask.h"
#include <FreeRTOS.h>



#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif


void setup()
{
   Serial.begin(115200); /* prepare for possible serial debug */
   Serial.println("Hello Arduino! (V8.2.X)");
   Serial.println("I am LVGL_Arduino");
   my_ui_init();
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
   Serial.println("xTaskCreatePinnedToCore Done");
}

void loop()
{
   lv_task_handler(); /* LVGL 工作函数 */
   lv_tick_inc(5);
   delay(5);
}
