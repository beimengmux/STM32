#include "wifi.h"
#include "delay.h"
#include "string.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stm32_eval_spi_flash.h"

char  Wifi_Name[30]="Xiaomi  12s Ultra";    //����Ĭ��wifi�˺�
char  WIFI_Password[15]="12345678";         //����Ĭ��wifi����

struct WIFI wifi = {0};                     //���������޸�wifi�����Ϣ

struct tagWIFIMessage wifi_message={.rcv_flag = 0,.rcv_count = 0};
uint8_t Net_State = 0;       //��������״̬  0  δ����  1 ����͸��ģʽ�ɹ�
uint8_t Net_Step = 0;        //AT��������
char WIFI_Buff[128] = {0};   //ƴ���ַ������õ��ı���

void WIFI_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	//USART_EN -- PE6 + USART3
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOE,&GPIO_InitStruct);

	GPIO_ResetBits(GPIOE,GPIO_Pin_6);//����
	Delay_nopms(500);
	GPIO_SetBits(GPIOE,GPIO_Pin_6);//����	
	USART3_Config(115200);
	Delay_nopms(3000);	
}

void USART3_Config(u32 brr)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	USART_InitTypeDef USART_InitStruct = {0};
	
	USART_InitStruct.USART_BaudRate = brr;//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;//��У��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//1��ֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//���ݳ���Ϊ8
	USART_Init(USART3,&USART_InitStruct);
	
	//�ж�����
	USART3_NVICConfig();
	
	//3.ʹ�ܴ��ڹ���
	USART_Cmd(USART3,ENABLE);
	
}

//����3�жϳ�ʼ��
void USART3_NVICConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	//2.1 �����ж�Դ
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//�����ж�
	USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);//�����ж�
  //2.2 �����ж�ͨ����NVIC��
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;//�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  //ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//ռ��
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//�μ�
	NVIC_Init(&NVIC_InitStruct);
}

//����3�жϷ�����
void USART3_IRQHandler(void)
{
	u8 temp = 0;
	//1.�ж��ж�Դ
	if(USART_GetITStatus(USART3,USART_IT_RXNE) == SET){  //����
	//2.����жϱ�־λ
	USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	USART1->DR = USART3->DR;                             //���Թ���
	//3.��������
		wifi_message.rcv_buff[wifi_message.rcv_count++] = USART3->DR;
	}
	if(USART_GetITStatus(USART3,USART_IT_IDLE) == SET)   //����
	{
		USART_ClearITPendingBit(USART3,USART_IT_IDLE);
		temp = USART3->DR;                                 //����жϱ�־λ
		wifi_message.rcv_flag = 1;
	}	
}

//����3��������
void USART3_Send(u8 *pdata,u32 len)
{
	for(u32 i =0;i<len;i++)
	{
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
		USART_SendData(USART3,pdata[i]);
	}
}

//WIFI����
void WIFI_SendCmd(u8 *pdata,u32 len)
{
	USART3_Send(pdata,len);
}

/**
 * ���ܣ����WIFI��Ӧ��
 * ������
 *			 src��WIFI���յ����ݵĻ�����
 *       dest��Ҫ����Ӧ���ź�
 *       timeout: �ȴ�Ӧ���źŵĲ�ѯ��ʱʱ��
 * ����ֵ��
         0 -- ��ȷ
				 1 -- ��ʱ���
				 2 -- ERROR -- ָ�����
         3 -- ����ģʽ�£�Ӧ���źŽ��ղ���ȫ			 						
 */
uint8_t WIFI_CheckAck(char* src, char* dest, uint32_t timeout)
{
	char *check = NULL;
	uint32_t time = timeout;
begin:
	//�ж�WIFI�Ƿ������ݷ��أ���ʱ��δ���յ�����
	while(timeout >0 && wifi_message.rcv_flag == 0)
	{
		vTaskDelay(1);//��ʱ1ms
		timeout--;
	}
	//������յ������ݣ��жϽ��յ������Ƿ�ΪӦ���ERROR
	if(wifi_message.rcv_count == 0 || timeout == 0)
		return 1;//��ʱ���
	
	//1.����Ƿ���յ�������ȷӦ��
	check = strstr(src,dest);
	if(check != NULL)
		return 0;
	
	check = strstr(src,"ERROR");
	if(check != NULL)
		return 2;
	
	check = strstr(src,"\r\n");
	if(check != NULL){
		wifi_message.rcv_flag = 0;
		timeout = time;//����Ѱ��
		goto begin;
	}
	return 0;
}
/**
 * ���ܣ�WIFI����ָ���ȡӦ��
 * ������
 *       cmd -- ָ���ַ���
 *       ack -- Ӧ���ַ���
 *       timeout -- Ӧ�����ʱ�� ʱ�䵥λΪms
 *			 check_cnt >= 1 -- ����ָ��Ĵ���������ģ��û��Ӧ�������෢���Σ�
 * ����ֵ��0 -- �ɹ�		>0 -- ʧ��
				 1 -- ��ʱ���
				 2 e-- ERROR -- ָ�����
 */
