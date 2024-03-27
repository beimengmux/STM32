#ifndef _WIFI_H_
#define _WIFI_H_

#include "stm32f10x.h"

#define ESP_S_LENGTH 600
#define ESP_R_LENGTH 1024

struct tagWIFIMessage
{
	uint8_t rcv_buff[ESP_R_LENGTH];
	uint8_t send_buff[ESP_S_LENGTH];
	u16 rcv_flag;                   //һ֡��Ϣ������ɱ�־ 0--û�н������  1--�������
	u16 rcv_count;
};

struct WIFI
{
	char  Wifi_Name[30];
	char  WIFI_Password[15];
	u8 CS;
};
extern u8 WIFI_Flag;
extern uint8_t Net_State; //��������״̬ 0 δ���� 1 ����͸��ģʽ�ɹ�
extern uint8_t Net_Step; //AT��������
extern struct tagWIFIMessage wifi_message;
extern uint32_t timestamp_cnt;
extern struct WIFI wifi;

void WIFI_Config(void);
void USART3_Config(u32 brr);
void USART3_NVICConfig(void);
void USART3_Send(u8 *pdata,u32 len);

uint8_t WIFI_SendCmdAndRevAck(char *cmd,char *ack,uint32_t timeout,uint32_t check_cnt);
uint8_t WIFI_CheckAck(char* src, char* dest, uint32_t timeout);
void WIFI_SendCmd(u8 *pdata,u32 len);
void WIFI_Test1(void);
void WIFI_Test2(void);
void Net_Connect(void);
void WIFI_Time(void);
void WIFI_Revise_AP_Net(void);
void WIFI_SET_AP(void);

#endif
