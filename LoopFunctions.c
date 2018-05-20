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


        Register_Uart[18] = statBreak;
        Register_Uart[19] = statDeadSwitch;
        Register_Uart[20] = speedValue;

        Register_Can[0] = statBreak;
        Register_Can[1] = statDeadSwitch;
        Register_Can[2] = speedValue;

        // Motor kartýna speed,break,deadSwitch bilgilerini yolluyor
        CanWrite(COMMAND_SPEED, DEVICE_RPI, DEVICE_MOTOR,&Register_Can[0]);

        // RPI den diðer kartlara istek yolluyor
        CanWrite(COMMAND_CHECK,DEVICE_RPI,DEVICE_BMS,&Register_Can[0]);
        CanWrite(COMMAND_CHECK,DEVICE_RPI,DEVICE_MOTOR,&Register_Can[0]);



    }
    else if(Device_Address == DEVICE_MOTOR)
    {

        speedWheel = curWheelEncoder * 0.385;
        speedMotor = curMotorEncoder * 0.385;

        if(statBreak || !statDeadSwitch)
            MotorStop();
        else
            MotorDrive(speed);


        counter++;
        if(counter == 50000)
        {
            counter = 0;
            GetADCResults();
        }


    }
    else if(Device_Address == DEVICE_BMS)
    {

        counter++;
        if(counter == 50000)
        {
            counter = 0;
            GetADCResults();
        }

    }


}

void MotorDrive(float motorSpeed){


      // Period-1 motoru durduruyor

    float actualProportion = SPEED_MAX / SPEED_VALUE_LIMIT;
    float actualSpeed = speedValue * actualProportion;
    errSpeed = actualSpeed - speedWheel;

    float P = errSpeed * KP;
    float I = errSpeed * KI;

    speedResult = P + I;

    if(speedResult < 0)
        MotorStop();
    else{

        motorSpeed -= (period/10);

        if(motorSpeed >= period)
            motorSpeed = period - 1;
        else if(motorSpeed < 0)
            motorSpeed = 1;

        TimerMatchSet(WTIMER1_BASE, TIMER_A, period - motorSpeed);
        TimerMatchSet(WTIMER1_BASE, TIMER_B, period - motorSpeed);

    }



}



void MotorStop(){


    TimerMatchSet(WTIMER1_BASE, TIMER_A, period - 1);
    TimerMatchSet(WTIMER1_BASE, TIMER_B, period - 1);

}






