#include "EXTI.h"
#include "BEEP.h"
#include "led.h"

//标准库实现
void EXTI0_Config(void)
{
	//1.PA0配置为浮空输入模式
	//2.EXTI0映射到PA0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    //打开AFIO时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);  //外部中断配置寄存器 EXTIO映射到AP0
	
	//3.配置EXTI0 -- 上升沿触发，使能
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE; //使能EXTI0
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt; 
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising; //配置为上升沿触发
	EXTI_Init(&EXTI_InitStruct);
	
	//4.配置NVIC -- 中断通道的选择、中断优先级、使能
	NVIC_InitTypeDef NVIC_InitStruct = {0};  //结构体
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn; //EXTI0通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; //抢占
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0; //次级
	NVIC_Init(&NVIC_InitStruct); //初始化NVIC寄存器
}

//寄存器实现
void EXTI4_Config(void)
{
	//1.PC4配置为上拉输入模式
	//2.EXTI4映射到PC4
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//打开AFIO时钟
	//配置寄存器先清零后置位
	AFIO->EXTICR[1] &= ~(0xf<<0);
	AFIO->EXTICR[1] |= (0x2<<0); //外部中断配置寄存器 EXTI1映射到PC4
	
	//3.配置EXTI4 -- 上升沿触发，使能
	EXTI->IMR |= (1<<4);   //使能EXTI4
	EXTI->FTSR |= (1<<4);		//配置为下降沿触发
	
	//4.配置NVIC -- 中断通道的选择、中断优先级、使能
	NVIC_InitTypeDef NVIC_InitStruct = {0};  //结构体
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn; //EXTI0通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; //抢占
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0; //次级
	NVIC_Init(&NVIC_InitStruct); //初始化NVIC寄存器
	
}


void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET ){//发生中断
		EXTI_ClearITPendingBit(EXTI_Line0); //再次置1可以清零
		//BEEP_Toggle;
	}
}

void EXTI4_IRQHandler(void)
{
	if((EXTI->PR &(1<<4)) != 0){
		EXTI->PR |= (1<<4);//再次置1可以清零
		LED1_Toggle;
	}
}
