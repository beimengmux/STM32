#include "led.h"

uint8_t LED_Status = 0;

void LED_configlib(void)
{
//	PE2配置通用推挽输出50MHz 0011
//	先清零，再置位
//	RCC->APB2ENR |= (1<<6);
//	GPIOE->CRL &= ~(0xf<<8);
//	GPIOE->CRL |=  (0x3<<8);
//	GPIOE->CRL &= ~(0xf<<12);
//	GPIOE->CRL |=  (0x3<<12);
//	GPIOE->CRL &= ~(0xf<<16);
//	GPIOE->CRL |=  (0x3<<16);
//	GPIOE->CRL &= ~(0xf<<20);
//	GPIOE->CRL |=  (0x3<<20);
	GPIO_InitTypeDef GPIO_InitStruct = {0};              //结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE); //配置时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;        //输出模式通用推挽
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;       //输出速度为50MHZ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5;   //管脚设置
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;

}


//流水灯
void LED_flow(void)
{
	static int i = 0;
	switch(i%4){
	case 0:
		LED4_OFF;LED1_ON;
		break;
	case 1:
		LED1_OFF;LED2_ON;
		break;
	case 2:
		LED2_OFF;LED3_ON;
		break;
	case 3:
		LED3_OFF;LED4_ON;
		break;
	}
	i++;

}