uint8_t WIFI_SendCmdAndRevAck(char *cmd,char *ack,uint32_t timeout,uint32_t check_cnt)
{
	uint8_t rev = 0;//���淵��ֵ
	//��ֹ����
	wifi_message.rcv_count = 0;
	wifi_message.rcv_flag = 0;
	memset(wifi_message.rcv_buff,0,1024);
CHECK:
	while(check_cnt){
		//1.��������
		if(cmd != NULL)
			WIFI_SendCmd((uint8_t *)cmd,strlen(cmd));
		//2.�ȴ�Ӧ����
		if(ack != NULL)
			rev = WIFI_CheckAck((char *)wifi_message.rcv_buff,ack,timeout);
		//3.���ݻ���������
		wifi_message.rcv_count = 0;
		wifi_message.rcv_flag = 0;
		//4.�ж��Ƿ�Ӧ��Ӧ������ѭ��
		if(rev == 1 && (--check_cnt) > 0)
		{
			goto CHECK;
		}
		else 
			break;
	}
	return rev;
}


void WIFI_Test1(void)
{
	//1.AT
	WIFI_SendCmd("AT\r\n",strlen("AT\r\n"));
	Delay_nopms(1000);
	//2.AT+CWMODE=1
	WIFI_SendCmd("AT+CWMODE=1\r\n",strlen("AT+CWMODE=1\r\n"));
	Delay_nopms(1000);
	//3.AT+CWJAP="Xiaomi  12s Ultra","12345678"
	WIFI_SendCmd("AT+CWJAP=\"Xiaomi  12s Ultra\",\"12345678\"\r\n",strlen("AT+CWJAP=\"Xiaomi  12s Ultra\",\"12345678\"\r\n"));
	Delay_nopms(5000);
	//4.AT+CIPSTART="TCP","122.114.122.174",35095
	WIFI_SendCmd("AT+CIPSTART=\"TCP\",\"122.114.122.174\",45473\r\n",strlen("AT+CIPSTART=\"TCP\",\"122.114.122.174\",45473\r\n"));
	Delay_nopms(3000);
	//5.AT+CIPMODE=1
	WIFI_SendCmd("AT+CIPMODE=1\r\n",strlen("AT+CIPMODE=1\r\n"));
	Delay_nopms(1000);
	//6.AT+CIPSEND
	WIFI_SendCmd("AT+CIPSEND\r\n",strlen("AT+CIPSEND\r\n"));
	Delay_nopms(1000);
	WIFI_SendCmd("guolinda",8);
	Delay_nopms(1000);
	//7.+++
	WIFI_SendCmd("+++",3);
	Delay_nopms(1000);
	//8.AT+CIPCLOSE
	WIFI_SendCmd("AT+CIPCLOSE\r\n",strlen("AT+CIPCLOSE\r\n"));
	Delay_nopms(1000);
}

