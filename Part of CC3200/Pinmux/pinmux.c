//*****************************************************************************
// pinmux.c
//
// configure the device pins for different peripheral signals
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

// This file was automatically generated on 7/21/2014 at 3:06:20 PM
// by TI PinMux version 3.0.334
//
//*****************************************************************************

#include "pinmux.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "rom.h"
#include "rom_map.h"
#include "gpio.h"
#include "prcm.h"

//*****************************************************************************
void
PinMuxConfig(void)
{
    // Enable Peripheral Clocks 
    MAP_PRCMPeripheralClkEnable(PRCM_UARTA0, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA0, PRCM_RUN_MODE_CLK);    //初始化 GPIOA0 组引脚的时钟  PIN_58

    /*--uart--*/
    MAP_PinTypeUART(PIN_55, PIN_MODE_3);    //Configure PIN_55 for UART0 UART0_TX
    MAP_PinTypeUART(PIN_57, PIN_MODE_3);    //Configure PIN_57 for UART0 UART0_RX

    /*--PIN_58 用于识别 AP 模式和 STA 模式--*/
    MAP_PinTypeGPIO(PIN_58, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA0_BASE, 0x8, GPIO_DIR_MODE_IN); // Configure PIN_58 for GPIOInput
    PinConfigSet(PIN_58,PIN_STRENGTH_2MA|PIN_STRENGTH_4MA,PIN_TYPE_STD_PD);

    /*--湿度测量， adc 通道选择控制引脚（控制外围模拟开关）--*/
    PinTypeGPIO(PIN_63, PIN_MODE_0, false);     //参数：引脚名 引脚功能模式  开漏模式或STD
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_0, GPIO_DIR_MODE_OUT); //哪一组的端口地址  GPIO_A1的第1个 GPIO位权(0~7)   输入或者输出

    PinTypeGPIO(PIN_64, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_1, GPIO_DIR_MODE_OUT);

    PinTypeGPIO(PIN_01, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_2, GPIO_DIR_MODE_OUT);

    PinTypeGPIO(PIN_02, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_3, GPIO_DIR_MODE_OUT);

    /*--湿度测量， adc 通道选择控制引脚（控制外围模拟开关）--*/
    PinTypeGPIO(PIN_03, PIN_MODE_0, false);     //参数：引脚名 引脚功能模式  开漏模式或STD
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_4, GPIO_DIR_MODE_OUT); //哪一组的端口地址  GPIO_A1的第1个 GPIO位权(0~7)   输入或者输出

    PinTypeGPIO(PIN_04, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_5, GPIO_DIR_MODE_OUT);

    PinTypeGPIO(PIN_05, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_6, GPIO_DIR_MODE_OUT);

    PinTypeGPIO(PIN_06, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_7, GPIO_DIR_MODE_OUT);
}

