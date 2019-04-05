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
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA0, PRCM_RUN_MODE_CLK); //��ʼ�� GPIOA0 �����ŵ�ʱ��  PIN_58

    /*--uart--*/
    MAP_PinTypeUART(PIN_55, PIN_MODE_3);   //Configure PIN_55 for UART0 UART0_TX
    MAP_PinTypeUART(PIN_57, PIN_MODE_3);   //Configure PIN_57 for UART0 UART0_RX

    /*--PIN_58 ����ʶ�� AP ģʽ�� STA ģʽ--*/
    MAP_PinTypeGPIO(PIN_58, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA0_BASE, 0x8, GPIO_DIR_MODE_IN); // Configure PIN_58 for GPIOInput
    PinConfigSet(PIN_58, PIN_STRENGTH_2MA | PIN_STRENGTH_4MA, PIN_TYPE_STD_PD);

    /*--ʪ�Ȳ����� adc ͨ��ѡ��������ţ�������Χģ�⿪�أ�--*/
    PinTypeGPIO(PIN_63, PIN_MODE_0, false);     //������������ ���Ź���ģʽ  ��©ģʽ��STD
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_0, GPIO_DIR_MODE_OUT); //��һ��Ķ˿ڵ�ַ  GPIO_A1�ĵ�0�� GPIOλȨ(0~7)   ����������
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_0, 0);        //����IO��  �ر�ģ�⿪��ͨ��1

    PinTypeGPIO(PIN_64, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_1, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_1, GPIO_PIN_1);        //����IO��  �ر�ģ�⿪��ͨ��2

    PinTypeGPIO(PIN_01, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_2, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_2, 0);        //����IO��  �ر�ģ�⿪��ͨ��3

    PinTypeGPIO(PIN_02, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_3, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA1_BASE, GPIO_PIN_3, GPIO_PIN_3);        //����IO��  �ر�ģ�⿪��ͨ��4

    /*--��ˮ���ƣ� ��ˮ�ڿ������ţ�������Χ���أ������ƽ�ˮ������ʼ������Ϊ�ͣ�������ˮ--*/
    PinTypeGPIO(PIN_03, PIN_MODE_0, false);     //������������ ���Ź���ģʽ  ��©ģʽ��STD
    GPIODirModeSet(GPIOA1_BASE, GPIO_PIN_4, GPIO_DIR_MODE_OUT); //��һ��Ķ˿ڵ�ַ  GPIO_A1�ĵ�4�� GPIOλȨ(0~7)   ����������
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

