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


}



void
TimerTick(void)
{

    TimerIntClear(TIMER1_BASE,TIMER_A);

    mSeconds++;

    curWheelEncoder = wheelEncoder - lastWheelEncoder;
    curMotorEncoder = motorEncoder - lastMotorEncoder;

    lastWheelEncoder = curWheelEncoder;
    lastMotorEncoder = curMotorEncoder;


}


void
PortEIntHandler(void)
{

    uint32_t statusPin = 0;
    statusPin = GPIOIntStatus(GPIO_PORTE_BASE,true);
    GPIOIntClear(GPIO_PORTE_BASE,statusPin);


    if(Device_Address == DEVICE_RPI)
    {


        if(statusPin == GPIO_INT_PIN_1 )
        {
            //Break Status
            statBreak = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) == GPIO_PIN_1 ? 0 : 1;


        }
        if(statusPin == GPIO_INT_PIN_2 )
        {
            // DeadManSwitch Status

            statDeadSwitch = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) == GPIO_PIN_2 ? 0 : 1;

            if(statDeadSwitch == 0)
                speedValue = 0;

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



    if(Device_Address == DEVICE_RPI )
    {


        if( statusPin == GPIO_INT_PIN_5)
        {


                if(speedValue > 0 ){
                    speedValue--;
                }

        }

        if( statusPin  == GPIO_INT_PIN_4)
        {


                if(speedValue < SPEED_VALUE_LIMIT){
                    speedValue++;
                }

        }



    }

    if(Device_Address == DEVICE_MOTOR)
       {


           if(statusPin == GPIO_INT_PIN_5){


               wheelEncoder++;


           }
           if(statusPin == GPIO_INT_PIN_4)
           {

               motorEncoder++;

           }


       }




}






void WatchdogIntHandler(void)
{

    if(!clearWatchdog){

        return;
    }


    uint32_t status = WatchdogIntStatus(WATCHDOG0_BASE, true);
    WatchdogIntClear(WATCHDOG0_BASE);


    clearWatchdog = false;


}


int CrcCalc(uint8_t *data,uint32_t length)
{


    uint32_t crc = 0;
    int i;
    for(i=0; i<length; i++)
        crc += data[i];

    return crc % 256;


}


int main(void)
{
   FPUEnable();
   FPULazyStackingEnable();
   InitialConfiguration(); // Baþlangýç ayarlarý


   while(1)
   {


      LoopFunction();
      clearWatchdog = true;

   }


}


