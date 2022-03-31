#include "calibration.h"
#include <src/Grbl.h>

//编码器校正函数
void EncoderCalibrating(void) {
    int32_t encoderVal        = 0;
    int32_t currentEncoderVal = 0;
    int32_t iStart            = 0;
    int32_t jStart            = 0;
    int32_t stepNo            = 0;
    int32_t estimated_value   = 0;
    // 一圈200整步的编码器值数组
    // int32_t fullStepVal[motor_full_steps_per_rev->get()];
    int32_t* fullStepVal = (int32_t*)malloc(motor_full_steps_per_rev->get() * sizeof(int32_t));
    int32_t  ticks       = 0;
    // 写入位置索引
    uint32_t index = 0;
    uint16_t lookupAngle;
    dir = 1;
    Serial.printf("Calibrate Start!\r\n");
    // 开始时固定在整步位置
    Output(0, calibration_mode_current_max_ma->get());
    // 闪烁提示开始
    for (int16_t i = 0; i < 4; i++) {
        LED.set(HIGH);
        delay(250);
        LED.set(LOW);
        delay(250);
    }
    // 逆时针跑一圈记下各整步位的值
    Serial.printf("Anticlockwise Motion Start!\r\n");
    for (int16_t i = 0; i < motor_full_steps_per_rev->get(); i++) {
        encoderVal      = 0;
        estimated_value = Encoder.ReadAngleHwCsYORO();
        if (estimated_value < ENCODER_CNT_PER_REV * 0.1 || estimated_value > ENCODER_CNT_PER_REV * 0.9) {
            // 多次读取取平均值
            for (uint8_t reading = 0; reading < 10; reading++) {
                currentEncoderVal = Encoder.ReadAngleHwCsYORO();
                // 溢出处理
                if (currentEncoderVal < ENCODER_CNT_PER_REV * 0.2) {
                    currentEncoderVal += ENCODER_CNT_PER_REV / 2;
                } else if (currentEncoderVal > ENCODER_CNT_PER_REV * 0.8) {
                    currentEncoderVal -= ENCODER_CNT_PER_REV / 2;
                }
                // 角度累积
                encoderVal += currentEncoderVal;
                delay(2);
            }
            encoderVal = (encoderVal / 10 + ENCODER_CNT_PER_REV / 2) % ENCODER_CNT_PER_REV;
        } else {
            // 多次读取取平均值
            for (uint8_t reading = 0; reading < 10; reading++) {
                currentEncoderVal = Encoder.ReadAngleHwCsYORO();
                // 角度累积
                encoderVal += currentEncoderVal;
                delay(2);
            }
            encoderVal = encoderVal / 10;
        }
        // Serial.printf("(%d, %d)\t", i, encoderVal);
        fullStepVal[i] = encoderVal;
        OneStep();
    }
    dir = 0;
    OneStep();
    delay(1000);
    Serial.printf("Clockwise Motion Start!\r\n");
    for (int16_t i = (motor_full_steps_per_rev->get() - 1); i >= 0; i--)  //顺时针跑一圈记下各整步位的值和之前逆时针保存的值求平均
    {
        encoderVal      = 0;
        estimated_value = Encoder.ReadAngleHwCsYORO();
        if (estimated_value < ENCODER_CNT_PER_REV * 0.1 || estimated_value > ENCODER_CNT_PER_REV * 0.9) {
            // 多次读取取平均值
            for (uint8_t reading = 0; reading < 10; reading++) {
                currentEncoderVal = Encoder.ReadAngleHwCsYORO();
                // 溢出处理
                if (currentEncoderVal < ENCODER_CNT_PER_REV * 0.2) {
                    currentEncoderVal += ENCODER_CNT_PER_REV / 2;
                } else if (currentEncoderVal > ENCODER_CNT_PER_REV * 0.8) {
                    currentEncoderVal -= ENCODER_CNT_PER_REV / 2;
                }
                // 角度累积
                encoderVal += currentEncoderVal;
                delay(2);
            }
            encoderVal = encoderVal / 10;
            // Serial.printf("(%d, %d, 1)\t", i, (encoderVal + ENCODER_CNT_PER_REV / 2) % ENCODER_CNT_PER_REV);
            // 溢出处理
            if (fullStepVal[i] < ENCODER_CNT_PER_REV * 0.2) {
                fullStepVal[i] += ENCODER_CNT_PER_REV / 2;
            } else if (fullStepVal[i] > ENCODER_CNT_PER_REV * 0.8) {
                fullStepVal[i] -= ENCODER_CNT_PER_REV / 2;
            }
            fullStepVal[i] = ((fullStepVal[i] + encoderVal) / 2 + ENCODER_CNT_PER_REV / 2) % ENCODER_CNT_PER_REV;
        } else {
            // 多次读取取平均值
            for (uint8_t reading = 0; reading < 10; reading++) {
                currentEncoderVal = Encoder.ReadAngleHwCsYORO();
                // 角度累积
                encoderVal += currentEncoderVal;
                delay(2);
            }
            encoderVal = encoderVal / 10;
            // Serial.printf("(%d, %d, 2)\t", i, encoderVal);
            fullStepVal[i] = (fullStepVal[i] + encoderVal) / 2;
        }
        // Serial.printf("(%d, %d)\t", i, fullStepVal[i]);
        OneStep();
    }
    for (int i = 0; i < 200; i++) {
        // Serial.printf("(%d, %d)\t", i, fullStepVal[i]);
    }
    CoilA.free();
    CoilB.free();
    Serial.printf("Save Cali Data Start!\r\n");
    // 寻找编码器0°所在位置
    // Serial.printf("ticks\r\n");
    for (uint8_t i = 0; i < motor_full_steps_per_rev->get(); i++) {
        // 溢出处理
        if (fullStepVal[(i + 1) % motor_full_steps_per_rev->get()] - fullStepVal[i] < 0) {
            ticks = fullStepVal[(i + 1) % motor_full_steps_per_rev->get()] + ENCODER_CNT_PER_REV - fullStepVal[i];
        } else {
            ticks = fullStepVal[(i + 1) % motor_full_steps_per_rev->get()] - fullStepVal[i];
        }
        // Serial.printf("(%d, %d)\t", i, ticks);
        /*
*                 0--1--2...199
*               |--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|...
*                    / ^  \
*                   /  |   \ iStart = 2
*          iStart: |-----...| len: 16384/200
*                     ^
*                     | jStart = 3
*/
        for (int32_t j = 0; j < ticks; j++) {
            stepNo = (fullStepVal[i] + j) % ENCODER_CNT_PER_REV;
            if (stepNo == 0) {
                iStart = i;  // 0扇区
                jStart = j;  // 偏移量
            }
        }
    }
    CaliTab.clear();
    // Serial.printf("iStart: %d, jStart: %d\r\n", iStart, jStart);
    //以步进电机整步为基准（小于0.08度）开始对编码器进行校正插值并将校正后的值存入FLASH
    for (int32_t i = iStart; i < (iStart + motor_full_steps_per_rev->get() + 1); i++) {
        // 溢出处理
        if (fullStepVal[(i + 1) % motor_full_steps_per_rev->get()] - fullStepVal[i % motor_full_steps_per_rev->get()] < 0) {
            ticks = fullStepVal[(i + 1) % motor_full_steps_per_rev->get()] + ENCODER_CNT_PER_REV -
                    fullStepVal[i % motor_full_steps_per_rev->get()];
        } else {
            ticks = fullStepVal[(i + 1) % motor_full_steps_per_rev->get()] - fullStepVal[i % motor_full_steps_per_rev->get()];
        }
        // Serial.printf("ticks: %d, %d\r\n", ticks, (i + 1) % motor_full_steps_per_rev->get());
        if (i == iStart) {
            // 0扇区右边
            for (int32_t j = jStart; j < ticks; j++) {
                // lookupAngle = i*16384/200 + j/tick*16384/200
                lookupAngle = ((ENCODER_CNT_PER_REV)*i + (ENCODER_CNT_PER_REV)*j / ticks) %
                              (ENCODER_CNT_PER_REV * motor_full_steps_per_rev->get()) / motor_full_steps_per_rev->get();
                // lookupAngle = i * ENCODER_CNT_PER_REV / motor_full_steps_per_rev->get() +
                //   j * ENCODER_CNT_PER_REV / ticks / motor_full_steps_per_rev->get();
                CaliTab.set(index, (uint16_t)lookupAngle);
                index++;
                // Serial.print("X");
            }
        } else if (i == (iStart + motor_full_steps_per_rev->get())) {
            // 0扇区左边
            for (int32_t j = 0; j < jStart; j++) {
                lookupAngle = ((ENCODER_CNT_PER_REV)*i + (ENCODER_CNT_PER_REV)*j / ticks) %
                              (ENCODER_CNT_PER_REV * motor_full_steps_per_rev->get()) / motor_full_steps_per_rev->get();
                // lookupAngle = i * ENCODER_CNT_PER_REV / motor_full_steps_per_rev->get() +
                //   j * ENCODER_CNT_PER_REV / ticks / motor_full_steps_per_rev->get();
                CaliTab.set(index, (uint16_t)lookupAngle);
                index++;
                // Serial.print("O");
            }
        } else {
            //this is the general case
            for (int32_t j = 0; j < ticks; j++) {
                // 普通扇区
                lookupAngle = ((ENCODER_CNT_PER_REV)*i + (ENCODER_CNT_PER_REV)*j / ticks) %
                              (ENCODER_CNT_PER_REV * motor_full_steps_per_rev->get()) / motor_full_steps_per_rev->get();
                // lookupAngle = i * ENCODER_CNT_PER_REV / motor_full_steps_per_rev->get() +
                //   j * ENCODER_CNT_PER_REV / ticks / motor_full_steps_per_rev->get();
                CaliTab.set(index, (uint16_t)lookupAngle);
                index++;
                // Serial.print("-");
            }
        }
    }
    free(fullStepVal);
    // 保存校准数据
    if (!CaliTab.saveCaliTable()) {
        Serial.println("Cali.saveCaliTable() feiled!");
    }
    Serial.println("\r\nCaliTable() 1!\r\n");
    for (int i = 0; i < CALITABLE_LENGTH; i += 100)
        Serial.printf("%d,", CaliTab.get(i));
    CaliTab.end();
    // 重新加载文件并打印数据
    CaliTab.begin();
    CaliTab.loadCaliTable();
    Serial.println("\r\nCaliTable() 2!\r\n");
    for (int i = 0; i < CALITABLE_LENGTH; i += 100)
        Serial.printf("%d,", CaliTab.get(i));
    Serial.printf("Calibrate End!\r\n");
    CaliTab.end();
    Serial.printf("Calibrate End2!\r\n");
    int cnt = 10;
    while (cnt--) {
        LED.set(HIGH);
        delay(250);
        LED.set(LOW);
        delay(250);
    }
}