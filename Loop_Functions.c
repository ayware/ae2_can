/*
 * Loop_Functions.c
 *
 *  Created on: Feb 10, 2018
 *      Author: s3rka
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
#include "driverlib/pwm.h"
#include "driverlib/pwm.c"

#include "GlobalVariablesExtern.h"
#include "GlobalDefines.h"


void LoopFunction(void)
{


    if( Device_Address == DEVICE_RPI)
    {

        Register_Uart[13] = statBreak;
        Register_Uart[14] = statDeadSwitch;
        Register_Uart[15] = speedValue;

        Register_Can[0] = statBreak;
        Register_Can[1] = statDeadSwitch;
        Register_Can[2] = speedValue;

        CanWrite(CATEGORY_SPEED, DEVICE_RPI, DEVICE_MOTOR,&Register_Can[0]);

        CanWrite(CATEGORY_CHECK,DEVICE_RPI,DEVICE_BMS,&Register_Can[0]);
        CanWrite(CATEGORY_CHECK,DEVICE_RPI,DEVICE_MOTOR,&Register_Can[0]);



    }
    else if(Device_Address == DEVICE_MOTOR)
    {

        motorEncoder = curEncoder * 0.385;

        counter++;
        if(counter == 50000)
        {

            counter = 0;

            GetADCResults();
            mosfetHeat1 = (uint8_t) (analogValues[0] & 0x00FF);
            mosfetHeat2 = (uint8_t) ((analogValues[0] >> 8) & 0x00FF);

            motorControllerHeat1 = (uint8_t) (analogValues[3] & 0x00FF);
            motorControllerHeat2 = (uint8_t) ((analogValues[3] >> 8) & 0x00FF);


        }

        if(statBreak || !statDeadSwitch)
            MotorStop();
        else
            MotorDrive(speed);

        counter++;
        if(counter == 10000)
        {

            counter = 0;

            GetADCResults();

            mosfetHeat1 = (uint8_t)(analogValues[0] >> 8);
            mosfetHeat2 = (uint8_t)(analogValues[0] & 0x000000FF);


             }


    }
    else if(Device_Address == DEVICE_BMS)
    {

        counter++;
        if(counter == 10000)
        {

            counter = 0;

            GetADCResults();

            BatteryVoltage1 = (uint8_t)( analogValues[2] / (float)(870/13) );
            BatteryCurrent1 = (uint8_t)( analogValues[1] / (float)(1000/0.09) );


        }



    }


}

void MotorDrive(float motorSpeed){


      // Period-1 motoru durduruyor

     TimerMatchSet(WTIMER1_BASE, TIMER_A, period - motorSpeed);
     TimerMatchSet(WTIMER1_BASE, TIMER_B, period - motorSpeed);

}



void MotorStop(){


       TimerMatchSet(WTIMER1_BASE, TIMER_A, period - 1);
       TimerMatchSet(WTIMER1_BASE, TIMER_B, period - 1);

}






