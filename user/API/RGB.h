#ifndef _GRB_H_
#define _GRB_H_

#include "stm32f10x.h"

//#define RGBB_ON    (GPIOA->ODR &= ~(1<<6))
//#define RGBB_OFF   (GPIOA->ODR |= (1<<6))
//#define RGBG_ON    (GPIOA->ODR &= ~(1<<7))
//#define RGBG_OFF   (GPIOA->ODR |= (1<<7))
//#define RGBR_ON    (GPIOA->ODR &= ~(1<<8))
//#define RGBR_OFF   (GPIOA->ODR |= (1<<8))

#define RGBB_ON    GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_RESET)
#define RGBB_OFF   GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_SET)
#define RGBG_ON    GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_RESET)
#define RGBG_OFF   GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_SET)
#define RGBR_ON    GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET)
#define RGBR_OFF   GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET)

void RGB_configlib(void);
void RGB_flow(void);
void RGB_SetMode(u8 mode);

#define RGB_MODE_OFF 0
#define RGB_MODE_R 1
#define RGB_MODE_G 2
#define RGB_MODE_B 3
#define RGB_MODE_ON 4

#endif
