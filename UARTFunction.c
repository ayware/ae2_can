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

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    IntDisable(INT_UART0);
    UARTDisable(UART0_BASE);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));     // Uart hýzý 115200 rpi dede ayný hýz olmalý
    UARTFIFODisable(UART0_BASE);
    UARTFlowControlSet(UART0_BASE, UART_FLOWCONTROL_NONE);
    UARTIntEnable(UART0_BASE,UART_INT_RX | UART_INT_RT);
    UARTEnable(UART0_BASE);

    IntEnable(INT_UART0); //enable the UART interrupt
}


void UARTSendData(uint32_t mBase,char mData){

    while(!UARTCharPutNonBlocking(mBase, mData));

}




void UARTIntHandler(void)
{


    // 100 ms de bir tetikleniyor. Bu süre rpi de ayarlanýyor.


    if(Device_Address == DEVICE_RPI){



        uint32_t uartStatus;
        uartStatus = UARTIntStatus(UART0_BASE, true);
        UARTIntClear(UART0_BASE, uartStatus);


        int32_t ctr = UARTCharGetNonBlocking(UART0_BASE);

        if(ctr == -1 || ctr != ACK)
            return;

        int32_t command = UARTCharGetNonBlocking(UART0_BASE);
        int32_t commandType = UARTCharGetNonBlocking(UART0_BASE);

        switch(command){


            case COMMAND_DATA_CHECKER:

                if(commandType == COMMAND_TYPE_DATA_REQUEST)
                {

                    uint32_t i;
                    crc = 0;

                    uint32_t DATA_LENGTH = 21;


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
                    for(i = 0; i < 4; i++){

                        UARTSendData(UART0_BASE,UartPrefix[i]);


                    }


                    // Datalar yollandý
                    for(i = 0; i < DATA_LENGTH; i++){

                        UARTSendData(UART0_BASE,Register_Uart[i]);

                    }


                    // Crc yollandý

                    UARTSendData(UART0_BASE, crc);



                    loopCounter++;
                    if(loopCounter == 3){ // 300 ms

                        loopCounter = 0;

                        Register_Uart[8] = 0;
                        Register_Uart[17] = 0;

                    }




                }



                break;


    }


    }else if(Device_Address == DEVICE_BMS){


        uint32_t uartStatus;
        uartStatus = UARTIntStatus(UART0_BASE, true);
        UARTIntClear(UART0_BASE, uartStatus);

        while(!UARTCharsAvail(UART0_BASE)){};
        int32_t ack = UARTCharGetNonBlocking(UART0_BASE);

        if( ack != -1 && ack == ACK){

            uint8_t command;
            uint8_t commandType;
            uint8_t dataLength;
            uint8_t crc = 0;
            uint32_t crcCalculated = 0;

            while(!UARTCharsAvail(UART0_BASE)){};
            command = UARTCharGetNonBlocking(UART0_BASE);

            while(!UARTCharsAvail(UART0_BASE)){};
            commandType = UARTCharGetNonBlocking(UART0_BASE);

            while(!UARTCharsAvail(UART0_BASE)){};
            dataLength = UARTCharGetNonBlocking(UART0_BASE);

            crcCalculated += ACK;
            crcCalculated += command;
            crcCalculated += commandType;
            crcCalculated += dataLength;

            uint8_t data[4];

            int i;
            for(i=0; i<dataLength; i++){

                while(!UARTCharsAvail(UART0_BASE)){};
                data[i] = UARTCharGetNonBlocking(UART0_BASE);;

                crcCalculated += data[i];

            }

            crcCalculated %= 256;

            while(!UARTCharsAvail(UART0_BASE)){};
            crc = UARTCharGetNonBlocking(UART0_BASE);


            if(crc == crcCalculated){

                batteryCurrent1 = data[0];
                batteryCurrent2 = data[1];
                batteryVoltage1 = data[2];
                batteryVoltage2 = data[3];


            }





        }


    }


}




