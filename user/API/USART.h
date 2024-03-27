#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "BEEP.h"
#include "RGB.h"
#include "LED.h"

struct tagUSARTMessage
{
	u8 rcv_buff[16];
	u8 rcv_flag;//   一帧信息接收完成标志 0--没有接收完成  1--接收完成
	u8 rcv_count;
};

void USART1_Config(u32 brr);
void USART1_NVICConfig(void);
u8 USART1_DataAnalysis(void);
void USART1_Send(u8 data);
void USART1_SendStr(u8 *pdata);
void USART1_SendBuff(u8 *pdata,uint16_t length);
void USART1_RecvTest1(void);
void USART1_RecvTest2(void);
int fputc(int c,FILE *stream);
void USART1_DMATx_Config(void);
void USART1_DMASendStr(u8 *pdata,u32 len);

//void USART1_Revc(void);
#endif
