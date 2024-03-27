#include "DHT11.h"
#include "delay.h"
#include "stdio.h"
/*
所对应的接口配置为输入和输出模式
mode = 0 -- 输出模式 （通用推挽） 50MHZ
			 1 -- 输入模式 （浮空输入）
*/

struct DHT11 dht11 ={0,0};

//初始化
void DHT11_GPIOConfig(u8 mode)
{
	//打开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	//结构体
	GPIO_InitTypeDef GPIO_InitStruct= {0};
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	if(mode == DHT11_Mode_OUT){
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	}else if(mode == DHT11_Mode_IN)
	{
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	GPIO_Init(GPIOG,&GPIO_InitStruct);
}

/*
读取DHT11的数据
参数：t和h用于保存读取数据的温度和湿度
返回值：1表示成功，0表示失败
*/

u8 DHT11_Read_T_H(float* t,u8* h)
{

	int i = 0,j = 0;
	u8 buff[5] = {0};
	//1.stm32发送开始信号
	//1.1把DHT11的DATA管脚配置成输出模式
	DHT11_GPIOConfig(DHT11_Mode_OUT);

	//1.2发送低电平> 18 us+高电平
	DHT11_DATA_L;
	Delay_nopms(18);
	DHT11_DATA_H;
	//2.DHT11发送应答信号（83us低电平+87us高电平）
	DHT11_GPIOConfig(DHT11_Mode_IN);
	while(DHT11_DATA == 1);//等待变为低电平
	while(DHT11_DATA == 0);//等待变为高电平
		
	//3.接受DHT11发送过来的数据
	for(i = 0;i < 5; i++)
	{
		for(j = 0;j < 8;j++ )
		{
			while(DHT11_DATA == 1);//等待变为低电平
			while(DHT11_DATA == 0);//等待变为高电平
			Delay_nopus(30);
			if(DHT11_DATA == 1){
				buff[i] |= (1<<(7-j));
			}else{
				buff[i] &= ~(1<<(7-j));
			}	
		}
	}
	//buff[i] <<= 1;
	//if(DHT11_DATA == 1)
	//	buff[i]++;
	//4.校验
	if(buff[4] == (buff[0]+buff[1]+buff[2]+buff[3]))
	{
		int temp = buff[3] & 0x7f; //保留小数部分
		if((buff[3] & 0x80) > 0)
		{
			*t = -(buff[2]+temp/10.0);
		}else{
		*t = buff[2]+temp/10.0;//温度

		}
		*h = buff[0];//湿度humidity
		return 1;
	}else{
		return 0;
	}
}


//在串口上显示DHT11的数据
void DHT11_Display(void)
{
	float t;
	u8 h;
	if(DHT11_Read_T_H(&t,&h) == 1)
	{
		dht11.t = t;
		dht11.h=h;
//		printf("temperature：%0.1f\r\n",t);  //打印温度
//		printf("humidity：%d\r\n",h);        //打印湿度
	}else
		printf("DHT11获取数据失败\r\n");
}
