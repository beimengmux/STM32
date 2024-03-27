#ifndef _KQM6600_H_
#define _KQM6600_H_

#include "stm32f10x.h"

struct KQMMessage
{
	u16 rcv_buff[16];
	u16 rcv_flag;//一帧信息接收完成标志 0--没有接收完成  1--接收完成
	u16 rcv_count;
};
extern struct tagSensor KQM;

struct tagSensor
{
	float voc;  //空气质量
	float hcho; //甲醛
	u16 co2;  //CO2
	u16 Lightintensity;
	u16 fumes;
	float chip;
};

void USART2_Config(u32 brr);
void USART2_NVICConfig(void);
u8 KQM6600_DataAnalysis(void);

#endif
