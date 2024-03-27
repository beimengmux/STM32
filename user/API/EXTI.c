#include "EXTI.h"
#include "BEEP.h"
#include "led.h"

//��׼��ʵ��
void EXTI0_Config(void)
{
	//1.PA0����Ϊ��������ģʽ
	//2.EXTI0ӳ�䵽PA0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    //��AFIOʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);  //�ⲿ�ж����üĴ��� EXTIOӳ�䵽AP0
	
	//3.����EXTI0 -- �����ش�����ʹ��
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE; //ʹ��EXTI0
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt; 
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising; //����Ϊ�����ش���
	EXTI_Init(&EXTI_InitStruct);
	
	//4.����NVIC -- �ж�ͨ����ѡ���ж����ȼ���ʹ��
	NVIC_InitTypeDef NVIC_InitStruct = {0};  //�ṹ��
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn; //EXTI0ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; //��ռ
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0; //�μ�
	NVIC_Init(&NVIC_InitStruct); //��ʼ��NVIC�Ĵ���
}

//�Ĵ���ʵ��
void EXTI4_Config(void)
{
	//1.PC4����Ϊ��������ģʽ
	//2.EXTI4ӳ�䵽PC4
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//��AFIOʱ��
	//���üĴ������������λ
	AFIO->EXTICR[1] &= ~(0xf<<0);
	AFIO->EXTICR[1] |= (0x2<<0); //�ⲿ�ж����üĴ��� EXTI1ӳ�䵽PC4
	
	//3.����EXTI4 -- �����ش�����ʹ��
	EXTI->IMR |= (1<<4);   //ʹ��EXTI4
	EXTI->FTSR |= (1<<4);		//����Ϊ�½��ش���
	
	//4.����NVIC -- �ж�ͨ����ѡ���ж����ȼ���ʹ��
	NVIC_InitTypeDef NVIC_InitStruct = {0};  //�ṹ��
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn; //EXTI0ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; //��ռ
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0; //�μ�
	NVIC_Init(&NVIC_InitStruct); //��ʼ��NVIC�Ĵ���
	
}


void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET ){//�����ж�
		EXTI_ClearITPendingBit(EXTI_Line0); //�ٴ���1��������
		//BEEP_Toggle;
	}
}

void EXTI4_IRQHandler(void)
{
	if((EXTI->PR &(1<<4)) != 0){
		EXTI->PR |= (1<<4);//�ٴ���1��������
		LED1_Toggle;
	}
}
