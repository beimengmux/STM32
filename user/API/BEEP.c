#include "BEEP.h"

void BEEP_configlib(void)
{
//  PE2����ͨ���������50MHz 0011
//  �����㣬����λ
//  ������PC0
//	RCC->APB2ENR |= (1<<4);
//  GPIOC->CRL &= ~(0xf);
//  GPIOC->CRL |= (0x3);
	GPIO_InitTypeDef GPIO_InitStruct = {0};              //�ṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //����ʱ��
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;        //���ģʽͨ������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;       //����ٶ�Ϊ50MHZ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;               //�ܽ�����
	GPIO_Init(GPIOC,&GPIO_InitStruct);                   //��ʼ��
}
