#include "kqm6600.h"
#include "FreeRTOS.h"
#include "semphr.h"  //�ź���
#include "main.h"

struct tagSensor KQM = {0};

void USART2_Config(u32 brr)
{
	//����PA3���������룩
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//����USART2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_InitTypeDef USART_InitStruct = {0};
	USART_InitStruct.USART_BaudRate = brr;                   //������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;        //��У��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;     //1��ֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//���ݳ���Ϊ8
	USART_Init(USART2,&USART_InitStruct);
	
	//�ж�����
	USART2_NVICConfig();
	
	//3.ʹ�ܴ��ڹ���
	USART_Cmd(USART2,ENABLE);
	//�����ж�
}

//��д�ж�
void USART2_NVICConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	//2.1 �����ж�Դ
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//�����ж�
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);//�����ж�
  //2.2 �����ж�ͨ����NVIC��
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;//�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  //ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; //ռ��
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;        //�μ�
	NVIC_Init(&NVIC_InitStruct);
}

struct KQMMessage KQM6600 = {0,0,0};
//�жϷ�����
void USART2_IRQHandler(void)
{
	u8 temp = 0;
	//1.�ж��ж�Դ
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET){//����
		//2.����жϱ�־λ
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		//3.��������
		KQM6600.rcv_buff[KQM6600.rcv_count++] = USART2->DR;
		if(KQM6600.rcv_count>=16)
			KQM6600.rcv_count=0;
		//rcv_buff[rcv_count++] = USART1->DR;
	}
	if(USART_GetITStatus(USART2,USART_IT_IDLE) == SET)//����
	{
		USART_ClearITPendingBit(USART2,USART_IT_IDLE);
		temp = USART2->DR;//����жϱ�־λ
		KQM6600.rcv_flag = 1;
		//����1   ��ֵ�ź����ľ��
		//����2   NULL
		//���ж������ȴ��ź���������2��Ҫ���ã�ֻ��1������ȴ���ֱ�Ӹ���
		xSemaphoreGiveFromISR(BinarySem_Handle,NULL);  //���ж����ͷ��ź���		
	}	
}

//��������
u8 KQM6600_DataAnalysis(void)
{
	if(KQM6600.rcv_flag == 0)//û���յ�����
		return 1;
	//�յ����ݴ�������
	//1.�ж�֡ͷ
	if(KQM6600.rcv_buff[0] != 0x5F){
		memset(KQM6600.rcv_buff,0,sizeof(KQM6600.rcv_buff));
		KQM6600.rcv_flag = 0;
		KQM6600.rcv_count = 0;//Ϊ��һ�ν���������׼��
		return 2;
	}
  //2.У��
	u32 t = 0;
	for(int i = 0; i < 7; i++)
	{
		t += KQM6600.rcv_buff[i];
	}
	if((t &0xff) != KQM6600.rcv_buff[7])
	{
		KQM6600.rcv_flag = 0;
		KQM6600.rcv_count = 0;//Ϊ��һ�ν���������׼��
	}
	
	//3.��������
	KQM.voc = (KQM6600.rcv_buff[1]*256+KQM6600.rcv_buff[2])*0.1;
	KQM.hcho =(KQM6600.rcv_buff[3]*256+KQM6600.rcv_buff[4])*0.01;
	KQM.co2 = KQM6600.rcv_buff[5]*256+KQM6600.rcv_buff[6];
	KQM6600.rcv_flag = 0;
	KQM6600.rcv_count = 0;//Ϊ��һ�ν���������׼��
	return 0x0;
}
