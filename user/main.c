#include "main.h"

TaskHandle_t  xLvglTaskHandle = NULL;      //����LVGL������
TaskHandle_t  LED1_TASK_Handle=NULL;       //����LED1�ľ��  ���������ɾ������͹���������Ҫ�õ�
TaskHandle_t  KEY_TASK_Handle=NULL;        //����KEY�ľ��
TaskHandle_t  KQM6600_TASK_Handle=NULL;    //KQM6600��������
TaskHandle_t  SU_03T_TASK_Handle=NULL;     //DHT11��������
TaskHandle_t  Sensor_TASK_Handle=NULL;     //DHT11��������
TaskHandle_t  Cloud_TASK_Handle=NULL;      //Cloud��������
static TimerHandle_t Swtmr_1s_Handle =NULL; /* �����ʱ����� */

/* ����Ϊ�ź�������Ҫ�� */
SemaphoreHandle_t BinarySem_Handle = NULL;     //������ֵ�ź������

/* ����Ϊ�¼�����Ҫ�� */
static EventGroupHandle_t Event_Handle = NULL; //�¼��ľ��
static TaskHandle_t LED4_Task_Handle = NULL;   //led4�ľ��
static TaskHandle_t KEY4_Task_Handle = NULL;   //KEY4�ľ��
//�궨��
#define KEY3_EVENT (0x01 << 0)                 //�����¼������λ 0
#define KEY4_EVENT (0x01 << 1)                 //�����¼������λ 1 
void LED4_Task(void* parameter);

void vLvglTaskFunction( void * pvParameters );
void LED1_Task(void* parameter);
void LED2_Task(void* parameter);
void KEY_Task(void* parameter);
void Sensor_Task(void* parameter);
void KQM6600_Task(void* parameter);
void Cloud_Task(void* parameter);
void SU_03T_TASK(void* parameter);
void Swtmr_1s_Callback(void* parameter);


uint16_t Time_Period[2]={0,10000};  //0Ϊ����ֵ��10000Ϊ����ֵ

//�������ܳ�ʼ��
void STM32_Init(void)
{

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ռ��2λ0~3   �μ�2λ0~3
	LED_configlib();        //LED��ʼ��
	RGB_configlib();        //RGB��ʼ��
//	BEEP_configlib();       //��������ʼ��
	KEY_configlib();        //������ʼ��
	USART1_Config(115200);  //����1��ʼ��
	UART4_Config(9600);     //����4��ʼ����su_03t��
	ADC1_Config();          //adc��ʼ��
	ADC1_DMAConfig();       //ADC��ʼ��
//	EXTI0_Config();
//	EXTI4_Config();
//	Delay_config();         //�ӳٶ��壨�δ�ʱ����
//	TIM3_Config();          //��ʱ��3�ĳ�ʼ��(PWM�����ƹ���)
	RTC_Config();             //RTCʱ�ӳ�ʼ��
	TIM6_Config();            //��ʱ��6�ĳ�ʼ�������Ʒ�������ת��
	SPI2_Config();            //SPI2��ʼ��
	sFLASH_ReadBuffer((uint8_t *)&wifi, FLASH_WriteAddress, sizeof(wifi));  //��flash��ȡ�����������wifi����
	Flash_Test();            //��flash�����ȡ��ӡ--����
	WIFI_Config();          //wifi��ʼ��
	USART1_SendStr((u8 *)"��ԥ�ͻ�ܱ�\r\n");
	printf("���Ͼͻ�׸�\r\n");
		lv_init();
	lv_port_disp_init(); //�����˺����Ľӿں���

}

