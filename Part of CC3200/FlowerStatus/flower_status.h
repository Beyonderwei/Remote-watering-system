/*
 * humidity.h
 *
 *  Created on: 2019��3��20��
 *      Author: Beyonderwei
 */
#ifndef FLOWERSTATUS_FLOWER_STATUS_H_
#define FLOWERSTATUS_FLOWER_STATUS_H_

#include "hw_types.h"
#include "pin.h"
#include "adc.h"
#include "hw_memmap.h"

/*------------������ʹ�õ� adc ����-----------*/
#define CHANNEL_2    ADC_CH_2  //adcͨ��  PIN_59 ��Ӧͨ�� ADC_CH_1
#define ADC_PIN_2    PIN_59   // adc ����  ��ʪ��

#define CHANNEL_3    ADC_CH_3  //adcͨ��  PIN_60 ��Ӧͨ�� ADC_CH_1
#define ADC_PIN_3    PIN_60   // adc ����  ���ǿ

#define CHANNEL_CNT    20   //��������

/*------------��������------------*/
void adcInit(void);
void flowerStatusUpdate(void);

#endif /* FLOWERSTATUS_FLOWER_STATUS_H_ */
