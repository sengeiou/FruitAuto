#ifndef __LED_H__
#define __LED_H__

#include "stm32f1xx_hal.h"

#define  LED_PIN                       GPIO_PIN_13
#define  LED_GPIO_PORT                 GPIOC
#define  LED_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define  LED_ON()                      HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET) //�˵�·��PC13����ߵ�ƽʱ�ư����͵�ƽʱ����
#define  LED_OFF()                     HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET)   //�˵�·��PC13����ߵ�ƽʱ�ư����͵�ƽʱ����
#define  LED_TOGGLE()                  HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN)

void LED_GPIO_init(void);
void LED_set(void);

#endif
