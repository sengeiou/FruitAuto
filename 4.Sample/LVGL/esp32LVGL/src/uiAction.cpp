#include "uiAction.h"
#include "myWifi.h"

lv_obj_t *dd;
lv_obj_t *btnWifiScan;
lv_obj_t *btnWifiConnect;
lv_obj_t *kb;
lv_obj_t *pwd_ta;

char wifi_ssid[32];
char wifi_pwd[32];

static void event_handler_dropdown(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        lv_dropdown_get_selected_str(obj, wifi_ssid, sizeof(wifi_ssid));
        Serial.printf("Option: %s\n", wifi_ssid);
    }
}

static void event_handler_button(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);

    if (code == LV_EVENT_CLICKED)
    {
        // LV_LOG_USER("Clicked");
        if (btn == btnWifiConnect)
        {
            *wifi_pwd = *lv_textarea_get_text(pwd_ta);
            if (wifi_ssid == NULL || wifi_pwd == NULL)
            {
                return;
            }
            wifiConnect(wifi_ssid, wifi_pwd);
        }
        if (btn == btnWifiScan)
        {
            wifiInit(dd);
        }
    }
}

static void ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED)
    {
        /*Focus on the clicked text area*/
        if (kb != NULL)
            lv_keyboard_set_textarea(kb, ta);
    }

    else if (code == LV_EVENT_READY)
    {
        LV_LOG_USER("Ready, current text: %s", lv_textarea_get_text(ta));
    }
}

void lv_pwd_init(void)
{
    /*Create the password box*/
    pwd_ta = lv_textarea_create(lv_scr_act());
    lv_textarea_set_text(pwd_ta, "");
    lv_textarea_set_password_mode(pwd_ta, true);
    lv_textarea_set_one_line(pwd_ta, true);
    lv_obj_set_width(pwd_ta, 200);
    lv_obj_set_pos(pwd_ta, 5, 50);
    lv_obj_add_event_cb(pwd_ta, ta_event_cb, LV_EVENT_ALL, NULL);

    /*Create a label and position it above the text box*/
    lv_obj_t *pwd_label = lv_label_create(lv_scr_act());
    lv_label_set_text(pwd_label, "Password:");
    lv_obj_align_to(pwd_label, pwd_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 60);

    kb = lv_keyboard_create(lv_scr_act());
    lv_obj_set_size(kb, LV_HOR_RES, LV_VER_RES / 2);
    lv_keyboard_set_textarea(kb, pwd_ta); /*Focus it on one of the text areas to start*/
}

void button_wifisacn_init(void)
{
    lv_obj_t *label;

    btnWifiScan = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btnWifiScan, event_handler_button, LV_EVENT_ALL, NULL);
    lv_obj_align(btnWifiScan, LV_ALIGN_TOP_RIGHT, -5, 5);

    label = lv_label_create(btnWifiScan);
    lv_label_set_text(label, "Scan Wifi");
    lv_obj_center(label);
}

void button_wificonnect_init(void)
{
    lv_obj_t *label;

    btnWifiConnect = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btnWifiConnect, event_handler_button, LV_EVENT_ALL, NULL);
    lv_obj_align(btnWifiConnect, LV_ALIGN_TOP_RIGHT, -5, 50);

    label = lv_label_create(btnWifiConnect);
    lv_label_set_text(label, "Connect");
    lv_obj_center(label);
}

void lv_example_img(void)
{
    LV_IMG_DECLARE(wifisuccess);
    lv_obj_t *img1 = lv_img_create(lv_scr_act());
    lv_img_set_src(img1, &wifisuccess);
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(img1, 200, 250);
}

void dropdown_wifiselect_build(const char *s)
{
    /*Create a normal drop down list*/
    dd = lv_dropdown_create(lv_scr_act());
    lv_obj_set_width(dd, 200);
    lv_dropdown_set_options(dd, s);
    lv_obj_align(dd, LV_ALIGN_TOP_LEFT, 5, 5);
    lv_obj_add_event_cb(dd, event_handler_dropdown, LV_EVENT_ALL, NULL);
}

void wifiSSID_dd_add(const char *s, int i)
{
    lv_dropdown_add_option(dd, s, i);
}