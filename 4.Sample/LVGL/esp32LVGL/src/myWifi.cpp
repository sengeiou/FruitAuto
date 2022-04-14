#include <Arduino.h>
#include "lvgl.h"
#include "myWifi.h"
#include <FreeRTOS.h>
void wifiLoad()
{
    WiFi.mode(WIFI_STA);
}

char **list;

void _wc(void *p)
{

    Serial.printf("ssid=%s, pwd=%s\n", list[0], list[1]);
    WiFi.begin(list[0], list[1]);
    // lv_example_arc();
    while (WiFi.status() != WL_CONNECTED) //等待网络连接成功
    {
        delay(500);
        Serial.printf("%d\n", WiFi.status());
    }
    // lv_obj_del(arc);

    Serial.println("WiFi connected!");
}

void wifiConnect(char *wifi_ssid, char *pwd)
{
    list[0] = wifi_ssid;
    list[1] = pwd;

    Serial.println("WiFi wifiConnect");

    // WiFi.begin(wifi_ssid, lv_textarea_get_text(pwd_ta)); //连接网络
    xTaskCreatePinnedToCore(_wc, "Task2", 5120, NULL, 1, NULL, 1);
    // lv_example_img();
    //_wc();
}

void wifiInit(lv_obj_t *d)
{
    WiFi.disconnect();
    WiFi.scanNetworks(true);
}
