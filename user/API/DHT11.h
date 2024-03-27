#ifndef _DHT11_H_
#define _DHT11_H_

#include "stm32f10x.h"

#define DHT11_Port GPIOG
#define DHT11_Pin GPIO_Pin_11

#define DHT11_DATA_H GPIO_WriteBit(DHT11_Port,DHT11_Pin,Bit_SET)
#define DHT11_DATA_L GPIO_WriteBit(DHT11_Port,DHT11_Pin,Bit_RESET)

//¶ÁÈ¡¹Ü½Å×´Ì¬
#define DHT11_DATA GPIO_ReadInputDataBit(DHT11_Port,DHT11_Pin)


#define DHT11_Mode_OUT 0
#define DHT11_Mode_IN  1

void DHT11_GPIOConfig(u8 mode);
u8 DHT11_Read_T_H(float *t,u8 *h);
void DHT11_Display(void);



struct DHT11{
	float t;
	u8 h;
};

extern struct DHT11 dht11;

#endif
