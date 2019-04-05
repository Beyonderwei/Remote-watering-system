/*
 * pump.c
 *
 *  Created on: 2019年2月16日
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
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_4, GPIO_PIN_4);  //拉高 PIN_03，打开水泵1
        UtilsDelay(20000000);
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_4, 0);  //拉高 PIN_03，关闭水泵1
        flower1.bulk = 0;
    }

    if (flower2.bulk != 0)
    {
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_5, GPIO_PIN_5);  //拉高 PIN_04，打开水泵2
        UtilsDelay(20000000);
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_5, 0);  //拉高 PIN_04，关闭水泵2
        flower2.bulk = 0;
    }

    if (flower3.bulk != 0)
    {
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_6, GPIO_PIN_6);  //拉高 PIN_05，打开水泵3
        UtilsDelay(20000000);
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_6, 0);  //拉高 PIN_05，关闭水泵3
        flower3.bulk = 0;
    }

    if (flower4.bulk != 0)
    {
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_7, GPIO_PIN_7);  //拉高 PIN_06，打开水泵4
        UtilsDelay(20000000);
        GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_7, 0);  //拉高 PIN_06，关闭水泵4
        flower4.bulk = 0;
    }
}

