#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"
#include "stdio.h"

extern u16 ADC_DMAGetValue[16];

u32 ADC_GetValue(void);
void ADC1_Config(void);
void ADC1_DMAConfig(void);
void ADC_value(void);



#endif