int main()
{
	STM32_Init();
	BaseType_t xReturn;                                    //��������ķ���ֵ
	
	BinarySem_Handle=xSemaphoreCreateBinary();             //������ֵ�ź���
	if(BinarySem_Handle!=NULL)
		printf("��ֵ�ź��������ɹ�\r\n");
	xSemaphoreGive( BinarySem_Handle );                    //������ֵ�ź���
	Event_Handle = xEventGroupCreate();                    //���� Event_Handle
	if (NULL != Event_Handle)
		printf("Event_Handle �¼������ɹ�!\r\n"); 
	Swtmr_1s_Handle=xTimerCreate((const char*)"AutoReloadTimer",(TickType_t)1000,(UBaseType_t)pdTRUE,(void*)1,(TimerCallbackFunction_t)Swtmr_1s_Callback);	
	if(Swtmr_1s_Handle!=NULL)
		printf("����1S�������ʱ���ɹ�");
	
	xReturn=xTaskCreate((TaskFunction_t)LED1_Task,(const char *)"LED1_Task",128,NULL,1,(TaskHandle_t *)&LED1_TASK_Handle);
	if(xReturn == pdPASS)
		printf("LED1_Task�����ɹ�\r\n");
	xReturn=xTaskCreate((TaskFunction_t)LED4_Task,(const char *)"LED4_Task",128,NULL,1,(TaskHandle_t *)&LED4_Task_Handle);
	if(xReturn == pdPASS)
		printf("LED4_Task�����ɹ�\r\n");
	xReturn=xTaskCreate((TaskFunction_t)KEY_Task,(const char *)"KEY_Task",128,NULL,5,(TaskHandle_t*)&KEY_TASK_Handle);    
	if(xReturn==pdPASS)
		printf("KEY_Task���񴴽��ɹ�\r\n");	
	xReturn=xTaskCreate((TaskFunction_t)KQM6600_Task, (const char *)"KQM6600_Task",256,NULL,2,(TaskHandle_t*)&KQM6600_TASK_Handle);            
	if(xReturn==pdPASS)
		printf("KQM6600_Task���񴴽��ɹ�\r\n");	
	xReturn=xTaskCreate((TaskFunction_t)Sensor_Task, (const char *)"Sensor_Task",256,NULL,2,(TaskHandle_t*)&Sensor_TASK_Handle);            
	if(xReturn==pdPASS)
		printf("Sensor_Task���񴴽��ɹ�\r\n");	
	xReturn=xTaskCreate((TaskFunction_t)Cloud_Task, (const char *)"Cloud_Task",1024,NULL,6,(TaskHandle_t*)&Cloud_TASK_Handle);            
	if(xReturn==pdPASS)
		printf("Cloud_Task�������񴴽��ɹ�\r\n");	
	xReturn = xTaskCreate((TaskFunction_t)vLvglTaskFunction, "lvgl_task", 512, NULL, 7, (TaskHandle_t*)&xLvglTaskHandle);
	if(xReturn==pdPASS)
		printf("lvgl_task���񴴽��ɹ�\r\n");
	xReturn = xTaskCreate((TaskFunction_t)SU_03T_TASK, (const char *)"SU_03T_TASK", 128, NULL, 3, (TaskHandle_t*)&SU_03T_TASK_Handle);
	if(xReturn==pdPASS)
		printf("SU_03T_TASK���񴴽��ɹ�\r\n");
	
	vTaskStartScheduler();           // �������񣬿������� 			
	while(1)
	{
		printf("��������ѭ��\r\n");    //���˲���ϵͳ���ⲿ�ִ���ִ�в���
	}
}

//����ջ������Ĺ��Ӻ���   �����ڴ�
void vApplicationStackOverflowHook (void)
{
	while(1)
	{}
}

void vApplicationMallocFailedHook(void)
{
	printf("Malloc Failed\r\n");
	while(1)
	{}
}

void vApplicationTickHook(void)
{
	//�ӿڵ�����12  ���Ը�֪ lvgl ������ʱ��   
	//�����ʱ����仰�ܷŶϵ㣬1MS��һ��   ������벻����������ǹ��Ӻ���û��ʹ��
	//#define configUSE_TICK_HOOK 1 //�� 1��ʹ��ʱ��Ƭ���ӣ�Tick Hook������ 0������ʱ��Ƭ����
	//���ж���ÿ�� x���� ���� lv_tick_inc(x) ���Ը�֪ lvgl ������ʱ�䣻�������ʹ�õ������������
	//��ôֱ�ӽ���������ŵ�Ӳ����ʱ����1ms�жϷ������ڣ��������ʹ�õ��ǲ���ϵͳ����ô���ǿ��Էŵ�ϵͳ�������ĵĹ��Ӻ����ڡ�	
	lv_tick_inc(1);
	timeDHT11[0]++;
	Time_Period[0]++;
}

//LED1����ľ�������   ÿһ��������while(1)
void LED1_Task(void* parameter)
{
	printf("LED1_Task��ʼ����\r\n");
	while(1)
	{
		//LED1_Toggle;
	if(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_2) == 0)
	{
		LED_Status = 1;
	}
	else
	{
		LED_Status = 0;
	}
		LED2_Toggle;
		vTaskDelay(500);   //ϵͳ������ӳٺ��� 500ms���ӳ�
//  	Delay_nopms(500);    //�����ʱ��������Ȼռ��CPU
	}
}

