#ifndef _SPI_H_
#define _SPI_H_

#include "stm32f10x.h"
  
void SPI2_Config(void);
u8 SPI2_SendAndRecvData(u8 data);

#endif
