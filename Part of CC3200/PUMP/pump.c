/*
 * pump.c
 *
 *  Created on: 2019��2��16��
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
    /*--ʹ����Χʱ�ӣ�������������һ���IO��ʱ�ӣ��������Ǹ�������--*/
    PRCMPeripheralClkEnable(PRCM_GPIOA1, PRCM_RUN_MODE_CLK);

    //
    // Configure PIN_64 for GPIOOutput
    //

    /*--��������--*/
    PinTypeGPIO(PUMP_PIN, PIN_MODE_0, false);
    /*--GPIO��ʼ��--*/
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
    GPIOPinWrite(GPIOA1_BASE,GPIO_PIN_1,GPIO_PIN_1);        //����IO�� -> PIN_64
}


/**
 * Function to pull down PIN_64
 *  \param  none
 *  \return none
 */
void
pump_close(void)
{
    GPIOPinWrite(GPIOA1_BASE,GPIO_PIN_1,0);        //����IO�� -> PIN_64
}




