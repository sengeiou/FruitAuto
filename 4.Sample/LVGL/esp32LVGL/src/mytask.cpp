#include <Arduino.h>
#include "mytask.h"
#include "uiAction.h"
#include "myWifi.h"

void taskOne(void *p)
{
    button_wifisacn_init();
    button_wificonnect_init();
    lv_pwd_init();
    dropdown_wifiselect_build("Wifi SSID");
    wifiLoad();
    for (;;)
    {
        delay(500);
        int n = WiFi.scanComplete(); //获取扫描状态
        if (n >= 0)
        {
            // WifiList = "";
            Serial.println("扫描完成");
            if(n > 10) n = 10;
            for (int i = 0; i < n; i++)
            {
                wifiSSID_dd_add((char *)WiFi.SSID(i).c_str(), i);
            }
            WiFi.scanDelete(); //清除内存中的扫描结果
            //return;
        }
        else if (n == -1)
        {
            Serial.println("正在扫描");
        }
        else if (n == -2)
        {
            Serial.println("未进行扫描");
        }
    }
}
