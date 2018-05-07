/*
 * UART_Function.c
 *
 *  Created on: Jan 23, 2018
 *      Author: s3rkan
 */

#include "stdio.h"
#include <stdint.h>
#include "stdbool.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_watchdog.h"


#include "driverlib/can.h"
#include "driverlib/cpu.h"
#include "driverlib/pin_map.h"

#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/rom.h"
#include "driverlib/watchdog.h"
#include "driverlib/adc.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"

#include "GlobalVariablesExtern.h"
#include "GlobalDefines.h"


void UartInit(void)
{

    GPIOPinConfigure(GPIO_PA0_U0RX); // uart giriþleri set edildi
    GPIOPinConfigure(GPIO_PA1_U0TX); // uart giriþleri set edildi

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); // Uart modülü aktif edildi


    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));     // Uart hýzý 115200 rpi dede ayný hýz olmalý

}

void UartReceived(){

    uint16_t CRC = 0x44,j = 0,i = 0;

    CRC = ((Received_Uart_Data[0] + Received_Uart_Data[1]
                                + Received_Uart_Data[2]) % 256);

    if (Received_Uart_Data[1] == CATEGORY_CHECK && Received_Uart_Data[3] == CRC)
    {


                UARTCharPut(UART0_BASE, ACK);
                CRC = ACK;

                for (j = 0; j < 18; j++)
                {
                    CRC += Register_Uart[j];
                }

                Register_Uart[18] = (uint8_t) (CRC % 256);

                for (i = 0; i < 19; i++)
                {
                     UARTCharPut(UART0_BASE, Register_Uart[i]);
                }


                loopCounter++;

                if(loopCounter == 100)
                {

                    loopCounter = 0;

                    Register_Uart[16] = 0;
                    Register_Uart[17] = 0;

                }



    }
    else if (Received_Uart_Data[1] == 0x55 && Received_Uart_Data[3] == 0xAA)
                UARTCharPut(UART0_BASE, ACK);
    else if (Received_Uart_Data[1] == 0xAA && Received_Uart_Data[3] == 0x55)
                UARTCharPut(UART0_BASE, ACK);
    else
                UARTCharPut(UART0_BASE, NACK);


}



