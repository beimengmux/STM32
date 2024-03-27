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

//����mqtt������
void Mqtt_Cloud_Connect(void)
{
	int len = 0;
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	data.clientID.cstring = ClientID;
	data.keepAliveInterval = 60;
	data.cleansession = 1;
	data.username.cstring = Username;
	data.password.cstring = Passwd;
	//����1�����������ݴ�ŵĵ�ַ�ռ�
	//����2�������ַ�ռ�Ĵ�С
	//����3������������ݽṹ
	//Ϊ�˷�ֹ��������У�������ݵĿռ䲻��������Ҫ��ǰ���ߺ������黺�����ĳ���
	//����ֵ����������Ч���ݳ���
	//���ǰѴ���3�ķ��ͻ��������ú���
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

//�ϴ���ƽ̨����Ϣ
void Mqtt_Cloud_Publish(void)
{
	int len = 0;
	char payload[1024];
	uint16_t payloadlen;
	MQTTString topicString = MQTTString_initializer;
	topicString.cstring = Topic_Pub;	                                //���ĵı���
	sprintf(payload,"{\"id\":1691569773121,\"params\":{\"temperature\":%.1f,\"Humidity\":%d,\"LEDSwitch\":%d,\"co2\":%d,\"TVOC\":%0.2f,\"HCHO\":%0.2f,\"LightLux\":%d,\"SmokeSensorState\":%d,\"chip\":%.1f},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}",dht11.t,dht11.h,LED_Status,KQM.co2,KQM.voc,KQM.hcho,KQM.Lightintensity,KQM.fumes,KQM.chip);
	payloadlen = strlen(payload);
	//����1  ������������ݵ�����
	//����2  ���������ȣ�������Խ��
	//����3  dup value  ��mqttЭ�� 3.3.1�̶���ͷ��������
	//����4  qos value  ��mqttЭ�� 3.3.1�̶���ͷ��������
	//����5  retained flag ��mqttЭ�� 3.3.1�̶���ͷ��������
	//����4 packetid�������������һ���򵥵�ʶ��ģ����Qos�ȼ�Ϊ0�Ļ���û������ֶΣ���Qos�ȼ�����0ʱ�����մ�����Ϣ�ķ���˺Ϳͻ�����Ҫ�ط�Ӧ��Ϊ�˶�Ӧÿһ��Ӧ���ĺ�PUBLISH���ľ���Ҫ��������ֶΣ���֤Ӧ���ĺ�PUBLISH��Ӧ�ϡ�����������ͼΪ��������ĳһ��Qos�ȼ�����0�ı��ģ�����һ����Ӧ��Ӧ��packetid�����������ֽӵ���Ӧ���Ƿ�ʱӦ���ӦPUBLISH���ĵ�һ����ʶ��
	//����5 topic
	//����6 ��Ч�غɵ��׵�ַ
	//����7 ��Ч�غɵĳ���	
	len = MQTTSerialize_publish(wifi_message.send_buff, ESP_S_LENGTH, 0, 0, 0, 0, topicString, (unsigned char*)payload, payloadlen);
	memset(wifi_message.rcv_buff,0,ESP_R_LENGTH);
	wifi_message.rcv_count = 0;
	USART1_SendBuff(wifi_message.send_buff,len);
	WIFI_SendCmd(wifi_message.send_buff,len);
}


//������Ϣ
void Mqtt_Subscribe_Ali(void)
{
	int msgid = 1;	
	int req_qos = 0;	
	uint16_t Send_len=0;      //���֮������͵ĳ���	
	MQTTString topicString = MQTTString_initializer;	
	/* subscribe */
	topicString.cstring = Subscribe_Topic;	                        //ƽ̨�·���Ϣ����Ҫ���ĵ�����
	Send_len = MQTTSerialize_subscribe(wifi_message.send_buff,wifi_message.rcv_buff, 0, msgid, 1, &topicString, &req_qos);
	memset(wifi_message.rcv_buff,0,sizeof(wifi_message.rcv_buff));  //��ս��ջ�����
	wifi_message.rcv_count=0;                                       //��ս��յ�����ı�ǩ  ������ͷ����
	USART1_SendBuff(wifi_message.send_buff,Send_len);               //������
	USART3_Send(wifi_message.send_buff,Send_len);                   //ͨ������3(ESP8266)�����ݷ��ͳ�ȥ
	printf("client subscribe:[%s]\r\n",topicString.cstring);		
}

//��������
void Mqtt_Heart_Send(void)
{
	uint16_t Send_len=0;      //���֮������͵ĳ���		
	Send_len = MQTTSerialize_pingreq((unsigned char*)wifi_message.send_buff, ESP_R_LENGTH);							//���������ݽ��д��      
	memset(wifi_message.rcv_buff,0,sizeof(wifi_message.rcv_buff));   //��ս��ջ�����
	wifi_message.rcv_count=0;   //��ս��յ�����ı�ǩ  ������ͷ����,����һ�仰Ҫ�ɶ�ʹ��
	USART1_SendBuff(wifi_message.send_buff,Send_len);  //������
	USART3_Send(wifi_message.send_buff,Send_len);  //ͨ������3(ESP8266)�����ݷ��ͳ�ȥ	
}


//���㳤��  �����յ��ı����Ǳ䳤�ȣ�������Ǽ���ʣ�೤�Ⱦ����Ƕ���
//����ֵ 0 ����ʧ��   
//buff �����������е��׵�ַ
//len ���ڴ洢���ȹ����ٸ��ֽڵ�ָ��
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


//ʹ��cJSON�������ݣ����Ի�ȡÿ���·��������ݣ���������д������ϱ��µ����ݼ���
//�����յ������п������£����Ǿ���������
//{"method":"thing.service.property.set","id":"1545661297","params":{"LEDSwitch":0},"version":"1.0.0"}
//��json����  startup_stm32f10x_hd.s�����ļ��У���ջ�ռ���Ҫ��  
//Stack_Size      EQU     0x00002000
//Heap_Size       EQU     0x00001000
void Ali_AlsDataAck(char *payload)
{
	//cJson������Ҫ�ı���
	cJSON* cjson_root = NULL;       //���ڵ�
	cJSON* cjson_params = NULL;     //�����ڵ�
	cJSON* cjson_LEDSwitch = NULL;
	
	char payLoad[512] = {0};//��Ӧ�ĸ�������

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
			LEDSwitch=cjson_LEDSwitch->valueint;  //�������ֵ
			Mqtt_Cloud_Publish();     //��Ӧ״̬
			
			if(cjson_LEDSwitch->valueint == 1) {
				LED1_ON;RGBR_ON;
			}
			else {
				LED1_OFF;RGBR_OFF;
			}
		}
	}
	cJSON_Delete(cjson_root);    //�ͷ��ڴ棨���ִ�
}