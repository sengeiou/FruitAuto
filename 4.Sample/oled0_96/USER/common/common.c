#include  "common.h"

// ���Ծ�ȷ�ӳ�
void  Delay_ms(uint32_t myms)
{
    uint32_t delaytime;
    delaytime = HAL_GetTick();
    while( (HAL_GetTick()-delaytime) < myms);
}

// ���ӳ��޷���ȷ��ʱ
void Delay(volatile uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

