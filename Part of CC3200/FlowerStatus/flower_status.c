/*
 * humidity.c
 *
 *  Created on: 2019年3月19日
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
    PinTypeADC(ADC_PIN_2, PIN_MODE_255);    //将 PIN_59 引脚 设置为ADC引脚功能
    PinTypeADC(ADC_PIN_3, PIN_MODE_255);    //将 PIN_60 引脚 设置为ADC引脚功能

    ADCTimerConfig(ADC_BASE, 2 ^ 17);  //adc 时钟初始化  定义一个时间戳获取 adc 数据样本
    ADCTimerEnable(ADC_BASE);   //使能 adc 时钟
    ADCEnable(ADC_BASE);    //使能 adc 模块

    ADCChannelEnable(ADC_BASE, CHANNEL_2);    //使能 adc 通道2
    ADCChannelEnable(ADC_BASE, CHANNEL_3);    //使能 adc 通道3
}

/**
 * Function to obtain voltage value
 *  \param  the channel of adc   eg: CHANNEL_2(defined in "humidity.h")
 *  \return voltage value
 */
static float adcValueGet(unsigned long Channel)
{
    float final_value_sum;
    int cnt; //采样计数值
    unsigned long adc_sample;    //adc 采样值

    for (cnt = 0; cnt < CHANNEL_CNT; cnt++)
    {
        if (ADCFIFOLvlGet(ADC_BASE, Channel))
        {
            adc_sample = ADCFIFORead(ADC_BASE, Channel);
            //例程采用下述方法计算的， 猜测右移两位的原因为：数据为16位，adc 为12位，最高和最低两位为0，所以需要右移两位
            final_value_sum += ((((float) ((adc_sample >> 2) & 0x0FFF)) * 1.4)
                    / 4096);    //基准电压1.4V 12位->4096
        }
    }
    return (final_value_sum / CHANNEL_CNT);  //返回 CHANNEL_CNT 次测量的平均值
}

static void flowerHumidityUpdate(void)
{
    //打开模拟开关1
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_0, GPIO_PIN_0);        //拉高IO口  PIN_63
    //测监测口1的湿度数据,更新数据给 flower1 的湿度变量
    flower1.humidity = adcValueGet(CHANNEL_2);
    //关闭模拟开关1
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_0, 0);

    //打开模拟开关2
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, 0);        //拉低IO口  PIN_64
    //测监测口2的湿度数据,更新数据给 flower2 的湿度变量
    flower2.humidity = adcValueGet(CHANNEL_2);
    //关闭模拟开关2
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, GPIO_PIN_1);

    //打开模拟开关3
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_2, GPIO_PIN_2);        //拉高IO口  PIN_01
    //测监测口3的湿度数据,更新数据给 flower3 的湿度变量
    flower3.humidity = adcValueGet(CHANNEL_2);
    //关闭模拟开关3
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_2, 0);

    //打开模拟开关4
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_3, 0);        //拉高IO口 PIN_02
    //测监测口4的湿度数据,更新数据给 flower4 的湿度变量
    flower4.humidity = adcValueGet(CHANNEL_2);
    //关闭模拟开关4
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
