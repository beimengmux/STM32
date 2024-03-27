#ifndef _SU_03T_H_
#define _SU_03T_H_

#include "stm32f10x.h"


struct SU03Message
{
	u8 rcv_buff[16];
	u8 rcv_flag;//һ֡��Ϣ������ɱ�־ 0--û�н������  1--�������
	u8 rcv_count;
};

void UART4_Config(u32 brr);
void UART4_NVICConfig(void);
u8 SU03_DataAnalysis(void);
void SU03T_TxBuff(u8 * data,u16 len);
void SU03_Send(void);

#endif
