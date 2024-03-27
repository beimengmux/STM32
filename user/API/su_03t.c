#include "su_03t.h"
#include "RGB.h"
#include "DHT11.h"
#include "stdio.h"

struct SU03Message su_03 = {0,0,0};

void UART4_Config(u32 brr)
{
	//����PC10���������������,PC11���������룩
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);	
	
	//����UART4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	
	USART_InitTypeDef USART_InitStruct = {0};
	USART_InitStruct.USART_BaudRate = brr;//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;//��У��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//1��ֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//���ݳ���Ϊ8
	USART_Init(UART4,&USART_InitStruct);
	
	//�ж�����
	UART4_NVICConfig();
	
	//3.ʹ�ܴ��ڹ���
	USART_Cmd(UART4,ENABLE);
	//�����ж�
}

//��д�ж�
void UART4_NVICConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	//2.1 �����ж�Դ
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);//�����ж�
	USART_ITConfig(UART4,USART_IT_IDLE,ENABLE);//�����ж�
  //2.2 �����ж�ͨ����NVIC��
	NVIC_InitStruct.NVIC_IRQChannel = UART4_IRQn;//�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  //ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//ռ��
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//�μ�
	NVIC_Init(&NVIC_InitStruct);
}

//�жϷ�����
void UART4_IRQHandler(void)
{
	u8 temp = 0;
	//1.�ж��ж�Դ
	if(USART_GetITStatus(UART4,USART_IT_RXNE) == SET){//����
		//2.����жϱ�־λ
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
		//3.��������
		su_03.rcv_buff[su_03.rcv_count++] = UART4->DR;
		//rcv_buff[rcv_count++] = USART1->DR;
	}
	if(USART_GetITStatus(UART4,USART_IT_IDLE) == SET)//����
	{
		USART_ClearITPendingBit(UART4,USART_IT_IDLE);
		temp = UART4->DR;//����жϱ�־λ
		su_03.rcv_flag = 1;
	}	
}

//��������
u8 SU03_DataAnalysis(void)
{
	if(su_03.rcv_flag == 0)//û���յ�����
		return 1;
	//�յ����ݴ�������
	//1.�ж�֡ͷ
	if(su_03.rcv_buff[0] != 0xAA || su_03.rcv_buff[1] != 0x55){
		su_03.rcv_flag = 0;
		su_03.rcv_count = 0;//Ϊ��һ�ν���������׼��
		return 2;
	}
	//2.�ж�֡β
	if(su_03.rcv_buff[3] != 0x55 || su_03.rcv_buff[4] != 0xAA){
		su_03.rcv_flag = 0;
		su_03.rcv_count = 0;//Ϊ��һ�ν���������׼��
		return 3;
	}
	//3.��������
	u32 temp = su_03.rcv_buff[2];
	switch(temp){
		case 1:break;
		case 2:RGBR_ON;RGBG_OFF;RGBB_OFF;break;
		case 3:RGBR_OFF;RGBG_ON;RGBB_OFF;break;
		case 4:RGBR_OFF;RGBG_OFF;RGBB_ON;break;
		case 5:RGBR_ON;RGBG_ON;RGBB_ON;break;
		case 6:RGBR_OFF;RGBG_OFF;RGBB_OFF;break;
	}
						
	su_03.rcv_flag = 0;
	su_03.rcv_count = 0;//Ϊ��һ�ν���������׼��
	return 0x0;
}


void SU03T_TxBuff(u8 * data,u16 len)
{
	for(int i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC) == RESET);
		USART_SendData(UART4,data[i]);
	}
}

//��������
void SU03_Send(void)
{
	u8 data_t[13] = {0xAA,0x55,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0xAA};
	u8 temp[8] = {0};
	double *t = (double *)&temp;
	*t = (double)dht11.t;
	for(int i=0;i<8;i++){
		data_t[i+3] = temp[i];
	}
	SU03T_TxBuff(data_t,13);
}
