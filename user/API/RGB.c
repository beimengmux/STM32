#include "RGB.h"

void RGB_configlib(void)
{
//	PE2配置通用推挽输出50MHz 0011
//	先清零，再置位
//	GRB灯 PA678
//	RCC->APB2ENR |= (1<<2);
//	GPIOA->CRL &= ~(0xf<<24);
//  GPIOA->CRL |= (0x3<<24);
//	GPIOA->CRL &= ~(0xf<<28);
//  GPIOA->CRL |= (0x3<<28);
//	GPIOA->CRH &= ~(0xf);
//  GPIOA->CRH |= (0x3);
	GPIO_InitTypeDef GPIO_InitStruct = {0};              //结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //配置时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;        //输出模式通用推挽
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;       //输出速度为50MHZ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8;   //管脚设置
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	RGBR_OFF;
	RGBG_OFF;
	RGBB_OFF;
}


//GRB各种灯闪烁
void RGB_flow(void)
{
	static int j = 0;
	switch(j%8){
	case 0:RGBB_ON;RGBR_ON;RGBG_ON; //RGB
		break;
	case 1:RGBB_OFF;RGBR_OFF;RGBG_OFF;RGBB_ON; //B
		break;
	case 2:RGBB_OFF;RGBR_ON;//R
		break;
	case 3:RGBR_OFF;RGBG_ON;//G
		break;
	case 4:RGBG_ON;RGBR_ON;//GR
		break;
	case 5:RGBR_OFF;RGBB_ON;//GB
		break;
	case 6:RGBG_OFF;RGBR_ON;//BR
		break;
	case 7:RGBR_OFF;RGBB_OFF;RGBG_OFF;
		break;
	}
	j++;
}

void RGB_SetMode(u8 mode)
{		
	switch(mode){
		case 0:RGBR_OFF;RGBG_OFF;RGBB_OFF;break;
		case 1:RGBR_ON;RGBG_OFF;RGBB_OFF;break;
		case 2:RGBR_OFF;RGBG_ON;RGBB_OFF;break;
		case 3:RGBR_OFF;RGBG_OFF;RGBB_ON;break;
		case 4:RGBR_ON;RGBG_ON;RGBB_ON;break;
	}
}
