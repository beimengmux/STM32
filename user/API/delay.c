#include "delay.h"

void Delay_nopus(u32 time)
{
	while(time--){
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();
	}
}
void Delay_nopms(u32 time)
{
	Delay_nopus(time*1000);
}

//滴答定时器，定时完成执行中断服务函数
u32 timeled[2] = {0,5000};
u32 RGBled[2] = {0,200};
u32 timekey[2] = {0,15};
u32 timeDHT11[2] = {0,5000};
u32 timeRTC[2] = {0,1000};
u32 timeKQM[2] = {0,30000};
u32 timeyuyin[2] = {0,10000};
//void SysTick_Handler(void)
//{
//	timeled[0]++;
//	timekey[0]++;
//	RGBled[0]++;
//	timeDHT11[0]++;
//	timeRTC[0]++;
//	timeKQM[0]++;
//	timeyuyin[0]++;
//}