//LED4����ľ�������
void LED4_Task(void* parameter)
{
	EventBits_t r_event; /* ����һ���¼����ձ��� */
	while(1)
	{
		r_event = xEventGroupWaitBits(Event_Handle,   /* �¼������� */
												 KEY3_EVENT|KEY4_EVENT,   /* �����������Ȥ���¼� */
										                    pdTRUE,   /* �˳�ʱ����¼�λ */
									                    	pdTRUE,   /* �������Ȥ�������¼� */
							                  portMAX_DELAY);   /* ָ����ʱ�¼�,һֱ�� */
		if ((r_event & (KEY3_EVENT|KEY4_EVENT)) == (KEY3_EVENT|KEY4_EVENT)) {
			/* ���������ɲ�����ȷ */
			printf ( "KEY1 �� KEY2 ������\n");
			LED4_Toggle; //LED1 ��ת
		} else{
			printf ( "�¼����� \n");
			}
	}
}
//KEY����ľ�������  ÿ����������ѭ��
void KEY_Task(void* parameter)
{
	u8 key = 0;	
	while(1)
	{
		key=Key_GetValue();
		switch(key)
		{
			case 0:   //û�а�������
				break;
			case 1: 
						
				for(int i = 0; i < 100 ;i++)
				{
					lv_scr_load(guider_ui.screen);     //������Ļ
					lv_bar_set_value(guider_ui.screen_bar_1,i,LV_ANIM_OFF);
					vTaskDelay(30);
				}

				break;
			case 2:   //����2����
				GPIO_ResetBits(GPIOE,GPIO_Pin_6);//����
				Delay_nopms(500);
				GPIO_SetBits(GPIOE,GPIO_Pin_6);//����
				Net_State = 4;
			  Net_Step = 0;
				break;
			case 3:   //����3����
				printf ( "����3���£� \n");
				lv_scr_load(guider_ui.screen);
				xEventGroupSetBits(Event_Handle,KEY3_EVENT);
				break;	
			case 4:   //����4����
				printf ( "����4���£� \n");
				lv_scr_load(guider_ui.screen_1);
				xEventGroupSetBits(Event_Handle,KEY4_EVENT);
				break;				
			default:
				break;
		}
		vTaskDelay(10);       //ϵͳ�������ʱ����  10ms����ʱ 	
	}
}


//��ֵ�ź�����Ӧ��
void KQM6600_Task(void* parameter)
{
	USART2_Config(9600);    //����2��ʼ����KQM6600��
	while(1)
	{
		//����1   �ȴ����ź������
		//����2   �ȴ�ʱ��     0(����)    �̶�����(�ȹ̶�����)   portMAX_DELAY(����)
		//�ȵ��ź�����������ִ�У��Ȳ����źţ�����������
		xSemaphoreTake( BinarySem_Handle, portMAX_DELAY );  //�ȴ��ź����ĵ���
		KQM6600_DataAnalysis();
//		taskENTER_CRITICAL();            //�����ٽ���  
//		printf("VOC = %.1fppm\r\n",KQM.voc);
//		printf("��ȩ = %.2fmg/m3\r\n",KQM.hcho);
//		printf("CO2 = %uppm\r\n",KQM.co2);
//		taskEXIT_CRITICAL();             //�˳��ٽ���
		vTaskDelay(1000);                //ϵͳ�������ʱ����  1000ms����ʱ 
	}
}

//�������ɼ�����
void Sensor_Task(void* parameter)
{
	vTaskDelay(1000);
	while(1)
	{
		taskENTER_CRITICAL();                 //�����ٽ��� 
		ADC_value();                          //���ա�����
		DHT11_Display();                      //DHT11��ʱ���ȡ,һ��Ҫ�ŵ��ٽ�����,�����յ������ݻ����
		taskEXIT_CRITICAL();                  //�˳��ٽ���
		vTaskDelay(1000);                     //ϵͳ�������ʱ���� 

	}
}

//SU_03T������
void SU_03T_TASK(void* parameter)
{
	while(1)
	{
		SU03_DataAnalysis();
		SU03_Send();
		vTaskDelay(10); 
	}
}

