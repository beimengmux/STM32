#include "kqm6600.h"
#include "FreeRTOS.h"
#include "semphr.h"  //信号量
#include "main.h"

struct tagSensor KQM = {0};

void USART2_Config(u32 brr)
{
	//配置PA3（浮空输入）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//配置USART2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_InitTypeDef USART_InitStruct = {0};
	USART_InitStruct.USART_BaudRate = brr;                   //波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;        //不校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;     //1个停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据长度为8
	USART_Init(USART2,&USART_InitStruct);
	
	//中断配置
	USART2_NVICConfig();
	
	//3.使能串口功能
	USART_Cmd(USART2,ENABLE);
	//配置中断
}

//编写中断
void USART2_NVICConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	//2.1 配置中断源
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//接收中断
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);//空闲中断
  //2.2 配置中断通道（NVIC）
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;//中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  //使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; //占先
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;        //次级
	NVIC_Init(&NVIC_InitStruct);
}

struct KQMMessage KQM6600 = {0,0,0};
//中断服务函数
void USART2_IRQHandler(void)
{
	u8 temp = 0;
	//1.判断中断源
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET){//接收
		//2.清除中断标志位
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		//3.保存数据
		KQM6600.rcv_buff[KQM6600.rcv_count++] = USART2->DR;
		if(KQM6600.rcv_count>=16)
			KQM6600.rcv_count=0;
		//rcv_buff[rcv_count++] = USART1->DR;
	}
	if(USART_GetITStatus(USART2,USART_IT_IDLE) == SET)//空闲
	{
		USART_ClearITPendingBit(USART2,USART_IT_IDLE);
		temp = USART2->DR;//清除中断标志位
		KQM6600.rcv_flag = 1;
		//参数1   二值信号量的句柄
		//参数2   NULL
		//当有多个任务等待信号量，参数2需要设置，只有1个任务等待，直接给空
		xSemaphoreGiveFromISR(BinarySem_Handle,NULL);  //在中断中释放信号量		
	}	
}

//解析数据
u8 KQM6600_DataAnalysis(void)
{
	if(KQM6600.rcv_flag == 0)//没有收到数据
		return 1;
	//收到数据处理数据
	//1.判断帧头
	if(KQM6600.rcv_buff[0] != 0x5F){
		memset(KQM6600.rcv_buff,0,sizeof(KQM6600.rcv_buff));
		KQM6600.rcv_flag = 0;
		KQM6600.rcv_count = 0;//为下一次接收数据做准备
		return 2;
	}
  //2.校验
	u32 t = 0;
	for(int i = 0; i < 7; i++)
	{
		t += KQM6600.rcv_buff[i];
	}
	if((t &0xff) != KQM6600.rcv_buff[7])
	{
		KQM6600.rcv_flag = 0;
		KQM6600.rcv_count = 0;//为下一次接收数据做准备
	}
	
	//3.解析数据
	KQM.voc = (KQM6600.rcv_buff[1]*256+KQM6600.rcv_buff[2])*0.1;
	KQM.hcho =(KQM6600.rcv_buff[3]*256+KQM6600.rcv_buff[4])*0.01;
	KQM.co2 = KQM6600.rcv_buff[5]*256+KQM6600.rcv_buff[6];
	KQM6600.rcv_flag = 0;
	KQM6600.rcv_count = 0;//为下一次接收数据做准备
	return 0x0;
}
