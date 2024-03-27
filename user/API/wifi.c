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

char  Wifi_Name[30]="Xiaomi  12s Ultra";    //出厂默认wifi账号
char  WIFI_Password[15]="12345678";         //出厂默认wifi密码

struct WIFI wifi = {0};                     //用来接受修改wifi后的信息

struct tagWIFIMessage wifi_message={.rcv_flag = 0,.rcv_count = 0};
uint8_t Net_State = 0;       //网络链接状态  0  未连接  1 建立透传模式成功
uint8_t Net_Step = 0;        //AT联网步骤
char WIFI_Buff[128] = {0};   //拼接字符串所用到的变量

void WIFI_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	//USART_EN -- PE6 + USART3
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOE,&GPIO_InitStruct);

	GPIO_ResetBits(GPIOE,GPIO_Pin_6);//拉低
	Delay_nopms(500);
	GPIO_SetBits(GPIOE,GPIO_Pin_6);//拉高	
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
	
	USART_InitStruct.USART_BaudRate = brr;//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;//不校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//1个停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据长度为8
	USART_Init(USART3,&USART_InitStruct);
	
	//中断配置
	USART3_NVICConfig();
	
	//3.使能串口功能
	USART_Cmd(USART3,ENABLE);
	
}

//串口3中断初始化
void USART3_NVICConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	//2.1 配置中断源
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//接收中断
	USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);//空闲中断
  //2.2 配置中断通道（NVIC）
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;//中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  //使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//占先
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//次级
	NVIC_Init(&NVIC_InitStruct);
}

//串口3中断服务函数
void USART3_IRQHandler(void)
{
	u8 temp = 0;
	//1.判断中断源
	if(USART_GetITStatus(USART3,USART_IT_RXNE) == SET){  //接收
	//2.清除中断标志位
	USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	USART1->DR = USART3->DR;                             //调试功能
	//3.保存数据
		wifi_message.rcv_buff[wifi_message.rcv_count++] = USART3->DR;
	}
	if(USART_GetITStatus(USART3,USART_IT_IDLE) == SET)   //空闲
	{
		USART_ClearITPendingBit(USART3,USART_IT_IDLE);
		temp = USART3->DR;                                 //清除中断标志位
		wifi_message.rcv_flag = 1;
	}	
}

//串口3发送数据
void USART3_Send(u8 *pdata,u32 len)
{
	for(u32 i =0;i<len;i++)
	{
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
		USART_SendData(USART3,pdata[i]);
	}
}

//WIFI发送
void WIFI_SendCmd(u8 *pdata,u32 len)
{
	USART3_Send(pdata,len);
}

/**
 * 功能：检测WIFI的应答
 * 参数：
 *			 src：WIFI接收到数据的缓存区
 *       dest：要检测的应答信号
 *       timeout: 等待应答信号的查询超时时间
 * 返回值：
         0 -- 正确
				 1 -- 超时溢出
				 2 -- ERROR -- 指令错误
         3 -- 回显模式下，应答信号接收不完全			 						
 */
uint8_t WIFI_CheckAck(char* src, char* dest, uint32_t timeout)
{
	char *check = NULL;
	uint32_t time = timeout;
begin:
	//判断WIFI是否有数据返回，超时，未接收到数据
	while(timeout >0 && wifi_message.rcv_flag == 0)
	{
		vTaskDelay(1);//延时1ms
		timeout--;
	}
	//代表接收到的数据，判断接收到数据是否为应答和ERROR
	if(wifi_message.rcv_count == 0 || timeout == 0)
		return 1;//超时溢出
	
	//1.检测是否接收到的是正确应答
	check = strstr(src,dest);
	if(check != NULL)
		return 0;
	
	check = strstr(src,"ERROR");
	if(check != NULL)
		return 2;
	
	check = strstr(src,"\r\n");
	if(check != NULL){
		wifi_message.rcv_flag = 0;
		timeout = time;//从新寻找
		goto begin;
	}
	return 0;
}
/**
 * 功能：WIFI发送指令获取应答
 * 参数：
 *       cmd -- 指令字符串
 *       ack -- 应答字符串
 *       timeout -- 应答溢出时长 时间单位为ms
 *			 check_cnt >= 1 -- 发送指令的次数（可能模组没反应过来，多发几次）
 * 返回值：0 -- 成功		>0 -- 失败
				 1 -- 超时溢出
				 2 e-- ERROR -- 指令错误
 */
