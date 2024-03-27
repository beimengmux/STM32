#include "USART.h"



struct tagUSARTMessage revmessage={.rcv_flag = 0,.rcv_count = 0};

/*
����ԭ�ͣ�void USART_Config(void)
�������ܣ���ʼ������1
������������Ҫ���õĲ�����
��������ֵ����
���ߣ�GLD
ʱ�䣺2023.7.21-16��00��
*/

//void USART1_Config(u32 brr)
//{
//	//1.����IO�ڣ�PA9(�����������)  PA10���������룩
//	//1.1 ��A�˿ڵ�ʱ��
//	RCC->APB2ENR |= (1<<2);
//	//1.2 ����PA9 
//	GPIOA->CRH &= ~(0xf<<4); //����
//	GPIOA->CRH |= (0xB<<4);  //1011
//	//PA10
//	GPIOA->CRH &= ~(0xf<<8); //����
//	GPIOA->CRH |= (0x4<<8);  //0100
//	//2.����USART1��1.232Э�飨1+8+0+1��   2.������   3.���ܻ��߷��͵�ʹ�ܣ�
//	//2.1��ʱ��
//	RCC->APB2ENR |= (1<<14);
//	//2.2���ݳ���
//	USART1->CR1 &= ~(1<<12); //����
//	USART1->CR1 &= ~(1<<10); //У��
//	USART1->CR2 &= ~(0x3<<12); //ֹͣλ
//	
//	//2.3 ���ò�����
//	float USARTDIV = 0;
//	u32 div_m; //��������
//	u32 div_f;
//	USARTDIV = 72000000.0/ (brr*16.0);
//	div_m = (u32)USARTDIV;
//	div_f = (u32)((USARTDIV-div_m)*16.0+0.5);
//	USART1->BRR = (div_m<<4) |div_f;
//	//2.4 ʹ��
//	USART1->CR1 |= (1<<2)|(1<<3);
//	//3.ʹ�ܴ��ڹ���
//	USART1->CR1 |= (1<<13);
//}

void USART1_Config(u32 brr)
{
	//1.����io�� -- PA9�������������ģʽ50MHZ����PA10���������룩
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//����usart
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitTypeDef USART_InitStruct = {0};
	
	USART_InitStruct.USART_BaudRate = brr;//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;//��У��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//1��ֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//���ݳ���Ϊ8
	USART_Init(USART1,&USART_InitStruct);
	
	//�ж�����
	USART1_NVICConfig();
	
	//3.ʹ�ܴ��ڹ���
	USART_Cmd(USART1,ENABLE);
}
//����һ���ַ�
void USART1_Send(u8 data)
{
	while((USART1->SR & (1<<6)) == 0);//δ��������
	USART1->DR = data;
}

void USART1_SendBuff(u8 *pdata,uint16_t length)
{
	uint16_t i;
	for(i = 0; i<length;i++)
	{
		USART1_Send(*pdata++);
	}
}

//����һ���ַ���
void USART1_SendStr(u8 *pdata)
{
	while(*pdata != '\0')
	{
		USART1_Send(*pdata);
		pdata++;
	}
}

//��printf���ն��Ͻ��д�ӡ
int fputc(int ch,FILE *stream)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	USART_SendData(USART1,ch);
	return ch;
}


//���ܴ����첽ȫ˫��ͨ��
//void USART1_Revc(void)
//{
//	char data;
//	//1.������λ�����͹���������
//	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
//	//2.�ж�����
//	data = USART1->DR;
//	if(data == 0)
//	{
//		BEEP_OFF;
//	}
//	else if(data == 1)
//	{
//		BEEP_ON;
//	}
//}

//�Զ������Э�� ���ݸ�ʽ���豸��+�豸״̬
//  X -- �豸�ţ�1~255�� �����豸-- 0  LED2 -- 1 LED3 -- 2 LED4 -- 3 ������ -- 4  RGB -- 5
//  X -- ״̬                                0--�ر�  1--��              0 -- �� 1 -- ��  2 �� 3 �� 4 -- ��
//  ���� 00 00 -- ȫ��      00 01 -- ȫ��
//void USART1_Revctest(void)
//{
//	u8 data[10];
//	int i = 0;
//	while(i < 10){
//		while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
//		data[i] = USART1->DR;
//		USART1->DR = data[i]; //����---����
//		if(data[i] != 0XAA && i == 0){
//			continue;  //��һ��ѭ��
//		}
//		if(data[i] != 0XCC){
//			return; //�������֡��ʽ����cc��β������
//		}
//		if(data[i] == 0XCC){
//			break;
//		}
//		i++;
//	}
//}

