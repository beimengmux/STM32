#include "USART.h"



struct tagUSARTMessage revmessage={.rcv_flag = 0,.rcv_count = 0};

/*
函数原型：void USART_Config(void)
函数功能：初始化串口1
函数参数：需要配置的波特率
函数返回值：无
作者：GLD
时间：2023.7.21-16点00分
*/

//void USART1_Config(u32 brr)
//{
//	//1.配置IO口，PA9(复用推挽输出)  PA10（浮空输入）
//	//1.1 打开A端口的时钟
//	RCC->APB2ENR |= (1<<2);
//	//1.2 配置PA9 
//	GPIOA->CRH &= ~(0xf<<4); //清零
//	GPIOA->CRH |= (0xB<<4);  //1011
//	//PA10
//	GPIOA->CRH &= ~(0xf<<8); //清零
//	GPIOA->CRH |= (0x4<<8);  //0100
//	//2.配置USART1（1.232协议（1+8+0+1）   2.波特率   3.接受或者发送的使能）
//	//2.1打开时钟
//	RCC->APB2ENR |= (1<<14);
//	//2.2数据长度
//	USART1->CR1 &= ~(1<<12); //数据
//	USART1->CR1 &= ~(1<<10); //校验
//	USART1->CR2 &= ~(0x3<<12); //停止位
//	
//	//2.3 配置波特率
//	float USARTDIV = 0;
//	u32 div_m; //整数部分
//	u32 div_f;
//	USARTDIV = 72000000.0/ (brr*16.0);
//	div_m = (u32)USARTDIV;
//	div_f = (u32)((USARTDIV-div_m)*16.0+0.5);
//	USART1->BRR = (div_m<<4) |div_f;
//	//2.4 使能
//	USART1->CR1 |= (1<<2)|(1<<3);
//	//3.使能串口功能
//	USART1->CR1 |= (1<<13);
//}

void USART1_Config(u32 brr)
{
	//1.配置io口 -- PA9（复用推挽输出模式50MHZ）和PA10（浮空输入）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//配置usart
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitTypeDef USART_InitStruct = {0};
	
	USART_InitStruct.USART_BaudRate = brr;//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;//不校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//1个停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据长度为8
	USART_Init(USART1,&USART_InitStruct);
	
	//中断配置
	USART1_NVICConfig();
	
	//3.使能串口功能
	USART_Cmd(USART1,ENABLE);
}
//发送一个字符
void USART1_Send(u8 data)
{
	while((USART1->SR & (1<<6)) == 0);//未发送数据
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

//发送一个字符串
void USART1_SendStr(u8 *pdata)
{
	while(*pdata != '\0')
	{
		USART1_Send(*pdata);
		pdata++;
	}
}

//用printf在终端上进行打印
int fputc(int ch,FILE *stream)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	USART_SendData(USART1,ch);
	return ch;
}


//接受串行异步全双工通信
//void USART1_Revc(void)
//{
//	char data;
//	//1.接受上位机发送过来的数据
//	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
//	//2.判断数据
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

//自定义接受协议 数据格式：设备号+设备状态
//  X -- 设备号（1~255） 所有设备-- 0  LED2 -- 1 LED3 -- 2 LED4 -- 3 蜂鸣器 -- 4  RGB -- 5
//  X -- 状态                                0--关闭  1--打开              0 -- 灭 1 -- 红  2 绿 3 蓝 4 -- 白
//  例如 00 00 -- 全灭      00 01 -- 全开
//void USART1_Revctest(void)
//{
//	u8 data[10];
//	int i = 0;
//	while(i < 10){
//		while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);
//		data[i] = USART1->DR;
//		USART1->DR = data[i]; //调试---发送
//		if(data[i] != 0XAA && i == 0){
//			continue;  //下一轮循环
//		}
//		if(data[i] != 0XCC){
//			return; //最后数据帧格式不是cc结尾，结束
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
	//2.1 配置中断源
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//接收中断
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);//空闲中断
  //2.2 配置中断通道（NVIC）
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;//中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  //使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//占先
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//次级
	NVIC_Init(&NVIC_InitStruct);
}

//2.3 编写中断服务函数
//u8 rcv_buff[16];
//u8 rcv_flag = 0;//一帧信息接收完成标志 0--没有接收完成  1--接收完成
//u8 rcv_count = 0;
void USART1_IRQHandler(void)
{
	u8 temp = 0;
	//1.判断中断源
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET){//接收
		//2.清除中断标志位
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		//3.保存数据
		revmessage.rcv_buff[revmessage.rcv_count++] = USART1->DR;
		//rcv_buff[rcv_count++] = USART1->DR;
	}
	if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)//空闲
	{
		USART_ClearITPendingBit(USART1,USART_IT_IDLE);
		temp = USART1->DR;//清除中断标志位
		revmessage.rcv_flag = 1;
//		rcv_flag = 1;
	}	
}
//解析数据
u8 USART1_DataAnalysis(void)
{
	if(revmessage.rcv_flag == 0)//没有收到数据
		return 1;
	//收到数据处理数据
	//1.判断帧头
	if(revmessage.rcv_buff[0] != 0xAA){
		revmessage.rcv_flag = 0;
		revmessage.rcv_count = 0;//为下一次接收数据做准备
		return 2;
	}
  //2.判断帧尾
	if(revmessage.rcv_buff[3] != 0xCC){
		revmessage.rcv_flag = 0;
		revmessage.rcv_count = 0;//为下一次接收数据做准备
		return 3;
	}
	//3.解析数据
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
	revmessage.rcv_count = 0;//为下一次接收数据做准备
	return 0x0;
}

void USART1_DMATx_Config(void)
{
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);//使能USART1_Tx的DMA1发送功能
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMA_InitStruct = {0};
	
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;//外设作为目标
	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)&USART1->DR;//外设地址
	DMA_InitStruct.DMA_MemoryBaseAddr = 0;//指向内存的首地址
	DMA_InitStruct.DMA_BufferSize = 0;    //要传输的数据长度 = 0
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//字节
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//字节
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;//正常模式 -- DMA传输1次
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址不增加
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器递增
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;//优先级
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;//不使用内存到内存
	
	DMA_Init(DMA1_Channel4,&DMA_InitStruct);
	//使能DMA
	DMA_Cmd(DMA1_Channel4,DISABLE);
}

/*
使用USART1的DMA功能，传输len个数据
*/
void USART1_DMASendStr(u8 *pdata,u32 len)
{
	//关闭DMA1 通道4功能
	DMA_Cmd(DMA1_Channel4,DISABLE);
	//修改存储器地址
	DMA1_Channel4->CMAR = (u32)pdata;
	//修改传输数据的长度
	DMA1_Channel4->CNDTR = len;
	//打开DMA1 通道4功能
	DMA_Cmd(DMA1_Channel4,ENABLE);
}


