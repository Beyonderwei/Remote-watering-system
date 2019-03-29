/*
 * humidity.c
 *
 *  Created on: 2019��3��19��
 *      Author: Beyonderwei
 */

#include "humidity.h"

/**
 * Function to initialize adc pins
 *  \param  none
 *  \return none
 */
void
adcInit(void)
{
    PinTypeADC(ADC_PIN,PIN_MODE_255);    //�� PIN_59 ���� ����ΪADC���Ź���
    ADCTimerConfig(ADC_BASE,2^17);  //adc ʱ�ӳ�ʼ��  ����һ��ʱ�����ȡ adc ��������
    ADCTimerEnable(ADC_BASE);   //ʹ�� adc ʱ��
    ADCEnable(ADC_BASE);    //ʹ�� adc ģ��
    ADCChannelEnable(ADC_BASE,CHANNEL);    //ʹ�� adc ͨ��
}

/**
 * Function to obtain voltage value
 *  \param  none
 *  \return voltage value
 */
float
adcValueGet(void)
{
    float final_value_sum;
    int cnt; //��������ֵ
    unsigned long adc_sample;    //adc ����ֵ

    for(cnt=0; cnt < CHANNEL_CNT ; cnt++)
        {
            if( ADCFIFOLvlGet (ADC_BASE, CHANNEL))
            {
                adc_sample = ADCFIFORead(ADC_BASE, CHANNEL);
                //���̲���������������ģ� �²�������λ��ԭ��Ϊ������Ϊ16λ��adc Ϊ12λ����ߺ������λΪ0��������Ҫ������λ
                final_value_sum += ((((float)((adc_sample >> 2 ) & 0x0FFF))*1.4)/4096);    //��׼��ѹ1.4V 12λ->4096
            }
        }
    return (final_value_sum/CHANNEL_CNT);  //���� CHANNEL_CNT �β�����ƽ��ֵ
}