void USART1_NVICConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	//2.1 �����ж�Դ
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//�����ж�
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);//�����ж�
  //2.2 �����ж�ͨ����NVIC��
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;//�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  //ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//ռ��
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//�μ�
	NVIC_Init(&NVIC_InitStruct);
}

//2.3 ��д�жϷ�����
//u8 rcv_buff[16];
//u8 rcv_flag = 0;//һ֡��Ϣ������ɱ�־ 0--û�н������  1--�������
//u8 rcv_count = 0;
void USART1_IRQHandler(void)
{
	u8 temp = 0;
	//1.�ж��ж�Դ
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET){//����
		//2.����жϱ�־λ
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		//3.��������
		revmessage.rcv_buff[revmessage.rcv_count++] = USART1->DR;
		//rcv_buff[rcv_count++] = USART1->DR;
	}
	if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)//����
	{
		USART_ClearITPendingBit(USART1,USART_IT_IDLE);
		temp = USART1->DR;//����жϱ�־λ
		revmessage.rcv_flag = 1;
//		rcv_flag = 1;
	}	
}
//��������
u8 USART1_DataAnalysis(void)
{
	if(revmessage.rcv_flag == 0)//û���յ�����
		return 1;
	//�յ����ݴ�������
	//1.�ж�֡ͷ
	if(revmessage.rcv_buff[0] != 0xAA){
		revmessage.rcv_flag = 0;
		revmessage.rcv_count = 0;//Ϊ��һ�ν���������׼��
		return 2;
	}
  //2.�ж�֡β
	if(revmessage.rcv_buff[3] != 0xCC){
		revmessage.rcv_flag = 0;
		revmessage.rcv_count = 0;//Ϊ��һ�ν���������׼��
		return 3;
	}
	//3.��������
	u8 no = revmessage.rcv_buff[1];
	u8 opt = revmessage.rcv_buff[2];
	switch(no)
	{
		case 0:
			if(opt == 1){
				LED2_ON;LED3_ON;LED4_ON;
				BEEP_ON;
				RGB_SetMode(RGB_MODE_ON);
			}else if(opt == 0){
				LED2_OFF;LED3_OFF;LED4_OFF;
				BEEP_OFF;
				RGB_SetMode(RGB_MODE_OFF);
			}
			break;
		case 1:if(opt == 0) LED1_OFF;
					 else if(opt == 1) LED1_ON;
			break;
		case 2:if(opt == 0) LED2_OFF;
					 else if(opt == 1) LED2_ON;
			break;
		case 3:if(opt == 0) LED3_OFF;
					 else if(opt == 1) LED3_ON;
			break;
		case 4:if(opt == 0) BEEP_OFF;
					 else if(opt == 1) BEEP_ON;
			break;
		case 5:
			if(opt == 0)	RGB_SetMode(RGB_MODE_OFF);
			else if(opt == 1)	RGB_SetMode(RGB_MODE_R);
			else if(opt == 2)	RGB_SetMode(RGB_MODE_G);
			else if(opt == 3)	RGB_SetMode(RGB_MODE_B);
			else if(opt == 4)	RGB_SetMode(RGB_MODE_ON);
			break;
	}
	revmessage.rcv_flag = 0;
	revmessage.rcv_count = 0;//Ϊ��һ�ν���������׼��
	return 0x0;
}

void USART1_DMATx_Config(void)
{
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);//ʹ��USART1_Tx��DMA1���͹���
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMA_InitStruct = {0};
	
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;//������ΪĿ��
	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)&USART1->DR;//�����ַ
	DMA_InitStruct.DMA_MemoryBaseAddr = 0;//ָ���ڴ���׵�ַ
	DMA_InitStruct.DMA_BufferSize = 0;    //Ҫ��������ݳ��� = 0
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�ֽ�
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�ֽ�
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;//����ģʽ -- DMA����1��
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ������
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;//���ȼ�
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;//��ʹ���ڴ浽�ڴ�
	
	DMA_Init(DMA1_Channel4,&DMA_InitStruct);
	//ʹ��DMA
	DMA_Cmd(DMA1_Channel4,DISABLE);
}

/*
ʹ��USART1��DMA���ܣ�����len������
*/
void USART1_DMASendStr(u8 *pdata,u32 len)
{
	//�ر�DMA1 ͨ��4����
	DMA_Cmd(DMA1_Channel4,DISABLE);
	//�޸Ĵ洢����ַ
	DMA1_Channel4->CMAR = (u32)pdata;
	//�޸Ĵ������ݵĳ���
	DMA1_Channel4->CNDTR = len;
	//��DMA1 ͨ��4����
	DMA_Cmd(DMA1_Channel4,ENABLE);
}