uint8_t WIFI_SendCmdAndRevAck(char *cmd,char *ack,uint32_t timeout,uint32_t check_cnt)
{
	uint8_t rev = 0;//保存返回值
	//防止干扰
	wifi_message.rcv_count = 0;
	wifi_message.rcv_flag = 0;
	memset(wifi_message.rcv_buff,0,1024);
CHECK:
	while(check_cnt){
		//1.发送命令
		if(cmd != NULL)
			WIFI_SendCmd((uint8_t *)cmd,strlen(cmd));
		//2.等待应答结果
		if(ack != NULL)
			rev = WIFI_CheckAck((char *)wifi_message.rcv_buff,ack,timeout);
		//3.数据缓冲区清零
		wifi_message.rcv_count = 0;
		wifi_message.rcv_flag = 0;
		//4.判断是否应答，应答跳出循环
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
//联网的步骤
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
			if(wifi.CS == 1){  //硬件储存了就使用更改过后的
				sprintf(WIFI_Buff,"AT+CWJAP=\"%s\",\"%s\"\r\n",wifi.Wifi_Name,wifi.WIFI_Password);
			}
			else{         //没有修改则使用复位默认的
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


uint32_t timestamp_cnt = 0;                      //储存获取网上的秒数

void WIFI_Time(void)
{
	WIFI_SendCmd("GET http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp\r\n",strlen("GET http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp\r\n"));
	Delay_nopms(3000);
	char *timestamp_start = strstr((char *)wifi_message.rcv_buff,"data");      //在接受的结构体中查找data字符串
	if (timestamp_start != NULL) 							 //查找不为空
	{
		timestamp_start += (strlen("data")+8);	 //跳过data
		char timestamp[14];
		strncpy(timestamp, timestamp_start, 10); //复制13个字符到timestamp数组
		timestamp[13] = '\0'; 					         //添加字符串结束符
		timestamp_cnt =atoi(timestamp);		       //转换为整数
	}
	
	//1.打开BKP和PWR的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP,ENABLE);
	//2.允许进入BKP后备区域
	PWR_BackupAccessCmd(ENABLE);
	RTC_SetCounter(timestamp_cnt); //计数器
	
	WIFI_Flag = 0;
	Net_State = 0;
	memset(wifi_message.rcv_buff,0,sizeof(wifi_message.rcv_buff));
	//重启WIFI模块
	GPIO_ResetBits(GPIOE,GPIO_Pin_6);//拉低
	Delay_nopms(500);
	GPIO_SetBits(GPIOE,GPIO_Pin_6);//拉高
	vTaskDelay(6000);
}

//设置AP模式，释放热点，修改WIFI账号和密码
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
		case 2:		//=0：单路连接模式     =1：多路连接模式
			if(WIFI_SendCmdAndRevAck("AT+CIPMUX=1\r\n","OK",6000,1)==0)		
				Net_Step++;				
		case 3:		//设置 ESP8266 SoftAP 的配置参数,,第三个参数，通道号，比如设置4。第四个参数，加密方式，可以选择4。
			if(WIFI_SendCmdAndRevAck("AT+CWSAP=\"ATK_ESP8266\",\"12345678\",6,4\r\n","OK",15000,1)==0)		
				Net_Step++;				//AT+CWSAP_CUR="ESP8266","1234567890",5,3
			break;
		case 4://设置端口号
			if(WIFI_SendCmdAndRevAck("AT+CIPSERVER=1,1001\r\n","OK",1000,1)==0)			
				Net_Step++;				
			break;
		case 5://查询IP地址是多少
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


//解析修改后的WIFI密码
void WIFI_SET_AP(void)
{
	//这里可能会出现bug 因为任务程序一直在这里解析 可能还没发送完数据 已经开始解析了
	char *timestamp_start = strstr((char *)wifi_message.rcv_buff,"wifiname");      //在接受的结构体中查找data字符串
	if (timestamp_start != NULL) 							 //查找不为空
	{
		timestamp_start += (strlen("wifiname") + 3); // 跳过 "wifiname"
    memset(wifi.Wifi_Name, 0, sizeof(wifi.Wifi_Name));
    char *end_quote = strchr(timestamp_start, '\"'); // 查找下一个双引号
    if (end_quote != NULL) // 如果找到了下一个双引号
    {
        size_t length = end_quote - timestamp_start; // 计算要复制的字符数
        strncpy(wifi.Wifi_Name, timestamp_start, length); // 复制字符到 Wifi_Name 数组
    }
	}
	
	char *timestamp_s = strstr((char *)wifi_message.rcv_buff,"password");      //在接受的结构体中查找data字符串
	if (timestamp_s != NULL) 							 //查找不为空
	{
		timestamp_s += (strlen("password")+3);	 //跳过data
		memset(wifi.WIFI_Password,0,sizeof(wifi.WIFI_Password));
		char *end_quote = strchr(timestamp_s, '\"'); // 查找下一个双引号
    if (end_quote != NULL) // 如果找到了下一个双引号
    {
        size_t length = end_quote - timestamp_s; // 计算要复制的字符数
        strncpy(wifi.WIFI_Password, timestamp_s, length); //复制4个字符到timestamp数组
    }
		//重启WIFI模块
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);//拉低
		Delay_nopms(500);
		GPIO_SetBits(GPIOE,GPIO_Pin_6);//拉高
		vTaskDelay(5000);
		Net_Step = 0;	
		Net_State = 0;   			//重新开始联网
		WIFI_Flag =1;         //重新获取时间
		memset(wifi_message.rcv_buff,0,sizeof(wifi_message.rcv_buff));
		
		//写入到flash
		sFLASH_EraseSector(FLASH_SectorToErase);    //flash写之前一定要擦除
		wifi.CS=1;                                  //标志位置位，修改默认wifi成功
		sFLASH_WriteBuffer((uint8_t *)&wifi, FLASH_WriteAddress, sizeof(wifi)); //保存参数
	}
}
