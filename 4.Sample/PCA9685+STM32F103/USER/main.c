#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "usmart.h"	 
#include "24cxx.h"	 
#include "pca9685.h"
 
/************************************************
 ALIENTEKս��STM32������ʵ��23
 IIC ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

 				 	
//Ҫд�뵽24c02���ַ�������
const u8 TEXT_Buffer[]={"WarShipSTM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	
	
 int main(void)
 {	 
	u8 key;
	u16 i=0;
	u16 j=0;
	u8 datatemp[SIZE];
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	//LCD_Init();			   	//��ʼ��LCD 	
	KEY_Init();	
	
			IIC_Init();//IIC��ʼ��
      pca_write(pca_mode1,0x0);//д��ַ
			pca_setfreq(330);//д���Ƶ�ʣ�ģ������50HZ�����ֵ��330HZ
			while(1)
			{
				/*��ֵ���㲽�裺
				����ʱ��0.5ms-2.5ms(ռ�ձ�5%-12.5%),Ƶ��330HZ������3.03ms�����ֱ���4096
				0�㣬0.5/3.03*4096=675
				90�㣬1.5/3.03*4096=2017
				180�㣬2.5/3.03*4096=3379
				*/
				for(j=600;j<2000;j++)//0·������Ȼ�����Ȼ����ת90�㣨������˲�䶯����
				{
					pca_setpwm(0,0,j);//��ת90��
					delay_ms(3);//��0�㵽180������ʱ�������������ڿ���Ч��
				}
					delay_ms(300);//0·���ת��180����ӳ�һ��ʱ�䣬1·�����ʼת
				for(i=600;i<2000;i++)//ͬ����
				{	
					pca_setpwm(1,0,i);
					delay_ms(3);	
				}
					delay_ms(300);
				for(i=600;i<3379;i++)
				{
					pca_setpwm(3,0,i);
					delay_ms(3);	
				}
					delay_ms(300);
				for(i=600;i<2000;i++)
				{	
					pca_setpwm(7,0,i);
					delay_ms(3);	
				}
					delay_ms(300);
//				pca_setpwm(0,0,2000);//��ת90��
//				delay_ms(3000);
				
				
				
	}
}
