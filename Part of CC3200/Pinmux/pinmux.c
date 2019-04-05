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
void PinMuxConfig(void)
{
    // Enable Peripheral Clocks 
    MAP_PRCMPeripheralClkEnable(PRCM_UARTA0, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA0, PRCM_RUN_MODE_CLK); //初始化 GPIOA0 组引脚的时钟  PIN_58

    /*--uart--*/
    MAP_PinTypeUART(PIN_55, PIN_MODE_3);   //Configure PIN_55 for UART0 UART0_TX
    MAP_PinTypeUART(PIN_57, PIN_MODE_3);   //Configure PIN_57 for UART0 UART0_RX

    /*--PIN_58 用于识别 AP 模式和 STA 模式--*/
    MAP_PinTypeGPIO(PIN_58, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA0_BASE, 0x8, GPIO_DIR_MODE_IN); // Configure PIN_58 for GPIOInput
    PinConfigSet(PIN_58, PIN_STRENGTH_2MA | PIN_STRENGTH_4MA, PIN_TYPE_STD_PD);

    /*--湿度测量， adc 通道选择控制引脚（控制外围模拟开关）--*/
    PinTypeGPIO(PIN_63, PIN_MODE_0, false);     //参数：引脚名 引脚功能模式  开漏模式或STD
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_0, GPIO_DIR_MODE_OUT); //哪一组的端口地址  GPIO_A1的第0个 GPIO位权(0~7)   输入或者输出
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_0, 0);        //拉低IO口  关闭模拟开关通道1

    PinTypeGPIO(PIN_64, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_1, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, GPIO_PIN_1);        //拉高IO口  关闭模拟开关通道2

    PinTypeGPIO(PIN_01, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_2, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_2, 0);        //拉低IO口  关闭模拟开关通道3

    PinTypeGPIO(PIN_02, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_3, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_3, GPIO_PIN_3);        //拉高IO口  关闭模拟开关通道4

    /*--浇水控制， 浇水口控制引脚（控制外围开关，来控制浇水）。初始化所有为低，即不浇水--*/
    PinTypeGPIO(PIN_03, PIN_MODE_0, false);     //参数：引脚名 引脚功能模式  开漏模式或STD
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_4, GPIO_DIR_MODE_OUT); //哪一组的端口地址  GPIO_A1的第4个 GPIO位权(0~7)   输入或者输出
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_4, 0);

    PinTypeGPIO(PIN_04, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_5, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_5, 0);

    PinTypeGPIO(PIN_05, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_6, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_6, 0);

    PinTypeGPIO(PIN_06, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_7, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_7, 0);
}

