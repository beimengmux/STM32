#ifndef _RTC_H_
#define _RTC_H_

#include "stm32f10x.h"


u32 RTC_InitTime(void);
void RTC_Config(void);
void RTC_GetTime(void);
extern struct tm *now_time;

#endif
