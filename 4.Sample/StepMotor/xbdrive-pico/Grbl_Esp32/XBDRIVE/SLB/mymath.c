/********************************************************************************
* @Filename:        mymath.c
* @Author:          
* @Version:         ver1.0
* @Date:            2021-5-10
* @Description:     
* @History:         
********************************************************************************/
#include "mymath.h"

// 求模函数
int16_t myMod(int32_t xMod, int16_t mMod)
{
    int16_t temp;
    temp = xMod % mMod;
    if(temp < 0)
    {
        return (temp + mMod);
    }
    else
    {
        return temp;
    }
}