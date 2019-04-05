/*
 * humidity.h
 *
 *  Created on: 2019年3月20日
 *      Author: Beyonderwei
 */
#ifndef FLOWERSTATUS_FLOWER_STATUS_H_
#define FLOWERSTATUS_FLOWER_STATUS_H_

#include "hw_types.h"
#include "pin.h"
#include "adc.h"
#include "hw_memmap.h"

/*------------定义所使用的 adc 引脚-----------*/
#define CHANNEL_2    ADC_CH_2  //adc通道  PIN_59 对应通道 ADC_CH_1
#define ADC_PIN_2    PIN_59   // adc 引脚  测湿度

#define CHANNEL_3    ADC_CH_3  //adc通道  PIN_60 对应通道 ADC_CH_1
#define ADC_PIN_3    PIN_60   // adc 引脚  测光强

#define CHANNEL_CNT    20   //采样次数

/*------------函数声明------------*/
void adcInit(void);
void flowerStatusUpdate(void);

#endif /* FLOWERSTATUS_FLOWER_STATUS_H_ */
