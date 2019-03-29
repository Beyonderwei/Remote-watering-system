/*
 * pump.c
 *
 *  Created on: 2019年2月16日
 *      Author: Beyonderwei
 */

#include "hw_types.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "pump.h"

/**
 * Function to config pump's IO
 *  \param  none
 *  \return none
 */
static void
pump_IO_config(void)
{
    /*--使能外围时钟：这里有配置哪一组的IO的时钟，容易忘记更改这里--*/
    PRCMPeripheralClkEnable(PRCM_GPIOA1, PRCM_RUN_MODE_CLK);

    //
    // Configure PIN_64 for GPIOOutput
    //

    /*--引脚配置--*/
    PinTypeGPIO(PUMP_PIN, PIN_MODE_0, false);
    /*--GPIO初始化--*/
    GPIODirModeSet(PUMP_IO_BASE, PUMP_IO, GPIO_DIR_MODE_OUT);
}


/**
 * Function to initialize pump
 *  \param  none
 *  \return none
 */
void
pump_init(void)
{
    pump_IO_config();
}


/**
 * Function to pull up PIN_64
 *  \param  none
 *  \return none
 */
void
pump_open(void)
{
    GPIOPinWrite(GPIOA1_BASE,GPIO_PIN_1,GPIO_PIN_1);        //拉高IO口 -> PIN_64
}


/**
 * Function to pull down PIN_64
 *  \param  none
 *  \return none
 */
void
pump_close(void)
{
    GPIOPinWrite(GPIOA1_BASE,GPIO_PIN_1,0);        //拉低IO口 -> PIN_64
}




