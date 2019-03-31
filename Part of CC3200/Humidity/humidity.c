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
    PinTypeADC(ADC_PIN_2,PIN_MODE_255);    //�� PIN_59 ���� ����ΪADC���Ź���
    PinTypeADC(ADC_PIN_3,PIN_MODE_255);    //�� PIN_60 ���� ����ΪADC���Ź���

    ADCTimerConfig(ADC_BASE,2^17);  //adc ʱ�ӳ�ʼ��  ����һ��ʱ�����ȡ adc ��������
    ADCTimerEnable(ADC_BASE);   //ʹ�� adc ʱ��
    ADCEnable(ADC_BASE);    //ʹ�� adc ģ��

    ADCChannelEnable(ADC_BASE,CHANNEL_2);    //ʹ�� adc ͨ��2
    ADCChannelEnable(ADC_BASE,CHANNEL_3);    //ʹ�� adc ͨ��3
}

/**
 * Function to obtain voltage value
 *  \param  the channel of adc   eg: CHANNEL_2(defined in "humidity.h")
 *  \return voltage value
 */
float
adcValueGet(unsigned long Channel)
{
    float final_value_sum;
    int cnt; //��������ֵ
    unsigned long adc_sample;    //adc ����ֵ

    for(cnt=0; cnt < CHANNEL_CNT ; cnt++)
        {
            if( ADCFIFOLvlGet (ADC_BASE, Channel))
            {
                adc_sample = ADCFIFORead(ADC_BASE, Channel);
                //���̲���������������ģ� �²�������λ��ԭ��Ϊ������Ϊ16λ��adc Ϊ12λ����ߺ������λΪ0��������Ҫ������λ
                final_value_sum += ((((float)((adc_sample >> 2 ) & 0x0FFF))*1.4)/4096);    //��׼��ѹ1.4V 12λ->4096
            }
        }
    return (final_value_sum/CHANNEL_CNT);  //���� CHANNEL_CNT �β�����ƽ��ֵ
}


