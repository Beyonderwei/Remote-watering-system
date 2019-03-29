/*
 * pump.h
 *
 *  Created on: 2019Äê2ÔÂ16ÈÕ
 *      Author: Beyonderwei
 */

#ifndef PUMP_PUMP_H_
#define PUMP_PUMP_H_

#include "pin.h"
#include "gpio.h"
#include "hw_memmap.h"

#define PUMP_PIN     PIN_64
#define PUMP_IO_BASE    GPIOA1_BASE
#define PUMP_IO      GPIO_PIN_1

static void pump_IO_config(void);
void pump_init(void);
void pump_open(void);
void pump_close(void);

#endif /* PUMP_PUMP_H_ */
