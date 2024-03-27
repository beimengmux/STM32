#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f10x.h"

void Delay_nopus(u32 time);
void Delay_nopms(u32 time);
void Delay_config(void);

extern u32 RGBled[2];
extern u32 timeled[2];
extern u32 timekey[2];
extern u32 timeDHT11[2];
extern u32 timeRTC[2];
extern u32 timeKQM[2];
extern u32 timeyuyin[2];

#endif
