#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)
#define KEY3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define KEY4 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)

u8 Key_GetValue(void);
void KEY_configlib(void);

//#define key1_ON    (GPIOA->IDR & (1 << 0))

#endif
