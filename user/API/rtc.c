#include "rtc.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "time.h"
#include "stdio.h"
#include "wifi.h"

void RTC_Config(void)
{
	if (BKP_ReadBackupRegister(BKP_DR1) != 0x7777) //上电的第一次运行
  {
		//1.打开BKP和PWR的时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP,ENABLE);
		//2.允许进入BKP后备区域
		PWR_BackupAccessCmd(ENABLE);
		//3.使能LSE
		RCC_LSEConfig(RCC_LSE_ON);
		//4.等待LSE完成
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
		//5.选择LSE作为RTC的时钟源
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		//6.使能RTC时钟
		RCC_RTCCLKCmd(ENABLE);
		//7.等待RTC与APB1同步
		RTC_WaitForSynchro();
		//8.等待RTC最近一次写操作的完成
		RTC_WaitForLastTask();
		//9.RTC进入配置模式
		RTC_EnterConfigMode();
		//10.操作寄存器
		RTC_SetPrescaler(32767);        //分频器 32767+1
		RTC_SetCounter(timestamp_cnt);  //计数器 获取的秒数
		//11.等待RTC最近一次写操作的完成
		RTC_WaitForLastTask();
		BKP_WriteBackupRegister(BKP_DR1, 0x7777);
	}
}

void RTC_GetTime(void)
{
	time_t time = 0;
	struct tm *now_time ={0};
	time = RTC_GetCounter();
	now_time = localtime(&time);
	lv_label_set_text_fmt(guider_ui.screen_1_label_14,"%04d/%02d/%02d \r\n",now_time->tm_year+1900,now_time->tm_mon+1,now_time->tm_mday);
	lv_label_set_text_fmt(guider_ui.screen_1_label_15,"%02d:%02d:%02d\r\n",now_time->tm_hour+8,now_time->tm_min,now_time->tm_sec);
}
