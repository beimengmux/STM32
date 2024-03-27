#include "main.h"

TaskHandle_t  xLvglTaskHandle = NULL;      //创建LVGL任务句柄
TaskHandle_t  LED1_TASK_Handle=NULL;       //任务LED1的句柄  创建任务和删除任务和挂起任务需要用到
TaskHandle_t  KEY_TASK_Handle=NULL;        //任务KEY的句柄
TaskHandle_t  KQM6600_TASK_Handle=NULL;    //KQM6600的任务句柄
TaskHandle_t  SU_03T_TASK_Handle=NULL;     //DHT11的任务句柄
TaskHandle_t  Sensor_TASK_Handle=NULL;     //DHT11的任务句柄
TaskHandle_t  Cloud_TASK_Handle=NULL;      //Cloud的任务句柄
static TimerHandle_t Swtmr_1s_Handle =NULL; /* 软件定时器句柄 */

/* 以下为信号量所需要的 */
SemaphoreHandle_t BinarySem_Handle = NULL;     //创建二值信号量句柄

/* 以下为事件所需要的 */
static EventGroupHandle_t Event_Handle = NULL; //事件的句柄
static TaskHandle_t LED4_Task_Handle = NULL;   //led4的句柄
static TaskHandle_t KEY4_Task_Handle = NULL;   //KEY4的句柄
//宏定义
#define KEY3_EVENT (0x01 << 0)                 //设置事件掩码的位 0
#define KEY4_EVENT (0x01 << 1)                 //设置事件掩码的位 1 
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


uint16_t Time_Period[2]={0,10000};  //0为计数值，10000为周期值

//各个功能初始化
void STM32_Init(void)
{

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//占先2位0~3   次级2位0~3
	LED_configlib();        //LED初始化
	RGB_configlib();        //RGB初始化
//	BEEP_configlib();       //蜂鸣器初始化
	KEY_configlib();        //按键初始化
	USART1_Config(115200);  //串口1初始化
	UART4_Config(9600);     //串口4初始化（su_03t）
	ADC1_Config();          //adc初始化
	ADC1_DMAConfig();       //ADC初始化
//	EXTI0_Config();
//	EXTI4_Config();
//	Delay_config();         //延迟定义（滴答定时器）
//	TIM3_Config();          //定时器3的初始化(PWM呼吸灯功能)
	RTC_Config();             //RTC时钟初始化
	TIM6_Config();            //定时器6的初始化（控制蜂鸣器反转）
	SPI2_Config();            //SPI2初始化
	sFLASH_ReadBuffer((uint8_t *)&wifi, FLASH_WriteAddress, sizeof(wifi));  //从flash读取保存在里面的wifi数据
	Flash_Test();            //从flash里面读取打印--测试
	WIFI_Config();          //wifi初始化
	USART1_SendStr((u8 *)"犹豫就会败北\r\n");
	printf("果断就会白给\r\n");
		lv_init();
	lv_port_disp_init(); //调用了函数的接口函数

}

int main()
{
	STM32_Init();
	BaseType_t xReturn;                                    //创建任务的返回值
	
	BinarySem_Handle=xSemaphoreCreateBinary();             //创建二值信号量
	if(BinarySem_Handle!=NULL)
		printf("二值信号量创建成功\r\n");
	xSemaphoreGive( BinarySem_Handle );                    //给出二值信号量
	Event_Handle = xEventGroupCreate();                    //创建 Event_Handle
	if (NULL != Event_Handle)
		printf("Event_Handle 事件创建成功!\r\n"); 
	Swtmr_1s_Handle=xTimerCreate((const char*)"AutoReloadTimer",(TickType_t)1000,(UBaseType_t)pdTRUE,(void*)1,(TimerCallbackFunction_t)Swtmr_1s_Callback);	
	if(Swtmr_1s_Handle!=NULL)
		printf("创建1S的软件定时器成功");
	
	xReturn=xTaskCreate((TaskFunction_t)LED1_Task,(const char *)"LED1_Task",128,NULL,1,(TaskHandle_t *)&LED1_TASK_Handle);
	if(xReturn == pdPASS)
		printf("LED1_Task创建成功\r\n");
	xReturn=xTaskCreate((TaskFunction_t)LED4_Task,(const char *)"LED4_Task",128,NULL,1,(TaskHandle_t *)&LED4_Task_Handle);
	if(xReturn == pdPASS)
		printf("LED4_Task创建成功\r\n");
	xReturn=xTaskCreate((TaskFunction_t)KEY_Task,(const char *)"KEY_Task",128,NULL,5,(TaskHandle_t*)&KEY_TASK_Handle);    
	if(xReturn==pdPASS)
		printf("KEY_Task任务创建成功\r\n");	
	xReturn=xTaskCreate((TaskFunction_t)KQM6600_Task, (const char *)"KQM6600_Task",256,NULL,2,(TaskHandle_t*)&KQM6600_TASK_Handle);            
	if(xReturn==pdPASS)
		printf("KQM6600_Task任务创建成功\r\n");	
	xReturn=xTaskCreate((TaskFunction_t)Sensor_Task, (const char *)"Sensor_Task",256,NULL,2,(TaskHandle_t*)&Sensor_TASK_Handle);            
	if(xReturn==pdPASS)
		printf("Sensor_Task任务创建成功\r\n");	
	xReturn=xTaskCreate((TaskFunction_t)Cloud_Task, (const char *)"Cloud_Task",1024,NULL,6,(TaskHandle_t*)&Cloud_TASK_Handle);            
	if(xReturn==pdPASS)
		printf("Cloud_Task联网任务创建成功\r\n");	
	xReturn = xTaskCreate((TaskFunction_t)vLvglTaskFunction, "lvgl_task", 512, NULL, 7, (TaskHandle_t*)&xLvglTaskHandle);
	if(xReturn==pdPASS)
		printf("lvgl_task任务创建成功\r\n");
	xReturn = xTaskCreate((TaskFunction_t)SU_03T_TASK, (const char *)"SU_03T_TASK", 128, NULL, 3, (TaskHandle_t*)&SU_03T_TASK_Handle);
	if(xReturn==pdPASS)
		printf("SU_03T_TASK任务创建成功\r\n");
	
	vTaskStartScheduler();           // 启动任务，开启调度 			
	while(1)
	{
		printf("进入了主循环\r\n");    //有了操作系统，这部分代码执行不到
	}
}

//任务栈区溢出的钩子函数   扩大内存
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
	//接口的适配12  用以告知 lvgl 经过的时间   
	//仿真的时候，这句话能放断点，1MS进一次   假如进入不到这里，可能是钩子函数没有使能
	//#define configUSE_TICK_HOOK 1 //置 1：使用时间片钩子（Tick Hook）；置 0：忽略时间片钩子
	//在中断中每隔 x毫秒 调用 lv_tick_inc(x) 用以告知 lvgl 经过的时间；我们如果使用的是裸机开发，
	//那么直接将这个函数放到硬件定时器的1ms中断服务函数内，如果我们使用的是操作系统，那么我们可以放到系统基础节拍的钩子函数内。	
	lv_tick_inc(1);
	timeDHT11[0]++;
	Time_Period[0]++;
}

//LED1任务的具体任务   每一个任务都是while(1)
void LED1_Task(void* parameter)
{
	printf("LED1_Task开始运行\r\n");
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
		vTaskDelay(500);   //系统级别的延迟函数 500ms的延迟
//  	Delay_nopms(500);    //这个延时函数，仍然占着CPU
	}
}

//LED4任务的具体任务
void LED4_Task(void* parameter)
{
	EventBits_t r_event; /* 定义一个事件接收变量 */
	while(1)
	{
		r_event = xEventGroupWaitBits(Event_Handle,   /* 事件对象句柄 */
												 KEY3_EVENT|KEY4_EVENT,   /* 接收任务感兴趣的事件 */
										                    pdTRUE,   /* 退出时清除事件位 */
									                    	pdTRUE,   /* 满足感兴趣的所有事件 */
							                  portMAX_DELAY);   /* 指定超时事件,一直等 */
		if ((r_event & (KEY3_EVENT|KEY4_EVENT)) == (KEY3_EVENT|KEY4_EVENT)) {
			/* 如果接收完成并且正确 */
			printf ( "KEY1 与 KEY2 都按下\n");
			LED4_Toggle; //LED1 反转
		} else{
			printf ( "事件错误！ \n");
			}
	}
}
//KEY任务的具体内容  每个任务都是死循环
void KEY_Task(void* parameter)
{
	u8 key = 0;	
	while(1)
	{
		key=Key_GetValue();
		switch(key)
		{
			case 0:   //没有按键按下
				break;
			case 1: 
						
				for(int i = 0; i < 100 ;i++)
				{
					lv_scr_load(guider_ui.screen);     //加载屏幕
					lv_bar_set_value(guider_ui.screen_bar_1,i,LV_ANIM_OFF);
					vTaskDelay(30);
				}

				break;
			case 2:   //按键2按下
				GPIO_ResetBits(GPIOE,GPIO_Pin_6);//拉低
				Delay_nopms(500);
				GPIO_SetBits(GPIOE,GPIO_Pin_6);//拉高
				Net_State = 4;
			  Net_Step = 0;
				break;
			case 3:   //按键3按下
				printf ( "按键3按下！ \n");
				lv_scr_load(guider_ui.screen);
				xEventGroupSetBits(Event_Handle,KEY3_EVENT);
				break;	
			case 4:   //按键4按下
				printf ( "按键4按下！ \n");
				lv_scr_load(guider_ui.screen_1);
				xEventGroupSetBits(Event_Handle,KEY4_EVENT);
				break;				
			default:
				break;
		}
		vTaskDelay(10);       //系统级别的延时函数  10ms的延时 	
	}
}


//二值信号量的应用
void KQM6600_Task(void* parameter)
{
	USART2_Config(9600);    //串口2初始化（KQM6600）
	while(1)
	{
		//参数1   等待的信号量句柄
		//参数2   等待时间     0(不等)    固定周期(等固定周期)   portMAX_DELAY(死等)
		//等到信号量，往下面执行，等不到信号，阻塞在这里
		xSemaphoreTake( BinarySem_Handle, portMAX_DELAY );  //等待信号量的到来
		KQM6600_DataAnalysis();
//		taskENTER_CRITICAL();            //进入临界区  
//		printf("VOC = %.1fppm\r\n",KQM.voc);
//		printf("甲醛 = %.2fmg/m3\r\n",KQM.hcho);
//		printf("CO2 = %uppm\r\n",KQM.co2);
//		taskEXIT_CRITICAL();             //退出临界区
		vTaskDelay(1000);                //系统级别的延时函数  1000ms的延时 
	}
}

//传感器采集任务
void Sensor_Task(void* parameter)
{
	vTaskDelay(1000);
	while(1)
	{
		taskENTER_CRITICAL();                 //进入临界区 
		ADC_value();                          //光照、烟雾
		DHT11_Display();                      //DHT11的时序获取,一定要放到临界区中,否则收到的数据会错误
		taskEXIT_CRITICAL();                  //退出临界区
		vTaskDelay(1000);                     //系统级别的延时函数 

	}
}

//SU_03T的任务
void SU_03T_TASK(void* parameter)
{
	while(1)
	{
		SU03_DataAnalysis();
		SU03_Send();
		vTaskDelay(10); 
	}
}

//联网的任务
void Cloud_Task(void* parameter)
{
	uint32_t dataLen = 0;           //可变报头和有效载荷的长度
	uint8_t lenlen = 0;             //标记几个字节表示长度
	uint16_t topicLen = 0;          //存放topic的长度
	char *payload = NULL;           //存放payload开始的起始地址
	char topic[256] = {0};
	while(1)
	{
		if(Net_State == 0)          //没有网络连接
		{
			Net_Connect();
		} 
		else if(Net_State == 1)        //建立了网络连接，没有mqtt链接
		{
			if(WIFI_Flag == 1)           //获取网络时间
			{
				WIFI_Time();
			}
			else{
				Mqtt_Cloud_Connect();		   //建立mqtt连接
			}
		}
		if(Time_Period[0]>Time_Period[1])    //时间片每十秒进来一次
		{
			Time_Period[0]=0;
			if(Net_State == 2)                 //已连接平台(网络通道已经建立)，已发送连接报文未发送订阅报文 
			{
				Mqtt_Subscribe_Ali();            //订阅报文
				wifi_message.rcv_flag = 0; 
				Net_State = 3;
			}
			else if(Net_State==3)              //已连接平台(网络通道已经建立)，已发送连接报文，已发送订阅报文，周期发布消息
			{
				Mqtt_Cloud_Publish();            //上报云平台
				vTaskDelay(50);		
				Mqtt_Heart_Send();               //心跳
			}
		}
		if(Net_State==3)                     //平台下发了数据   解析
		{
			wifi_message.rcv_flag = 0;	
			switch(wifi_message.rcv_buff[0])   //报头
			{
				case 0x90:   //订阅的回复
					printf("收到订阅回复\r\n");
					break;
				case 0x30:   //平台发布的消息
					printf("平台发布消息\r\n");		
					//求剩余长度				lenlen是剩余长度的长度		
					dataLen =  MQTT_LengthCalculation(&wifi_message.rcv_buff[1], &lenlen);            //计算可变报头+有效载荷长度
					topicLen = wifi_message.rcv_buff[1+lenlen]<<8|wifi_message.rcv_buff[1+lenlen+1];  //计算topic长度
					memcpy(topic,&wifi_message.rcv_buff[1+lenlen+2],topicLen);                        //一块内存中的数据复制到另一块内存中
					printf("收到下发控制数据：\r\n主题类型：0x%02X, \r\n剩余长度%d字节, 剩余长度：%d, \r\ntopic长度：%d\r\n",
																				wifi_message.rcv_buff[0], lenlen, dataLen, topicLen);
					printf("topic:%s\r\n", topic);
					if(strcmp(Subscribe_Topic, topic) == 0) {   //对比这个主题收到是下行的主题
						printf("收到下行设置报文,开始解析\r\n");
						payload = strstr((char*)&wifi_message.rcv_buff[1+lenlen+1+1], "{");//从topic开始查找负载 因为前几个数据可能有0，表示字符串结尾
						printf("payload：%s\r\n", payload);
						Ali_AlsDataAck(payload);
					}				
					else if(strcmp(Publish_Topic_Reply, topic) == 0) {  //平台收到消息后会回复一个消息
						printf("收到发布应答报文\r\n");						
					}
					memset(topic,0,sizeof(topic));
					break;
				case 0xD0:   //心跳的应答
					printf("心跳回复\r\n");					
					break;				
			}
			memset(wifi_message.rcv_buff,0,sizeof(wifi_message.rcv_buff));  //清空接收缓冲区
			wifi_message.rcv_count = 0;	;  //清空接收的数组的标签  让它从头接收	
		}
		if(Net_State==4)                //重新设置WIFI账号和密码
		{
			WIFI_Revise_AP_Net();
		}
		vTaskDelay(10); 		
	}
}

//屏幕的任务
void vLvglTaskFunction( void * pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS( 5 );
	xLastWakeTime = xTaskGetTickCount(); 
	setup_scr_screen(&guider_ui);      //屏幕screen内容的初始化    不加载
	setup_scr_screen_1(&guider_ui);    //屏幕screen_1内容的初始化  不加载

	vTaskDelay(200);
	lv_scr_load(guider_ui.screen_1);
	xTimerStart(Swtmr_1s_Handle,0); //开启周期定时器1
	for(;;)
	{		
		//接口的适配13         每隔x毫秒定期调用 ltask_handler()
		lv_task_handler();   //每隔 x毫秒 定期调用 lv_task_handler()  用以处理与 lvgl 相关的任务  
		vTaskDelayUntil( &xLastWakeTime, xPeriod );    //绝对延时
	}
}

char Lvgl_T[10];
void Swtmr_1s_Callback(void* parameter)
{
	RTC_GetTime();
//	void lv_label_set_text_fmt(lv_obj_t * label, const char * fmt, ...);
	memset(Lvgl_T,0,sizeof(Lvgl_T));
	sprintf (Lvgl_T,"%.1f",dht11.t);
	lv_label_set_text_fmt(guider_ui.screen_1_label_18,"%s",Lvgl_T);              //屏幕打印温度
	lv_label_set_text_fmt(guider_ui.screen_1_label_16,"%d",dht11.h);             //屏幕打印湿度
	lv_label_set_text_fmt(guider_ui.screen_1_label_19,"%d",KQM.co2);             //屏幕打印二氧化碳
	lv_label_set_text_fmt(guider_ui.screen_1_label_24,"%d",ADC_DMAGetValue[0]);  //屏幕打印光照
	memset(Lvgl_T,0,sizeof(Lvgl_T));
	sprintf (Lvgl_T,"%.2f",KQM.hcho);
	lv_label_set_text_fmt(guider_ui.screen_1_label_21,"%s",Lvgl_T);              //屏幕打印甲醛

//	lv_label_set_text(guider_ui.screen_1_label_1, "温度:27℃ ");
//	Time_Cnt=RTC_GetCounter();  //返回RTC的计数器的值
//	Now_time=localtime((const time_t *)&Time_Cnt);  //将秒数转换成时间的结构体
//第一种时间更新方式  用官方提供的格式化输出函数 lv_label_set_text_fmt
//	lv_label_set_text_fmt(guider_ui.screen_label_2,"%2d:%2d:%2d",Now_time->tm_hour,Now_time->tm_min,Now_time->tm_sec);
//第二种时间更新方式  自己格式化输出
//	sprintf((char *)Buf_Temp,"%2d:%2d:%2d",Now_time->tm_hour,Now_time->tm_min,Now_time->tm_sec);
//	lv_label_set_text(guider_ui.screen_label_2, (char *)Buf_Temp);
//	printf("%d年%d月%d日 %d:%d:%d\r\n",Now_time->tm_year+1900,Now_time->tm_mon+1,Now_time->tm_mday,Now_time->tm_hour,Now_time->tm_min,Now_time->tm_sec);					
}

//空闲钩子函数（Idle Hook）：

//作用：在系统处于空闲状态（即没有任务需要运行）时调用，可以用于执行一些低优先级的任务或进行系统性能统计。

//堆溢出钩子函数（Heap Overflow Hook）：

//作用：在任务运行时申请堆内存失败（堆溢出）时调用，可以用于采取适当的措施，如重启系统、打印错误信息等。

//任务创建钩子函数（Task Create Hook）：

//作用：在任务被创建时调用，可以用于执行特定的初始化操作，如分配资源、设置任务优先级等。

//任务删除钩子函数（Task Delete Hook）：

//作用：在任务被删除前调用，可以用于执行一些清理操作，如释放资源、保存状态等。

//任务切换钩子函数（Task Switch Hook）：

//作用：在任务切换时调用，可以用于执行一些特定的操作，如记录任务切换次数、监控任务的运行时间等。

//延迟钩子函数（Tick Hook）：

//作用：在系统滴答定时器中断中调用，可以用于执行一些周期性的任务，如更新系统时钟、处理周期性事件等。