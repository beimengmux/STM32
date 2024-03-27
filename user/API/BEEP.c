#include "BEEP.h"

void BEEP_configlib(void)
{
//  PE2配置通用推挽输出50MHz 0011
//  先清零，再置位
//  蜂鸣器PC0
//	RCC->APB2ENR |= (1<<4);
//  GPIOC->CRL &= ~(0xf);
//  GPIOC->CRL |= (0x3);
	GPIO_InitTypeDef GPIO_InitStruct = {0};              //结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //配置时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;        //输出模式通用推挽
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;       //输出速度为50MHZ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;               //管脚设置
	GPIO_Init(GPIOC,&GPIO_InitStruct);                   //初始化
}