//����������
void Cloud_Task(void* parameter)
{
	uint32_t dataLen = 0;           //�ɱ䱨ͷ����Ч�غɵĳ���
	uint8_t lenlen = 0;             //��Ǽ����ֽڱ�ʾ����
	uint16_t topicLen = 0;          //���topic�ĳ���
	char *payload = NULL;           //���payload��ʼ����ʼ��ַ
	char topic[256] = {0};
	while(1)
	{
		if(Net_State == 0)          //û����������
		{
			Net_Connect();
		} 
		else if(Net_State == 1)        //�������������ӣ�û��mqtt����
		{
			if(WIFI_Flag == 1)           //��ȡ����ʱ��
			{
				WIFI_Time();
			}
			else{
				Mqtt_Cloud_Connect();		   //����mqtt����
			}
		}
		if(Time_Period[0]>Time_Period[1])    //ʱ��Ƭÿʮ�����һ��
		{
			Time_Period[0]=0;
			if(Net_State == 2)                 //������ƽ̨(����ͨ���Ѿ�����)���ѷ������ӱ���δ���Ͷ��ı��� 
			{
				Mqtt_Subscribe_Ali();            //���ı���
				wifi_message.rcv_flag = 0; 
				Net_State = 3;
			}
			else if(Net_State==3)              //������ƽ̨(����ͨ���Ѿ�����)���ѷ������ӱ��ģ��ѷ��Ͷ��ı��ģ����ڷ�����Ϣ
			{
				Mqtt_Cloud_Publish();            //�ϱ���ƽ̨
				vTaskDelay(50);		
				Mqtt_Heart_Send();               //����
			}
		}
		if(Net_State==3)                     //ƽ̨�·�������   ����
		{
			wifi_message.rcv_flag = 0;	
			switch(wifi_message.rcv_buff[0])   //��ͷ
			{
				case 0x90:   //���ĵĻظ�
					printf("�յ����Ļظ�\r\n");
					break;
				case 0x30:   //ƽ̨��������Ϣ
					printf("ƽ̨������Ϣ\r\n");		
					//��ʣ�೤��				lenlen��ʣ�೤�ȵĳ���		
					dataLen =  MQTT_LengthCalculation(&wifi_message.rcv_buff[1], &lenlen);            //����ɱ䱨ͷ+��Ч�غɳ���
					topicLen = wifi_message.rcv_buff[1+lenlen]<<8|wifi_message.rcv_buff[1+lenlen+1];  //����topic����
					memcpy(topic,&wifi_message.rcv_buff[1+lenlen+2],topicLen);                        //һ���ڴ��е����ݸ��Ƶ���һ���ڴ���
					printf("�յ��·��������ݣ�\r\n�������ͣ�0x%02X, \r\nʣ�೤��%d�ֽ�, ʣ�೤�ȣ�%d, \r\ntopic���ȣ�%d\r\n",
																				wifi_message.rcv_buff[0], lenlen, dataLen, topicLen);
					printf("topic:%s\r\n", topic);
					if(strcmp(Subscribe_Topic, topic) == 0) {   //�Ա���������յ������е�����
						printf("�յ��������ñ���,��ʼ����\r\n");
						payload = strstr((char*)&wifi_message.rcv_buff[1+lenlen+1+1], "{");//��topic��ʼ���Ҹ��� ��Ϊǰ�������ݿ�����0����ʾ�ַ�����β
						printf("payload��%s\r\n", payload);
						Ali_AlsDataAck(payload);
					}				
					else if(strcmp(Publish_Topic_Reply, topic) == 0) {  //ƽ̨�յ���Ϣ���ظ�һ����Ϣ
						printf("�յ�����Ӧ����\r\n");						
					}
					memset(topic,0,sizeof(topic));
					break;
				case 0xD0:   //������Ӧ��
					printf("�����ظ�\r\n");					
					break;				
			}
			memset(wifi_message.rcv_buff,0,sizeof(wifi_message.rcv_buff));  //��ս��ջ�����
			wifi_message.rcv_count = 0;	;  //��ս��յ�����ı�ǩ  ������ͷ����	
		}
		if(Net_State==4)                //��������WIFI�˺ź�����
		{
			WIFI_Revise_AP_Net();
		}
		vTaskDelay(10); 		
	}
}

