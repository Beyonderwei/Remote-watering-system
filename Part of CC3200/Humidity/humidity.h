/*
 * humidity.h
 *
 *  Created on: 2019��3��20��
 *      Author: Beyonderwei
 */
#ifndef HUMIDITY_HUMIDITY_H_
#define HUMIDITY_HUMIDITY_H_

#include "hw_types.h"
#include "pin.h"
#include "adc.h"
#include "hw_memmap.h"

/*------------������ʹ�õ� adc ����-----------*/
#define CHANNEL_2    ADC_CH_2  //adcͨ��  PIN_58 ��Ӧͨ�� ADC_CH_1
#define ADC_PIN_2    PIN_59   // adc ����

#define CHANNEL_3    ADC_CH_3  //adcͨ��  PIN_58 ��Ӧͨ�� ADC_CH_1
#define ADC_PIN_3    PIN_60   // adc ����

#define CHANNEL_CNT    20   //��������

/*------------��������------------*/
void adcInit(void);
float adcValueGet(unsigned long Channel);

#endif /* HUMIDITY_HUMIDITY_H_ */
