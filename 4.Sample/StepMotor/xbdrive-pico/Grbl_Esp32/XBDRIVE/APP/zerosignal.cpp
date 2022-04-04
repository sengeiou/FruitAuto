#include "zerosignal.h"

// zerosignal Task
TaskHandle_t zerosignalTaskHandle = NULL;

// zerosignal Binary Semaphore
SemaphoreHandle_t zerosignal_sem = NULL;

void zerosignal_entry(void *pvParameters)
{
    BaseType_t err;
    while (1)
    {
        if (zerosignal_sem != NULL)
        {
            err = xSemaphoreTake(zerosignal_sem, portMAX_DELAY);
            if (err == pdPASS)
            {
                //Serial.println("zerosignal test");
            }
            else
            {
                //Serial.println("zerosignal error");
            }
        }

        delay(10);
    }
}

void zerosignal_init()
{
    // 创建二值信号量
    zerosignal_sem = xSemaphoreCreateBinary();
    // 创建接收任务
    xTaskCreatePinnedToCore(zerosignal_entry, // task
                            "zerosignal",     // name for task
                            4096,             // size of task stack
                            NULL,             // parameters
                            1,                // priority
                            &zerosignalTaskHandle,
                            CONFIG_ARDUINO_RUNNING_CORE);
}