void WIFI_Test2(void)
{
	u8 ret = 0;
	//1.AT
	ret = WIFI_SendCmdAndRevAck("AT\r\n","OK",1000,1);
	printf("ret = %d\r\n",ret);
	//2.AT+CWMODE=1
	ret = WIFI_SendCmdAndRevAck("AT+CWMODE=1\r\n","OK",1000,1);
	printf("ret = %d\r\n",ret);
	//3.AT+CWJAP="9205","12345678"
	ret = WIFI_SendCmdAndRevAck("AT+CWJAP=\"Xiaomi  12s Ultra\",\"12345678\"\r\n","OK",10000,1);
	printf("ret = %d\r\n",ret);	
	//4.AT+CIPSTART="TCP","122.114.122.174",35095
	ret = WIFI_SendCmdAndRevAck("AT+CIPSTART=\"TCP\",\"122.114.122.174\",45473\r\n","OK",10000,1);
	printf("ret = %d\r\n",ret);
	//5.AT+CIPMODE=1
	ret = WIFI_SendCmdAndRevAck("AT+CIPMODE=1\r\n","OK",5000,1);
	printf("ret = %d\r\n",ret);
	//6.AT+CIPSEND
	ret = WIFI_SendCmdAndRevAck("AT+CIPSEND\r\n",">",1000,1);
	printf("ret = %d\r\n",ret);
	WIFI_SendCmd("CHINESE",7);
	Delay_nopms(1000);
	//7.+++
	WIFI_SendCmd("+++",3);
	Delay_nopms(1000);
	//8.AT+CIPCLOSE
	ret = WIFI_SendCmdAndRevAck("AT+CIPCLOSE\r\n","OK",1000,1);
	printf("ret = %d\r\n",ret);
}

u8 WIFI_Flag = 1;
//�����Ĳ���
void Net_Connect(void)
{
	switch(Net_Step)
	{
		case 0:
			if(WIFI_SendCmdAndRevAck("AT\r\n","OK",1000,1)==0)
				Net_Step++;
			break;
		case 1:
			if(WIFI_SendCmdAndRevAck("AT+CWMODE=1\r\n","OK",5000,1)==0)
				Net_Step++;
			break;
		case 2:
			memset(WIFI_Buff,0,sizeof(WIFI_Buff));
			if(wifi.CS == 1){  //Ӳ�������˾�ʹ�ø��Ĺ����
				sprintf(WIFI_Buff,"AT+CWJAP=\"%s\",\"%s\"\r\n",wifi.Wifi_Name,wifi.WIFI_Password);
			}
			else{         //û���޸���ʹ�ø�λĬ�ϵ�
				sprintf(WIFI_Buff,"AT+CWJAP=\"%s\",\"%s\"\r\n",Wifi_Name,WIFI_Password);
			}
			if(WIFI_SendCmdAndRevAck(WIFI_Buff,"OK",15000,1)==0)
				Net_Step++;	
			break;
		case 3:
			if(WIFI_Flag == 1)
			{
				if(WIFI_SendCmdAndRevAck("AT+CIPSTART=\"TCP\",\"api.m.taobao.com\",80\r\n","OK",10000,1)==0)
					Net_Step++;
			}
			else
			{
				if(WIFI_SendCmdAndRevAck("AT+CIPSTART=\"TCP\",\"iot-06z00df3rp0rddf.mqtt.iothub.aliyuncs.com\",1883\r\n","OK",10000,1)==0)
					Net_Step++;	
			}
			break;
		case 4:
			if(WIFI_SendCmdAndRevAck("AT+CIPMODE=1\r\n","OK",1000,1)==0)
				Net_Step++;	
			break;
		case 5:
			if(WIFI_SendCmdAndRevAck("AT+CIPSEND\r\n",">",3000,1)==0)
			{
				Net_State=1;
				Net_Step=0;
			}	
			break;
		default:
			Net_Step = 0;
			break;
	}
}


uint32_t timestamp_cnt = 0;                      //�����ȡ���ϵ�����

void WIFI_Time(void)
{
	WIFI_SendCmd("GET http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp\r\n",strlen("GET http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp\r\n"));
	Delay_nopms(3000);
	char *timestamp_start = strstr((char *)wifi_message.rcv_buff,"data");      //�ڽ��ܵĽṹ���в���data�ַ���
	if (timestamp_start != NULL) 							 //���Ҳ�Ϊ��
	{
		timestamp_start += (strlen("data")+8);	 //����data
		char timestamp[14];
		strncpy(timestamp, timestamp_start, 10); //����13���ַ���timestamp����
		timestamp[13] = '\0'; 					         //����ַ���������
		timestamp_cnt =atoi(timestamp);		       //ת��Ϊ����
	}
	
	//1.��BKP��PWR��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP,ENABLE);
	//2.�������BKP������
	PWR_BackupAccessCmd(ENABLE);
	RTC_SetCounter(timestamp_cnt); //������
	
	WIFI_Flag = 0;
	Net_State = 0;
	memset(wifi_message.rcv_buff,0,sizeof(wifi_message.rcv_buff));
	//����WIFIģ��
	GPIO_ResetBits(GPIOE,GPIO_Pin_6);//����
	Delay_nopms(500);
	GPIO_SetBits(GPIOE,GPIO_Pin_6);//����
	vTaskDelay(6000);
}

