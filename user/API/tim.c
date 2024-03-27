#include "tim.h"

/*
tim��ʱ�ӵ�ѧϰ
ʱ�䣺2023-07-30-16-54
*/

//��ʱ��3��ʼ��
void TIM3_Config(void)
{
	//����PA6Ϊ�����������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//��ʼ��
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//1.��TIM3��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//2.����TIM3,1ms���ж�ģʽ(��ʱʱ�� = ��Ƶ��*������/ʱ��Դ)
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = 1000-1;//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;//��Ƶ��
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	//2.1����TIM3����CH1ͨ��ΪPWM1ģʽ
	TIM_OCInitTypeDef TIM_OCInitStruct = {0};
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//����ΪPWM1ģʽ(��Ч��ƽ)
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; //���˿�CH1����Ϊ���ģʽ
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;//���ü���Ϊ��
	TIM_OCInitStruct.TIM_Pulse = 0; //�ȽϼĴ�����ֵ
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	//2.2�����ж�
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //�����ж�Դ�������жϣ�
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn; //�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//ռ�����ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//�μ����ȼ�
	NVIC_Init(&NVIC_InitStruct);
	
	//3.ʹ��TIM3
	TIM_Cmd(TIM3,ENABLE);
}

void TIM3_IRQHandler(void)
{
	static int counter = 0;
	static int minus = 1000;//��Ϊ��������ֵΪ1000
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//����жϱ�־λ
		counter++;
		if(counter > 999)
		{
			minus--;
			//��minus��ֵ���ȽϼĴ���
			TIM_SetCompare1(TIM3,minus);
			if(minus == 0)
			{
				counter = 0;
				minus = 1000;
			}
		}
		else{
		//��counter��ֵ���ȽϼĴ���
		TIM_SetCompare1(TIM3,counter);
		}
	}
}


void TIM6_Config(void)
{
	//1.��TIM6��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	//2.����TIM6��2����ж�ģʽ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = 20000-1;//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;//��Ƶ��
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	//�����ж�
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //�����ж�Դ
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	NVIC_InitStruct.NVIC_IRQChannel = TIM6_IRQn; //�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//ռ�����ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//�μ����ȼ�
	NVIC_Init(&NVIC_InitStruct);
	
	//3.ʹ��TIM6
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
