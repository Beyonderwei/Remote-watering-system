/*
 * humidity.c
 *
 *  Created on: 2019��3��19��
 *      Author: Beyonderwei
 */

#include "flower_status.h"
#include "pinmux.h"
#include "gpio.h"
#include "flowerdata.h"

extern FLOWER_DATA flower1;
extern FLOWER_DATA flower2;
extern FLOWER_DATA flower3;
extern FLOWER_DATA flower4;

/**
 * Function to initialize adc pins
 *  \param  none
 *  \return none
 */
void adcInit(void)
{
    PinTypeADC(ADC_PIN_2, PIN_MODE_255);    //�� PIN_59 ���� ����ΪADC���Ź���
    PinTypeADC(ADC_PIN_3, PIN_MODE_255);    //�� PIN_60 ���� ����ΪADC���Ź���

    ADCTimerConfig(ADC_BASE, 2 ^ 17);  //adc ʱ�ӳ�ʼ��  ����һ��ʱ�����ȡ adc ��������
    ADCTimerEnable(ADC_BASE);   //ʹ�� adc ʱ��
    ADCEnable(ADC_BASE);    //ʹ�� adc ģ��

    ADCChannelEnable(ADC_BASE, CHANNEL_2);    //ʹ�� adc ͨ��2
    ADCChannelEnable(ADC_BASE, CHANNEL_3);    //ʹ�� adc ͨ��3
}

/**
 * Function to obtain voltage value
 *  \param  the channel of adc   eg: CHANNEL_2(defined in "humidity.h")
 *  \return voltage value
 */
static float adcValueGet(unsigned long Channel)
{
    float final_value_sum;
    int cnt; //��������ֵ
    unsigned long adc_sample;    //adc ����ֵ

    for (cnt = 0; cnt < CHANNEL_CNT; cnt++)
    {
        if (ADCFIFOLvlGet(ADC_BASE, Channel))
        {
            adc_sample = ADCFIFORead(ADC_BASE, Channel);
            //���̲���������������ģ� �²�������λ��ԭ��Ϊ������Ϊ16λ��adc Ϊ12λ����ߺ������λΪ0��������Ҫ������λ
            final_value_sum += ((((float) ((adc_sample >> 2) & 0x0FFF)) * 1.4)
                    / 4096);    //��׼��ѹ1.4V 12λ->4096
        }
    }
    return (final_value_sum / CHANNEL_CNT);  //���� CHANNEL_CNT �β�����ƽ��ֵ
}

static void flowerHumidityUpdate(void)
{
    //��ģ�⿪��1
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_0, GPIO_PIN_0);        //����IO��  PIN_63
    //�����1��ʪ������,�������ݸ� flower1 ��ʪ�ȱ���
    flower1.humidity = adcValueGet(CHANNEL_2);
    //�ر�ģ�⿪��1
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_0, 0);

    //��ģ�⿪��2
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, 0);        //����IO��  PIN_64
    //�����2��ʪ������,�������ݸ� flower2 ��ʪ�ȱ���
    flower2.humidity = adcValueGet(CHANNEL_2);
    //�ر�ģ�⿪��2
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, GPIO_PIN_1);

    //��ģ�⿪��3
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_2, GPIO_PIN_2);        //����IO��  PIN_01
    //�����3��ʪ������,�������ݸ� flower3 ��ʪ�ȱ���
    flower3.humidity = adcValueGet(CHANNEL_2);
    //�ر�ģ�⿪��3
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_2, 0);

    //��ģ�⿪��4
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_3, 0);        //����IO�� PIN_02
    //�����4��ʪ������,�������ݸ� flower4 ��ʪ�ȱ���
    flower4.humidity = adcValueGet(CHANNEL_2);
    //�ر�ģ�⿪��4
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_3, GPIO_PIN_3);
}

static void flowerLightUpdate(void)
{
    flower1.light = flower2.light = flower3.light = flower4.light =
            (int) adcValueGet(CHANNEL_3);
}

void flowerStatusUpdate(void)
{
    flowerHumidityUpdate();
    flowerLightUpdate();
}