//����APģʽ���ͷ��ȵ㣬�޸�WIFI�˺ź�����
void WIFI_Revise_AP_Net(void)
{
	switch(Net_Step)
	{
		case 0:
			Delay_nopms(5000);
			if(WIFI_SendCmdAndRevAck("AT\r\n","OK",1000,1)==0)		
				Net_Step++;
			break;
		case 1:
			if(WIFI_SendCmdAndRevAck("AT+CWMODE=2\r\n","OK",5000,1)==0)			
				Net_Step++;
			break;	
		case 2:		//=0����·����ģʽ     =1����·����ģʽ
			if(WIFI_SendCmdAndRevAck("AT+CIPMUX=1\r\n","OK",6000,1)==0)		
				Net_Step++;				
		case 3:		//���� ESP8266 SoftAP �����ò���,,������������ͨ���ţ���������4�����ĸ����������ܷ�ʽ������ѡ��4��
			if(WIFI_SendCmdAndRevAck("AT+CWSAP=\"ATK_ESP8266\",\"12345678\",6,4\r\n","OK",15000,1)==0)		
				Net_Step++;				//AT+CWSAP_CUR="ESP8266","1234567890",5,3
			break;
		case 4://���ö˿ں�
			if(WIFI_SendCmdAndRevAck("AT+CIPSERVER=1,1001\r\n","OK",1000,1)==0)			
				Net_Step++;				
			break;
		case 5://��ѯIP��ַ�Ƕ���
			if(WIFI_SendCmdAndRevAck("AT+CIFSR\r\n","OK",1000,1)==0)		
			{
				Net_Step++;
			}				
		case 6:
				WIFI_SET_AP();
				break;
		default:
			break;
	}
}


//�����޸ĺ��WIFI����
void WIFI_SET_AP(void)
{
	//������ܻ����bug ��Ϊ�������һֱ��������� ���ܻ�û���������� �Ѿ���ʼ������
	char *timestamp_start = strstr((char *)wifi_message.rcv_buff,"wifiname");      //�ڽ��ܵĽṹ���в���data�ַ���
	if (timestamp_start != NULL) 							 //���Ҳ�Ϊ��
	{
		timestamp_start += (strlen("wifiname") + 3); // ���� "wifiname"
    memset(wifi.Wifi_Name, 0, sizeof(wifi.Wifi_Name));
    char *end_quote = strchr(timestamp_start, '\"'); // ������һ��˫����
    if (end_quote != NULL) // ����ҵ�����һ��˫����
    {
        size_t length = end_quote - timestamp_start; // ����Ҫ���Ƶ��ַ���
        strncpy(wifi.Wifi_Name, timestamp_start, length); // �����ַ��� Wifi_Name ����
    }
	}
	
	char *timestamp_s = strstr((char *)wifi_message.rcv_buff,"password");      //�ڽ��ܵĽṹ���в���data�ַ���
	if (timestamp_s != NULL) 							 //���Ҳ�Ϊ��
	{
		timestamp_s += (strlen("password")+3);	 //����data
		memset(wifi.WIFI_Password,0,sizeof(wifi.WIFI_Password));
		char *end_quote = strchr(timestamp_s, '\"'); // ������һ��˫����
    if (end_quote != NULL) // ����ҵ�����һ��˫����
    {
        size_t length = end_quote - timestamp_s; // ����Ҫ���Ƶ��ַ���
        strncpy(wifi.WIFI_Password, timestamp_s, length); //����4���ַ���timestamp����
    }
		//����WIFIģ��
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);//����
		Delay_nopms(500);
		GPIO_SetBits(GPIOE,GPIO_Pin_6);//����
		vTaskDelay(5000);
		Net_Step = 0;	
		Net_State = 0;   			//���¿�ʼ����
		WIFI_Flag =1;         //���»�ȡʱ��
		memset(wifi_message.rcv_buff,0,sizeof(wifi_message.rcv_buff));
		
		//д�뵽flash
		sFLASH_EraseSector(FLASH_SectorToErase);    //flashд֮ǰһ��Ҫ����
		wifi.CS=1;                                  //��־λ��λ���޸�Ĭ��wifi�ɹ�
		sFLASH_WriteBuffer((uint8_t *)&wifi, FLASH_WriteAddress, sizeof(wifi)); //�������
	}
}
