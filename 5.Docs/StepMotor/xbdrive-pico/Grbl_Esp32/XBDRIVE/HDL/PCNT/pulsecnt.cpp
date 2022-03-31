/********************************************************************************
* @Filename:        pulsecnt.cpp
* @Author:          
* @Version:         ver1.0
* @Date:            2021-5-9
* @Description:     
* @History:         
********************************************************************************/
#include "pulsecnt.h"
pcnt_unit_t o_PCNT_Unit;
int PCNT_DIR_flg = 0;
uint32_t H_overflow = 0;
uint32_t L_overflow = 0;

static void IRAM_ATTR pcnt_example_intr_handler(void *arg)
{
    int16_t count;
    pcnt_get_counter_value(o_PCNT_Unit, &count);
    if (count > 0)
    {
        PCNT_DIR_flg = 1;
    }
    else if (count < 0)
    {
        PCNT_DIR_flg = -1;
    }
    else
    {
        if (PCNT_DIR_flg == 1)
        {
            H_overflow++;
        }
        else if (PCNT_DIR_flg == -1)
        {
            L_overflow++;
        }
        PCNT_DIR_flg = 0;
    }
}

PulseCNTClass::PulseCNTClass()
{
}
PulseCNTClass::~PulseCNTClass()
{
}

bool PulseCNTClass::init(PulseCNTInit_t *PulseCNTInit)
{
    return init(PulseCNTInit->_PCNT_Pulse_Pin, PulseCNTInit->_PCNT_Dir_Pin, PulseCNTInit->_maxcnt, PulseCNTInit->_PCNT_Unit);
}

bool PulseCNTClass::init(uint8_t _PCNT_Pulse_Pin, uint8_t _PCNT_Dir_Pin, int16_t _maxcnt, pcnt_unit_t _PCNT_Unit)
{
    esp_err_t res = 0;
    // 判断传入参数合法性
    if (_PCNT_Pulse_Pin == GPIO_NUM_MAX)
    {
        res++;
    }
    if (_PCNT_Dir_Pin == GPIO_NUM_MAX)
    {
        res++;
    }
    if (_maxcnt == 0)
    {
        res++;
    }
    // if(_PCNT_Unit != PCNT_CHANNEL_0 && _PCNT_Unit != PCNT_CHANNEL_1)return false;
    // 参数传递
    PCNT_Pulse_Pin = _PCNT_Pulse_Pin;
    PCNT_Dir_Pin = _PCNT_Dir_Pin;
    PCNT_Unit = _PCNT_Unit;
    maxcnt = _maxcnt;
    // 外部变量初始化
    o_PCNT_Unit = _PCNT_Unit;
    // 变量初始化
    PCNT_DIR_flg = 0;
    H_overflow = 0;
    L_overflow = 0;
    // 配置pcnt单元
    pcnt_config_t pcnt_config = {
        .pulse_gpio_num = PCNT_Pulse_Pin,
        .ctrl_gpio_num = PCNT_Dir_Pin,
        // What to do when control input is low or high?
        .lctrl_mode = PCNT_MODE_KEEP,    // 低电平增量计数
        .hctrl_mode = PCNT_MODE_REVERSE, // 高电平逆转计数方向
        // What to do on the positive / negative edge of pulse input?
        .pos_mode = PCNT_COUNT_INC, // 上升沿增量计数
        .neg_mode = PCNT_COUNT_DIS, // 忽略下降沿
        // Set the maximum and minimum limit values to watch
        .counter_h_lim = (int16_t)maxcnt,
        .counter_l_lim = (int16_t)(-maxcnt),
        .unit = PCNT_Unit,
        .channel = PCNT_CHANNEL_0,
    };
    res += pcnt_unit_config(&pcnt_config);
    // 低通滤波器
    //pcnt_set_filter_value(PCNT_Unit, 10);
    //pcnt_filter_enable(PCNT_Unit);
    // 阈值事件0
    res += pcnt_set_event_value(PCNT_Unit, PCNT_EVT_THRES_0, maxcnt * 0.9);
    res += pcnt_event_enable(PCNT_Unit, PCNT_EVT_THRES_0);
    // 阈值事件1
    res += pcnt_set_event_value(PCNT_Unit, PCNT_EVT_THRES_1, -maxcnt * 0.9);
    res += pcnt_event_enable(PCNT_Unit, PCNT_EVT_THRES_1);
    // H溢出事件
    res += pcnt_event_enable(PCNT_Unit, PCNT_EVT_H_LIM);
    // L溢出事件
    res += pcnt_event_enable(PCNT_Unit, PCNT_EVT_L_LIM);
    // 暂停计数
    res += pcnt_counter_pause(PCNT_Unit);
    // 计数置0
    res += pcnt_counter_clear(PCNT_Unit);
    // 初始化中断服务和添加中断回调处理程序
    // Install interrupt service and add isr callback handler
    res += pcnt_isr_service_install(0);
    res += pcnt_isr_handler_add(PCNT_Unit, pcnt_example_intr_handler, (void *)PCNT_Unit);
    // 开始计数
    // Everything is set up, now go to counting
    res += pcnt_counter_resume(PCNT_Unit);

    return !res;
}

bool PulseCNTClass::begin()
{
    esp_err_t res = 0;

    PCNT_DIR_flg = 0;
    H_overflow = 0;
    L_overflow = 0;

    res += pcnt_counter_pause(PCNT_Unit);
    res += pcnt_counter_clear(PCNT_Unit);
    res += pcnt_counter_resume(PCNT_Unit);

    return !res;
}

bool PulseCNTClass::pause()
{
    return !pcnt_counter_pause(PCNT_Unit);
}

bool PulseCNTClass::resume()
{
    return !pcnt_counter_resume(PCNT_Unit);
}

bool PulseCNTClass::end()
{
    esp_err_t res = 0;
    res += pcnt_counter_pause(PCNT_Unit);
    res += pcnt_counter_clear(PCNT_Unit);

    return !res;
}
bool PulseCNTClass::clear()
{
    PCNT_DIR_flg = 0;
    H_overflow = 0;
    L_overflow = 0;
    return !pcnt_counter_clear(PCNT_Unit);
}
int32_t PulseCNTClass::getCnt()
{
    int16_t count;
    pcnt_get_counter_value(PCNT_Unit, &count);
    return (H_overflow - L_overflow) * maxcnt + count;
}

PulseCNTInit_t::PulseCNTInit_t()
{
    _PCNT_Pulse_Pin = GPIO_NUM_MAX;
    _PCNT_Dir_Pin = GPIO_NUM_MAX;
    _maxcnt = 2000;
    _PCNT_Unit = PCNT_UNIT_0;
}