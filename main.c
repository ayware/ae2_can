/*
 * main.c
 *
 *  Created on: Jan 23, 2018
 *      Author: s3rkan
 */
#include "stdio.h"
#include <stdint.h>
#include "stdbool.h"

#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"
#include "inc/hw_watchdog.h"

#include "driverlib/cpu.h"

#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"

#include "driverlib/fpu.h"
#include "driverlib/cpu.c"
#include "driverlib/interrupt.c"
#include "driverlib/sysctl.c"
#include "driverlib/can.h"
#include "driverlib/can.c"
#include "driverlib/i2c.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"
#include "utils/uartstdio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.c"
#include "driverlib/rom.h"
#include "driverlib/watchdog.h"
#include "driverlib/adc.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "GlobalVariables.h"
#include "GlobalDefines.h"


#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif

void
SysTickIntHandler(void)
{


    if(ui32C!=0)
        ui32C--;

}



void
TimerTick(void)
{

    TimerIntClear(TIMER1_BASE,TIMER_A);

    mSeconds++;

    curEncoder = wheelCounter - lastEncoder;
    lastEncoder = wheelCounter;


}


void
PortEIntHandler(void)
{

    uint32_t statusPin = 0;
    statusPin = GPIOIntStatus(GPIO_PORTE_BASE,true);
    GPIOIntClear(GPIO_PORTE_BASE,statusPin);

    if(Device_Address == DEVICE_RPI)
    {


        if(statusPin == GPIO_INT_PIN_1)
        {
            //Break Status
            statBreak = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) == GPIO_PIN_1 ? 0 : 1;


        }
        if(statusPin == GPIO_INT_PIN_2)
        {
            // DeadManSwitch Status

            statDeadSwitch = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) == GPIO_PIN_2 ? 0 : 1;

        }




    }


    if(Device_Address == DEVICE_BMS)
    {


    }



}

void
PortCIntHandler(void)
{

    uint32_t statusPin = 0;
    statusPin = GPIOIntStatus(GPIO_PORTC_BASE, true);
    GPIOIntClear(GPIO_PORTC_BASE,statusPin);

    if(Device_Address == DEVICE_RPI)
    {


        if(statusPin == GPIO_INT_PIN_4)
        {

            if(speedValue > 0)
                speedValue--;


        }

        if(statusPin == GPIO_INT_PIN_5)
        {

            if(speedValue < SPEED_LIMIT)
                speedValue++;


        }



    }
    if(Device_Address == DEVICE_MOTOR)
       {


           if(statusPin == GPIO_INT_PIN_5){

               //Encoder

               wheelCounter++;

           }


       }



}




void UARTIntHandler(void)
{

 unsigned long ulStatus;
 ulStatus = UARTIntStatus(UART0_BASE, true); //get interrupt status
 UARTIntClear(UART0_BASE, ulStatus); //clear the asserted interrupts
 while(UARTCharsAvail(UART0_BASE)) //loop while there are chars
  {
     Received_Uart_Data[uartDataCounter++]=UARTCharGetNonBlocking(UART0_BASE);

     if(Received_Uart_Data[0]!=0x5A)
         uartDataCounter=0;

     if(uartDataCounter==4)
     {
         uartDataCounter=0;
         Uart_Data_received=1;

         UartReceived();

     }

  }

}



int main(void)
{
   FPUEnable();
   FPULazyStackingEnable();
   InitialConfiguration(); // Baþlangýç ayarlarý

   while(1)
   {

      LoopFunction();


   }


}


