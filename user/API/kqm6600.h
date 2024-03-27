#ifndef _KQM6600_H_
#define _KQM6600_H_

#include "stm32f10x.h"

struct KQMMessage
{
	u16 rcv_buff[16];
	u16 rcv_flag;//һ֡��Ϣ������ɱ�־ 0--û�н������  1--�������
	u16 rcv_count;
};
extern struct tagSensor KQM;

struct tagSensor
{
	float voc;  //��������
	float hcho; //��ȩ
	u16 co2;  //CO2
	u16 Lightintensity;
	u16 fumes;
	float chip;
};

void USART2_Config(u32 brr);
void USART2_NVICConfig(void);
u8 KQM6600_DataAnalysis(void);

#endif
