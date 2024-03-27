#include "DHT11.h"
#include "delay.h"
#include "stdio.h"
/*
����Ӧ�Ľӿ�����Ϊ��������ģʽ
mode = 0 -- ���ģʽ ��ͨ�����죩 50MHZ
			 1 -- ����ģʽ ���������룩
*/

struct DHT11 dht11 ={0,0};

//��ʼ��
void DHT11_GPIOConfig(u8 mode)
{
	//��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	//�ṹ��
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
��ȡDHT11������
������t��h���ڱ����ȡ���ݵ��¶Ⱥ�ʪ��
����ֵ��1��ʾ�ɹ���0��ʾʧ��
*/

u8 DHT11_Read_T_H(float* t,u8* h)
{

	int i = 0,j = 0;
	u8 buff[5] = {0};
	//1.stm32���Ϳ�ʼ�ź�
	//1.1��DHT11��DATA�ܽ����ó����ģʽ
	DHT11_GPIOConfig(DHT11_Mode_OUT);

	//1.2���͵͵�ƽ> 18 us+�ߵ�ƽ
	DHT11_DATA_L;
	Delay_nopms(18);
	DHT11_DATA_H;
	//2.DHT11����Ӧ���źţ�83us�͵�ƽ+87us�ߵ�ƽ��
	DHT11_GPIOConfig(DHT11_Mode_IN);
	while(DHT11_DATA == 1);//�ȴ���Ϊ�͵�ƽ
	while(DHT11_DATA == 0);//�ȴ���Ϊ�ߵ�ƽ
		
	//3.����DHT11���͹���������
	for(i = 0;i < 5; i++)
	{
		for(j = 0;j < 8;j++ )
		{
			while(DHT11_DATA == 1);//�ȴ���Ϊ�͵�ƽ
			while(DHT11_DATA == 0);//�ȴ���Ϊ�ߵ�ƽ
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
	//4.У��
	if(buff[4] == (buff[0]+buff[1]+buff[2]+buff[3]))
	{
		int temp = buff[3] & 0x7f; //����С������
		if((buff[3] & 0x80) > 0)
		{
			*t = -(buff[2]+temp/10.0);
		}else{
		*t = buff[2]+temp/10.0;//�¶�

		}
		*h = buff[0];//ʪ��humidity
		return 1;
	}else{
		return 0;
	}
}


//�ڴ�������ʾDHT11������
void DHT11_Display(void)
{
	float t;
	u8 h;
	if(DHT11_Read_T_H(&t,&h) == 1)
	{
		dht11.t = t;
		dht11.h=h;
//		printf("temperature��%0.1f\r\n",t);  //��ӡ�¶�
//		printf("humidity��%d\r\n",h);        //��ӡʪ��
	}else
		printf("DHT11��ȡ����ʧ��\r\n");
}
