/*
 * humidity.h
 *
 *  Created on: 2019年3月20日
 *      Author: Beyonderwei
 */
#ifndef HUMIDITY_HUMIDITY_H_
#define HUMIDITY_HUMIDITY_H_

#include "hw_types.h"
#include "pin.h"
#include "adc.h"
#include "hw_memmap.h"

/*------------定义所使用的 adc 引脚-----------*/
#define CHANNEL_2    ADC_CH_2  //adc通道  PIN_58 对应通道 ADC_CH_1
#define ADC_PIN_2    PIN_59   // adc 引脚

#define CHANNEL_3    ADC_CH_3  //adc通道  PIN_58 对应通道 ADC_CH_1
#define ADC_PIN_3    PIN_60   // adc 引脚

#define CHANNEL_CNT    20   //采样次数

/*------------函数声明------------*/
void adcInit(void);
float adcValueGet(unsigned long Channel);

#endif /* HUMIDITY_HUMIDITY_H_ */
