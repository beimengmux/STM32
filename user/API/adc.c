#include "adc.h"
#include "kqm6600.h"

/*
作者：gld
函数作用：初始化adc
参数：无
返回值：无
time：2023-07-27-15：02
*/

//保存校准值
u16 adc_value = 0;
//定义一个数组保存ADC转换后的数据
u16 ADC_DMAGetValue[16] = {0};

void ADC1_Config(void)
{
	//1.PA5/PC1配置为模拟输入
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);//时钟
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;//管脚 5
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;//管脚 1
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	//2.配置ADC1
	//2.1打开ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//2.2配置ADC1时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//2.3配置ADC1--连续、扫描、启动方式
	ADC_InitTypeDef ADC_InitStruct = {0};
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//连续
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//不适用外部触发
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitStruct.ADC_NbrOfChannel = 3;//转换通道数
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;//扫描
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//2.4配置ADC1——IN5、通道5 -- 采样速录 -- 配置规则通道的位置
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,1,ADC_SampleTime_1Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,2,ADC_SampleTime_1Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_16,3,ADC_SampleTime_1Cycles5);
	//3.使能ADC1
	ADC_Cmd(ADC1,ENABLE);
	
	//ADC校准
	ADC_ResetCalibration(ADC1);//复位
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	adc_value = ADC1->DR;

	ADC1_DMAConfig();//初始化DMA
	
	//ADC_TempSensorVrefintCmd(ENABLE); //开启内部温度传感器
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);

}

void ADC1_DMAConfig(void)
{
	//使能DMA请求
	ADC_DMACmd(ADC1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMA_InitStruct = {0};
	DMA_InitStruct.DMA_BufferSize = 3;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;//外设作为数据传输的来源
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;//不是内存到内存的传输
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)ADC_DMAGetValue;//定义DMA内存基地址
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//数据宽度为16位
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//内存地址寄存器增加
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;//工作在循环缓存模式
	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //储存外设基地址
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据宽度
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址寄存器不变
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;//优先级很高
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//使能DMA
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

void ADC_value(void)
{
//	printf("初始值：%d\r\n",adc_value);
//	printf("Light intensity：%d\r\n",ADC_DMAGetValue[0]);
//	printf("fumes:%d\r\n",ADC_DMAGetValue[1]);
//	printf("芯片内部温度:%.f\r\n",(1.43-ADC_DMAGetValue[2])/4.3+25);
	KQM.fumes = ADC_DMAGetValue[1];
	KQM.Lightintensity = ADC_DMAGetValue[0];
	KQM.chip = (1.43-ADC_DMAGetValue[2])/4.3+25;
}

u32 ADC_GetValue(void)
{
    //1. 启动ADC1
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    //2. 等待ADC1转换完成
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    //3. 读取ADC1的值
		u32 i = ADC_GetConversionValue(ADC1) - adc_value;
		printf("Light intensity：%d\r\n",i);
    return i;
}

