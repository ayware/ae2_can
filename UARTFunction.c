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
    UARTFIFOEnable(UART0_BASE);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));     // Uart hýzý 115200 rpi dede ayný hýz olmalý

}


void UARTIntHandler(void)
{

    uint32_t uartStatus;
    uartStatus = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, uartStatus);


    if(!UARTCharsAvail(UART0_BASE))
        return;

    int32_t ctr = UARTCharGetNonBlocking(UART0_BASE);

    if(ctr == -1 || ctr != ACK)
        return;

    if(!UARTCharsAvail(UART0_BASE))
        return;

    int32_t command = UARTCharGetNonBlocking(UART0_BASE);

    switch(command){


    case COMMAND_DATA_CHECKER:


        if(!UARTCharsAvail(UART0_BASE))
            return;

        int32_t commandType = UARTCharGetNonBlocking(UART0_BASE);

        if(commandType == COMMAND_TYPE_DATA_REQUEST)
        {

            uint32_t i = 0;
            crc = 0;

            uint32_t DATA_LENGTH = 14;


            UartPrefix[0] = ACK;
            UartPrefix[1] = COMMAND_DATA_CHECKER;
            UartPrefix[2] = COMMAND_TYPE_DATA_RESPONSE;
            UartPrefix[3] = DATA_LENGTH;


            // Prefix crc hesaplandý;

            for(i=0; i<4; i++)
                crc += UartPrefix[i];

            // Datalar crc hesaplandý ve prefixe eklenip modlandý
            for(i=0; i<DATA_LENGTH; i++)
                crc += Register_Uart[i];

            crc %= 256;

            // Prefix yollandý
            for(i = 0; i < 4; i++)
                UARTCharPutNonBlocking(UART0_BASE,UartPrefix[i]);

            // Datalar yollandý
            for(i = 0; i < DATA_LENGTH; i++)
                UARTCharPutNonBlocking(UART0_BASE,Register_Uart[i]);


            // Crc yollandý
            UARTCharPutNonBlocking(UART0_BASE,crc);


            loopCounter++;
            if(loopCounter == 3){ // 300 ms

                loopCounter = 0;

                Register_Uart[4] = 0;
                Register_Uart[10] = 0;

            }



        }


        break;


    }


}




