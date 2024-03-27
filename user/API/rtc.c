#include "rtc.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "time.h"
#include "stdio.h"
#include "wifi.h"

void RTC_Config(void)
{
	if (BKP_ReadBackupRegister(BKP_DR1) != 0x7777) //�ϵ�ĵ�һ������
  {
		//1.��BKP��PWR��ʱ��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP,ENABLE);
		//2.�������BKP������
		PWR_BackupAccessCmd(ENABLE);
		//3.ʹ��LSE
		RCC_LSEConfig(RCC_LSE_ON);
		//4.�ȴ�LSE���
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
		//5.ѡ��LSE��ΪRTC��ʱ��Դ
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		//6.ʹ��RTCʱ��
		RCC_RTCCLKCmd(ENABLE);
		//7.�ȴ�RTC��APB1ͬ��
		RTC_WaitForSynchro();
		//8.�ȴ�RTC���һ��д���������
		RTC_WaitForLastTask();
		//9.RTC��������ģʽ
		RTC_EnterConfigMode();
		//10.�����Ĵ���
		RTC_SetPrescaler(32767);        //��Ƶ�� 32767+1
		RTC_SetCounter(timestamp_cnt);  //������ ��ȡ������
		//11.�ȴ�RTC���һ��д���������
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
