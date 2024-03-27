#include "adc.h"
#include "kqm6600.h"

/*
���ߣ�gld
�������ã���ʼ��adc
��������
����ֵ����
time��2023-07-27-15��02
*/

//����У׼ֵ
u16 adc_value = 0;
//����һ�����鱣��ADCת���������
u16 ADC_DMAGetValue[16] = {0};

void ADC1_Config(void)
{
	//1.PA5/PC1����Ϊģ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);//ʱ��
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//ģ������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;//�ܽ� 5
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;//�ܽ� 1
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	//2.����ADC1
	//2.1��ADC1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//2.2����ADC1ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//2.3����ADC1--������ɨ�衢������ʽ
	ADC_InitTypeDef ADC_InitStruct = {0};
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//����
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������ⲿ����
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_InitStruct.ADC_NbrOfChannel = 3;//ת��ͨ����
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;//ɨ��
	ADC_Init(ADC1,&ADC_InitStruct);
	
	//2.4����ADC1����IN5��ͨ��5 -- ������¼ -- ���ù���ͨ����λ��
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,1,ADC_SampleTime_1Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,2,ADC_SampleTime_1Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_16,3,ADC_SampleTime_1Cycles5);
	//3.ʹ��ADC1
	ADC_Cmd(ADC1,ENABLE);
	
	//ADCУ׼
	ADC_ResetCalibration(ADC1);//��λ
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	adc_value = ADC1->DR;

	ADC1_DMAConfig();//��ʼ��DMA
	
	//ADC_TempSensorVrefintCmd(ENABLE); //�����ڲ��¶ȴ�����
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);

}

void ADC1_DMAConfig(void)
{
	//ʹ��DMA����
	ADC_DMACmd(ADC1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMA_InitStruct = {0};
	DMA_InitStruct.DMA_BufferSize = 3;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;//������Ϊ���ݴ������Դ
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;//�����ڴ浽�ڴ�Ĵ���
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)ADC_DMAGetValue;//����DMA�ڴ����ַ
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���ݿ��Ϊ16λ
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//�ڴ��ַ�Ĵ�������
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;//������ѭ������ģʽ
	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //�����������ַ
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݿ��
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�Ĵ�������
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;//���ȼ��ܸ�
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//ʹ��DMA
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

void ADC_value(void)
{
//	printf("��ʼֵ��%d\r\n",adc_value);
//	printf("Light intensity��%d\r\n",ADC_DMAGetValue[0]);
//	printf("fumes:%d\r\n",ADC_DMAGetValue[1]);
//	printf("оƬ�ڲ��¶�:%.f\r\n",(1.43-ADC_DMAGetValue[2])/4.3+25);
	KQM.fumes = ADC_DMAGetValue[1];
	KQM.Lightintensity = ADC_DMAGetValue[0];
	KQM.chip = (1.43-ADC_DMAGetValue[2])/4.3+25;
}

u32 ADC_GetValue(void)
{
    //1. ����ADC1
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    //2. �ȴ�ADC1ת�����
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    //3. ��ȡADC1��ֵ
		u32 i = ADC_GetConversionValue(ADC1) - adc_value;
		printf("Light intensity��%d\r\n",i);
    return i;
}

