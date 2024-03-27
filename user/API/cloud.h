#ifndef _CLOUD_H_
#define _CLOUD_H_

#include "stm32f10x.h"

#define  Subscribe_Topic       "/sys/k02vhQrIfuK/Device9025/thing/service/property/set"       //ƽ̨�·�������Ҫ���ĵ�����
#define  Publish_Topic_Reply   "/sys/k02vhQrIfuK/Device9025/thing/event/property/post_reply"  //ƽ̨�յ�STM32���������ݣ���Ӧ�������

void Mqtt_Cloud_Connect(void);
void Mqtt_Cloud_Publish(void);
void Mqtt_Subscribe_Ali(void);
void Mqtt_Heart_Send(void);
uint32_t MQTT_LengthCalculation(uint8_t *buff, uint8_t *len);
void Ali_AlsDataAck(char *payload);

#endif
