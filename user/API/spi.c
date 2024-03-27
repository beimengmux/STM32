#include "spi.h"

/*
    选用的    SPI2
FLASH_CS -- PB12 -- 通用推挽输出模式
SPI_SCK  -- PB13 -- 复用推挽输出模式
SPI_MISO -- PB14 -- 浮空输入
SPI_MOSI -- PB15 -- 复用推挽输出
*/
void SPI2_Config(void)
{
	//1.配置相应的管脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);//把片选拉高
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//2.初始化SPI2
		//2.1 打开SPI2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	//2.2 速率、CPOL、CPHA、数据宽度、发送高位/低位、NSS（软件模式/硬件模式）
	SPI_InitTypeDef SPI_InitStruct = {0};
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//传输速率 PCLK/2
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;//模式0/3
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;//数据宽度 = 8
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//全双工
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;//高位在前
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;//主机模式
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//NSS管脚为软件模式
	SPI_Init(SPI2,&SPI_InitStruct);
	//3.使能SPI2
	SPI_Cmd(SPI2,ENABLE);
	
}


u8 SPI2_SendAndRecvData(u8 data)
{
	//1.发送数据
	//检测DR寄存器是否为空,上一次发送是否完成
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET);
	//上一次的发送完成,然后将数据发送出去
	SPI_I2S_SendData(SPI2,data);
	//2.接收数据
	//等待接收完成
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == RESET);
	//从数据寄存器中，取数据，并返回
	return SPI_I2S_ReceiveData(SPI2);
}
