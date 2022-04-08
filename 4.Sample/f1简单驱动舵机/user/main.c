#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "stm32_pca9685.h"



/*
  我缺少积分，请各位下载此代码给点积分。
	我的博客：https://blog.csdn.net/seatest

	STM32F103C8T6  专用。使用IIC1通道，对应针脚：PA6,PA7
	其他STM32板子，请修改默认针脚

	代码自改，简单方便，亲测可用，不仅可以控制舵机，还可以直接控制Led亮度
	stm32_pca9685只有一个c文件和h文件，不含其他库，复制过去就可以用，
	代码极简只用1个函数就可以控制舵机，另1函数控制led
	
	
	
	控制Led时，led的正极接控制板的信号插口（黄），负极接gnd（黑）。

*/


int main(void)
{	
	delay_init();//延时函数初始化
	PCA_MG9XX_Init(60,90);//初始化舵机驱动
	
	delay_ms(1000);
	delay_ms(1000);
	
	
	for(int i=0;i<25;i++) 
	{
		
		//PCA_MG9XX(1,0,180,2,5+5*i); //通道1，慢慢的转
		//PCA_MG9XX(2,0,180,2,5+5*i); //通道2，慢慢的转
		
		PCA_MG9XX(12,0,180,1,10); //通道1 从0度转到180度
		PCA_MG9XX(12,0,180,1,10); //通道2 从0度转到180度
		PCA_MG9XX(13,180,0,1,10); //通道1 从180度转到0度
		PCA_MG9XX(13,180,0,1,10); //通道2 从180度转到0度
	}
	
	

	/*
while(1) //直接控制led,
{
	for(int i=0;i<4096;i++)
	{
	  pca_setpwm(7,0,i);delay_ms(1);//用通道7直接控制Led亮度
	}
}*/



}
 