//��Ļ������
void vLvglTaskFunction( void * pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS( 5 );
	xLastWakeTime = xTaskGetTickCount(); 
	setup_scr_screen(&guider_ui);      //��Ļscreen���ݵĳ�ʼ��    ������
	setup_scr_screen_1(&guider_ui);    //��Ļscreen_1���ݵĳ�ʼ��  ������

	vTaskDelay(200);
	lv_scr_load(guider_ui.screen_1);
	xTimerStart(Swtmr_1s_Handle,0); //�������ڶ�ʱ��1
	for(;;)
	{		
		//�ӿڵ�����13         ÿ��x���붨�ڵ��� ltask_handler()
		lv_task_handler();   //ÿ�� x���� ���ڵ��� lv_task_handler()  ���Դ����� lvgl ��ص�����  
		vTaskDelayUntil( &xLastWakeTime, xPeriod );    //������ʱ
	}
}

char Lvgl_T[10];
void Swtmr_1s_Callback(void* parameter)
{
	RTC_GetTime();
//	void lv_label_set_text_fmt(lv_obj_t * label, const char * fmt, ...);
	memset(Lvgl_T,0,sizeof(Lvgl_T));
	sprintf (Lvgl_T,"%.1f",dht11.t);
	lv_label_set_text_fmt(guider_ui.screen_1_label_18,"%s",Lvgl_T);              //��Ļ��ӡ�¶�
	lv_label_set_text_fmt(guider_ui.screen_1_label_16,"%d",dht11.h);             //��Ļ��ӡʪ��
	lv_label_set_text_fmt(guider_ui.screen_1_label_19,"%d",KQM.co2);             //��Ļ��ӡ������̼
	lv_label_set_text_fmt(guider_ui.screen_1_label_24,"%d",ADC_DMAGetValue[0]);  //��Ļ��ӡ����
	memset(Lvgl_T,0,sizeof(Lvgl_T));
	sprintf (Lvgl_T,"%.2f",KQM.hcho);
	lv_label_set_text_fmt(guider_ui.screen_1_label_21,"%s",Lvgl_T);              //��Ļ��ӡ��ȩ

//	lv_label_set_text(guider_ui.screen_1_label_1, "�¶�:27�� ");
//	Time_Cnt=RTC_GetCounter();  //����RTC�ļ�������ֵ
//	Now_time=localtime((const time_t *)&Time_Cnt);  //������ת����ʱ��Ľṹ��
//��һ��ʱ����·�ʽ  �ùٷ��ṩ�ĸ�ʽ��������� lv_label_set_text_fmt
//	lv_label_set_text_fmt(guider_ui.screen_label_2,"%2d:%2d:%2d",Now_time->tm_hour,Now_time->tm_min,Now_time->tm_sec);
//�ڶ���ʱ����·�ʽ  �Լ���ʽ�����
//	sprintf((char *)Buf_Temp,"%2d:%2d:%2d",Now_time->tm_hour,Now_time->tm_min,Now_time->tm_sec);
//	lv_label_set_text(guider_ui.screen_label_2, (char *)Buf_Temp);
//	printf("%d��%d��%d�� %d:%d:%d\r\n",Now_time->tm_year+1900,Now_time->tm_mon+1,Now_time->tm_mday,Now_time->tm_hour,Now_time->tm_min,Now_time->tm_sec);					
}

//���й��Ӻ�����Idle Hook����

//���ã���ϵͳ���ڿ���״̬����û��������Ҫ���У�ʱ���ã���������ִ��һЩ�����ȼ�����������ϵͳ����ͳ�ơ�

//��������Ӻ�����Heap Overflow Hook����

//���ã�����������ʱ������ڴ�ʧ�ܣ��������ʱ���ã��������ڲ�ȡ�ʵ��Ĵ�ʩ��������ϵͳ����ӡ������Ϣ�ȡ�

//���񴴽����Ӻ�����Task Create Hook����

//���ã������񱻴���ʱ���ã���������ִ���ض��ĳ�ʼ���������������Դ�������������ȼ��ȡ�

//����ɾ�����Ӻ�����Task Delete Hook����

//���ã�������ɾ��ǰ���ã���������ִ��һЩ������������ͷ���Դ������״̬�ȡ�

//�����л����Ӻ�����Task Switch Hook����

//���ã��������л�ʱ���ã���������ִ��һЩ�ض��Ĳ��������¼�����л�������������������ʱ��ȡ�

//�ӳٹ��Ӻ�����Tick Hook����

//���ã���ϵͳ�δ�ʱ���ж��е��ã���������ִ��һЩ�����Ե����������ϵͳʱ�ӡ������������¼��ȡ