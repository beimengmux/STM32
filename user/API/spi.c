#include "spi.h"

/*
    ѡ�õ�    SPI2
FLASH_CS -- PB12 -- ͨ���������ģʽ
SPI_SCK  -- PB13 -- �����������ģʽ
SPI_MISO -- PB14 -- ��������
SPI_MOSI -- PB15 -- �����������
*/
void SPI2_Config(void)
{
	//1.������Ӧ�Ĺܽ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);//��Ƭѡ����
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//2.��ʼ��SPI2
		//2.1 ��SPI2ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	//2.2 ���ʡ�CPOL��CPHA�����ݿ�ȡ����͸�λ/��λ��NSS�����ģʽ/Ӳ��ģʽ��
	SPI_InitTypeDef SPI_InitStruct = {0};
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//�������� PCLK/2
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;//ģʽ0/3
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;//���ݿ�� = 8
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//ȫ˫��
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;//��λ��ǰ
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;//����ģʽ
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//NSS�ܽ�Ϊ���ģʽ
	SPI_Init(SPI2,&SPI_InitStruct);
	//3.ʹ��SPI2
	SPI_Cmd(SPI2,ENABLE);
	
}


u8 SPI2_SendAndRecvData(u8 data)
{
	//1.��������
	//���DR�Ĵ����Ƿ�Ϊ��,��һ�η����Ƿ����
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET);
	//��һ�εķ������,Ȼ�����ݷ��ͳ�ȥ
	SPI_I2S_SendData(SPI2,data);
	//2.��������
	//�ȴ��������
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == RESET);
	//�����ݼĴ����У�ȡ���ݣ�������
	return SPI_I2S_ReceiveData(SPI2);
}
