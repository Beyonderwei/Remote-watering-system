/*
 * pump.c
 *
 *  Created on: 2019��2��16��
 *      Author: Beyonderwei
 */
#include "flowerdata.h"
#include "pump.h"
#include "hw_types.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "gpio.h"

extern FLOWER_DATA flower1;
extern FLOWER_DATA flower2;
extern FLOWER_DATA flower3;
extern FLOWER_DATA flower4;

/**
 * Function to Water the flower
 *  \param  none
 *  \return none
 */
void WaterTheFlowers(void)
{
    if (flower1.bulk != 0)
    {
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_4, GPIO_PIN_4);  //���� PIN_03����ˮ��1
        UtilsDelay(20000000);
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_4, 0);  //���� PIN_03���ر�ˮ��1
        flower1.bulk = 0;
    }

    if (flower2.bulk != 0)
    {
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_5, GPIO_PIN_5);  //���� PIN_04����ˮ��2
        UtilsDelay(20000000);
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_5, 0);  //���� PIN_04���ر�ˮ��2
        flower2.bulk = 0;
    }

    if (flower3.bulk != 0)
    {
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_6, GPIO_PIN_6);  //���� PIN_05����ˮ��3
        UtilsDelay(20000000);
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_6, 0);  //���� PIN_05���ر�ˮ��3
        flower3.bulk = 0;
    }

    if (flower4.bulk != 0)
    {
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_7, GPIO_PIN_7);  //���� PIN_06����ˮ��4
        UtilsDelay(20000000);
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_7, 0);  //���� PIN_06���ر�ˮ��4
        flower4.bulk = 0;
    }
}

