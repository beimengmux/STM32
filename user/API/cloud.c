#include "cloud.h"
#include "wifi.h"
#include "MQTTPacket.h"
#include "string.h"
#include "USART.h"
#include "delay.h"
#include "DHT11.h"
#include "kqm6600.h"
#include "LED.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cJSON.h"

#define ClientID "k02vhQrIfuK.Device9025|securemode=2,signmethod=hmacsha256,timestamp=1691480003752|"
#define Passwd "dd7b1adebfbd28e713d8105091690448c0f4cd0bee3ce928e58927f0940afed2"
#define Username "Device9025&k02vhQrIfuK"

#define Topic_Pub "/sys/k02vhQrIfuK/Device9025/thing/event/property/post" 

uint8_t LEDSwitch=0;

//建立mqtt的连接
void Mqtt_Cloud_Connect(void)
{
	int len = 0;
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	data.clientID.cstring = ClientID;
	data.keepAliveInterval = 60;
	data.cleansession = 1;
	data.username.cstring = Username;
	data.password.cstring = Passwd;
	//参数1：打包后的数据存放的地址空间
	//参数2：这个地址空间的大小
	//参数3：待打包的数据结构
	//为了防止打包过程中，存放数据的空间不够，所以要提前告诉函数数组缓冲区的长度
	//返回值：打包后的有效数据长度
	//我们把串口3的发送缓冲区给该函数
	len = MQTTSerialize_connect(wifi_message.send_buff, ESP_S_LENGTH, &data);
	memset(wifi_message.rcv_buff,0,ESP_R_LENGTH);
	wifi_message.rcv_count = 0;
	USART1_SendBuff(wifi_message.send_buff,len);
	WIFI_SendCmd(wifi_message.send_buff,len);
	vTaskDelay(5000);
	if(wifi_message.rcv_buff[0]==0x20 && wifi_message.rcv_buff[1]==0x02 && wifi_message.rcv_buff[2]==0x00 && wifi_message.rcv_buff[3]==0x00)
	{
		Net_State = 2;
	}
}

//上传云平台的消息
void Mqtt_Cloud_Publish(void)
{
	int len = 0;
	char payload[1024];
	uint16_t payloadlen;
	MQTTString topicString = MQTTString_initializer;
	topicString.cstring = Topic_Pub;	                                //订阅的报文
	sprintf(payload,"{\"id\":1691569773121,\"params\":{\"temperature\":%.1f,\"Humidity\":%d,\"LEDSwitch\":%d,\"co2\":%d,\"TVOC\":%0.2f,\"HCHO\":%0.2f,\"LightLux\":%d,\"SmokeSensorState\":%d,\"chip\":%.1f},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}",dht11.t,dht11.h,LED_Status,KQM.co2,KQM.voc,KQM.hcho,KQM.Lightintensity,KQM.fumes,KQM.chip);
	payloadlen = strlen(payload);
	//参数1  打包待发送数据的数组
	//参数2  数组的最长长度，避免打包越界
	//参数3  dup value  从mqtt协议 3.3.1固定报头中描述的
	//参数4  qos value  从mqtt协议 3.3.1固定报头中描述的
	//参数5  retained flag 从mqtt协议 3.3.1固定报头中描述的
	//参数4 packetid这个是用来进行一个简单的识别的，如果Qos等级为0的话，没有这个字段，当Qos等级大于0时，接收此条消息的服务端和客户端需要回发应答，为了对应每一条应答报文和PUBLISH报文就需要设置这个字段，保证应答报文和PUBLISH对应上。以下面两张图为例，对于某一条Qos等级大于0的报文，会有一个相应的应答，packetid就是用来区分接到的应答是否时应答对应PUBLISH报文的一个标识。
	//参数5 topic
	//参数6 有效载荷的首地址
	//参数7 有效载荷的长度	
	len = MQTTSerialize_publish(wifi_message.send_buff, ESP_S_LENGTH, 0, 0, 0, 0, topicString, (unsigned char*)payload, payloadlen);
	memset(wifi_message.rcv_buff,0,ESP_R_LENGTH);
	wifi_message.rcv_count = 0;
	USART1_SendBuff(wifi_message.send_buff,len);
	WIFI_SendCmd(wifi_message.send_buff,len);
}


//订阅消息
void Mqtt_Subscribe_Ali(void)
{
	int msgid = 1;	
	int req_qos = 0;	
	uint16_t Send_len=0;      //打包之后待发送的长度	
	MQTTString topicString = MQTTString_initializer;	
	/* subscribe */
	topicString.cstring = Subscribe_Topic;	                        //平台下发消息所需要订阅的主题
	Send_len = MQTTSerialize_subscribe(wifi_message.send_buff,wifi_message.rcv_buff, 0, msgid, 1, &topicString, &req_qos);
	memset(wifi_message.rcv_buff,0,sizeof(wifi_message.rcv_buff));  //清空接收缓冲区
	wifi_message.rcv_count=0;                                       //清空接收的数组的标签  让它从头接收
	USART1_SendBuff(wifi_message.send_buff,Send_len);               //调试用
	USART3_Send(wifi_message.send_buff,Send_len);                   //通过串口3(ESP8266)将数据发送出去
	printf("client subscribe:[%s]\r\n",topicString.cstring);		
}

//心跳上行
void Mqtt_Heart_Send(void)
{
	uint16_t Send_len=0;      //打包之后待发送的长度		
	Send_len = MQTTSerialize_pingreq((unsigned char*)wifi_message.send_buff, ESP_R_LENGTH);							//心跳包数据进行打包      
	memset(wifi_message.rcv_buff,0,sizeof(wifi_message.rcv_buff));   //清空接收缓冲区
	wifi_message.rcv_count=0;   //清空接收的数组的标签  让它从头接收,和上一句话要成对使用
	USART1_SendBuff(wifi_message.send_buff,Send_len);  //调试用
	USART3_Send(wifi_message.send_buff,Send_len);  //通过串口3(ESP8266)将数据发送出去	
}


//计算长度  由于收到的报文是变长度，因此我们计算剩余长度具体是多少
//返回值 0 计算失败   
//buff 长度在数组中的首地址
//len 用于存储长度共多少个字节的指针
uint32_t MQTT_LengthCalculation(uint8_t *buff, uint8_t *len)
{
	uint32_t multiplier = 1;
	uint32_t value = 0;
	uint8_t encodedByte = 0;
	uint32_t i = 0;
	do{
		encodedByte = buff[i];
		value += (encodedByte & 127) * multiplier;
		multiplier *= 128;
		if (multiplier > (128*128*128)){
			return 0;//err
		}
		i++;
	}while((encodedByte&128) != 0);
	*len = i;
	return value;
}


//使用cJSON解析数据，可以获取每个下发控制内容，解析后进行处理，并上报新的数据即可
//比如收到的下行控制如下，我们就这样解析
//{"method":"thing.service.property.set","id":"1545661297","params":{"LEDSwitch":0},"version":"1.0.0"}
//用json解析  startup_stm32f10x_hd.s启动文件中，堆栈空间需要改  
//Stack_Size      EQU     0x00002000
//Heap_Size       EQU     0x00001000
void Ali_AlsDataAck(char *payload)
{
	//cJson解析需要的变量
	cJSON* cjson_root = NULL;       //根节点
	cJSON* cjson_params = NULL;     //参数节点
	cJSON* cjson_LEDSwitch = NULL;
	
	char payLoad[512] = {0};//回应的负载数据

	cjson_root = cJSON_Parse(payload);
	if(cjson_root != NULL) {
		cjson_params = cJSON_GetObjectItem(cjson_root, "params");
		if(cjson_params != NULL) {
			cjson_LEDSwitch = cJSON_GetObjectItem(cjson_params, "LEDSwitch");
			if(cjson_LEDSwitch != NULL) {
				printf("LEDSwitch:%d\r\n", cjson_LEDSwitch->valueint);
			}
			sprintf(payLoad, "{\"id\":\"123\",\
					\"method\":\"thing.event.property.post\",\
					\"params\":{\
					\"LEDSwitch\":%d,\
					},\"version\":\"1.0\"}", cjson_LEDSwitch->valueint);
			LEDSwitch=cjson_LEDSwitch->valueint;  //保存的数值
			Mqtt_Cloud_Publish();     //响应状态
			
			if(cjson_LEDSwitch->valueint == 1) {
				LED1_ON;RGBR_ON;
			}
			else {
				LED1_OFF;RGBR_OFF;
			}
		}
	}
	cJSON_Delete(cjson_root);    //释放内存（保持存活）
}