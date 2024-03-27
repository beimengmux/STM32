#include "KEY.h"
#include "delay.h"

void KEY_configlib(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};                           //�ṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);              //����ʱ��
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;                //��������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;                            //�ܽ�����
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);              //����ʱ��
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;             
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;  //�ܽ�����
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}


u8 Key_GetValue(void)
{
	if(KEY1 != 0){//��ⰴ���Ƿ���
		//��ʱ����
		Delay_nopms(20);
		if(KEY1 != 0){
			while(KEY1 != 0);//���ּ��
			return 1;
		}
	}
	if(KEY2 == 0){//��ⰴ���Ƿ���	
		Delay_nopms(20);		
		if(KEY2 == 0){
			//��ʱ����	
			while(KEY2 == 0);//���ּ��
			return 2;
		}
	}
	if(KEY3 == 0){//��ⰴ���Ƿ���	
		Delay_nopms(20);		
		if(KEY3 == 0){
			//��ʱ����	
			while(KEY3 == 0);//���ּ��
			return 3;
		}	
	}
	if(KEY4 == 0){//��ⰴ���Ƿ���	
		Delay_nopms(20);		
		if(KEY4 == 0){
			//��ʱ����	
			while(KEY4 == 0);//���ּ��
			return 4;
		}			
	}
	return 0;
}

////����
//u8 Key_GetValue(void)
//{
//	static int count = 0;//��¼��������
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
