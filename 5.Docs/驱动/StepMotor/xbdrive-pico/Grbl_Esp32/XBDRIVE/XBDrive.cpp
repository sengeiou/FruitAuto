#include "XBDrive.h"

XBDrive::XBDrive() {}

XBDrive::~XBDrive() {}

void temp() {}

#define SUPPORT_TASK_CORE 0  // Reference: CONFIG_ARDUINO_RUNNING_CORE = 1
static TaskHandle_t initTaskHandle = 0;

class XBDrive;

void initTask(void* pvParameters) {
    // 指示灯初始化
    LED.begin(LED_PIN);
    // 编码器初始化
    EncoderInit_t EncoderInit;
    EncoderInit.cs   = ENC_CSN_PIN;
    EncoderInit.sck  = ENC_SCK_PIN;
    EncoderInit.miso = ENC_SDO_PIN;
    EncoderInit.mosi = ENC_SDI_PIN;
    if (!Encoder.begin(&EncoderInit)) {
        DEBUG_port->printf("Encoder initialization failed! \r\n");
    }
    Encoder.setHwCs(true);
    // 零位信号初始化
    zerosignal_init();
    // 线圈初始化
    DriversInit_t DriversInitA, DriversInitB;
    DriversInitA._IN1Pin = A_PHASE_IN1_PIN;
    DriversInitA._IN2Pin = A_PHASE_IN2_PIN;
    DriversInitA._refPin = A_PHASE_VREF_DAC_PIN;
    if (!CoilA.begin(&DriversInitA)) {
        DEBUG_port->printf("Coli A initialization failed! \r\n");
    }
    DriversInitB._IN1Pin = B_PHASE_IN1_PIN;
    DriversInitB._IN2Pin = B_PHASE_IN2_PIN;
    DriversInitB._refPin = B_PHASE_VREF_DAC_PIN;
    if (!CoilB.begin(&DriversInitB)) {
        DEBUG_port->printf("Coli B initialization failed! \r\n");
    }
    // 矫正表初始化
    if (!CaliTab.begin()) {
        DEBUG_port->printf("Calibration table initialization failed! \r\n");
    }
    // 矫正表加载
    if (!CaliTab.loadCaliTable()) {
        DEBUG_port->printf("Calibration table load failed! \r\n");
    }
    // for (int i = 0; i < CALITABLE_LENGTH / 100; i++)
    //     DEBUG_port->printf("%d,", CaliTab.get(i));
    // DEBUG_port->printf("Calibrate End!\r\n");
    // 运行模式初始化
    OperationalModeInit_t OperationalModeInit;
    OperationalModeInit._OperationalModeCheak = powerOnCheck;
    OperationalMode.begin(&OperationalModeInit);
    // 控制器初始化
    // -定时器回调
    StepCtrl.begin(ControlerLoop_callback);
    // 步进输入初始化
    // -外部中断回调
    StepperInputInit_t StepperInputInit;
    StepperInputInit._ENN_callBack     = ENN_IRQHandler;
    StepperInputInit._ENN_Pin          = ENN_PIN;
    StepperInputInit._ENN_Active_Level = LOW;
    StepperInputInit._STEP_Pin         = STEP_PIN;
    StepperInputInit._DIR_Pin          = DIR_PIN;
    if (!StepperInput.begin(&StepperInputInit)) {
        DEBUG_port->printf("S/D接口初始化失败！\r\n");
    }
    // 温度传感器
    TempSensor.begin(TEMPSENSOR_ADC_CHANNEL);
    // 电压传感器
    PowerVoltage.begin(VOLSAMP_ADC_CHANNEL);
    //
    delay(200);
    //任务的删除
    vTaskDelete(NULL);

    while (1)
        delay(10);
}

void XBDrive::setup() {
    xTaskCreatePinnedToCore(initTask,    // task
                            "initTask",  // name for task
                            8192,        // size of task stack
                            NULL,        // parameters
                            1,           // priority
                            &initTaskHandle,
                            SUPPORT_TASK_CORE  // must run the task on same core
                                               // core
    );
    delay(2000);
}

void XBDrive::loop() {
    delay(monitor_delay->get());
    monitor_once();
}

XBDrive xbdrive;