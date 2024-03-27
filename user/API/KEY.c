#include "KEY.h"
#include "delay.h"

void KEY_configlib(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};                           //结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);              //配置时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;                //浮空输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;                            //管脚设置
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);              //配置时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;             
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;  //管脚设置
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}


u8 Key_GetValue(void)
{
	if(KEY1 != 0){//检测按键是否按下
		//延时消抖
		Delay_nopms(20);
		if(KEY1 != 0){
			while(KEY1 != 0);//松手检测
			return 1;
		}
	}
	if(KEY2 == 0){//检测按键是否按下	
		Delay_nopms(20);		
		if(KEY2 == 0){
			//延时消抖	
			while(KEY2 == 0);//松手检测
			return 2;
		}
	}
	if(KEY3 == 0){//检测按键是否按下	
		Delay_nopms(20);		
		if(KEY3 == 0){
			//延时消抖	
			while(KEY3 == 0);//松手检测
			return 3;
		}	
	}
	if(KEY4 == 0){//检测按键是否按下	
		Delay_nopms(20);		
		if(KEY4 == 0){
			//延时消抖	
			while(KEY4 == 0);//松手检测
			return 4;
		}			
	}
	return 0;
}

////消抖
//u8 Key_GetValue(void)
//{
//	static int count = 0;//记录采样次数
//	if(KEY1 != 0) count++;
//	else if(count > 10)
//	{
//		count = 0;
//		return 1;
//	}else
//	{
//		count = 0;
//	}
//	return 0;
//}
