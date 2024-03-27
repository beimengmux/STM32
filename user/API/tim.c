#include "tim.h"

/*
tim的时钟的学习
时间：2023-07-30-16-54
*/

//定时器3初始化
void TIM3_Config(void)
{
	//配置PA6为复用推挽输出
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开始终
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//1.打开TIM3的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//2.配置TIM3,1ms的中断模式(定时时长 = 分频数*计数器/时钟源)
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_Period = 1000-1;//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;//分频数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	//2.1配置TIM3——CH1通道为PWM1模式
	TIM_OCInitTypeDef TIM_OCInitStruct = {0};
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//配置为PWM1模式(有效电平)
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; //将端口CH1配置为输出模式
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;//设置极性为低
	TIM_OCInitStruct.TIM_Pulse = 0; //比较寄存器的值
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	//2.2配置中断
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //配置中断源（更新中断）
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn; //中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//占先优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//次级优先级
	NVIC_Init(&NVIC_InitStruct);
	
	//3.使能TIM3
	TIM_Cmd(TIM3,ENABLE);
}

void TIM3_IRQHandler(void)
{
	static int counter = 0;
	static int minus = 1000;//因为计数器的值为1000
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除中断标志位
		counter++;
		if(counter > 999)
		{
			minus--;
			//把minus的值给比较寄存器
			TIM_SetCompare1(TIM3,minus);
			if(minus == 0)
			{
				counter = 0;
				minus = 1000;
			}
		}
		else{
		//把counter的值给比较寄存器
		TIM_SetCompare1(TIM3,counter);
		}
	}
}


void TIM6_Config(void)
{
	//1.打开TIM6的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	//2.配置TIM6，2秒的中断模式
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_Period = 20000-1;//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;//分频数
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	//配置中断
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //配置中断源
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	NVIC_InitStruct.NVIC_IRQChannel = TIM6_IRQn; //中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//占先优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//次级优先级
	NVIC_Init(&NVIC_InitStruct);
	
	//3.使能TIM6
	TIM_Cmd(TIM6,ENABLE);
}

void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
		BEEP_Toggle;
	}
}
