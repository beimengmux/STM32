#ifndef _MAIN_H_
#define _MAIN_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "led.h"
#include "KEY.h"
#include "BEEP.h"
#include "RGB.h"
#include "EXTI.h"
#include "delay.h"
#include "USART.h"
#include "DHT11.h"
#include "adc.h"
#include "tim.h"
#include "rtc.h"
#include "kqm6600.h"
#include "su_03t.h"
#include "bsp_lcd.h"
#include "spi.h"
#include "stm32_eval_spi_flash.h"
#include "wifi.h"
#include "cloud.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"  //消息队列
#include "semphr.h" //信号量
#include "event_groups.h" // 事件头文件 软件定时器
#include "lv_port_disp.h"
#include "lvgl.h"
#include "gui_guider.h"

extern SemaphoreHandle_t BinarySem_Handle;

#endif

