/*
 * ADC_Function.c
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

#include "GlobalVariablesExtern.h"
#include "GlobalDefines.h"



void ADCInit (int address)
{

    if(address == DEVICE_MOTOR)
    {

        ADCHardwareOversampleConfigure(ADC0_BASE, 64);
        ADCSequenceDisable(ADC0_BASE, 3);
        ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
        ADCSequenceStepConfigure(ADC0_BASE, 3, 0,ADC_CTL_TS |  ADC_CTL_IE | ADC_CTL_END);
        ADCSequenceEnable(ADC0_BASE, 3);
        ADCIntClear(ADC0_BASE, 3);


    }



}
void GetADCResults (void)
{
        uint8_t i;

        for(i=0;i<4;i++)
            analogValues[i] = 0;

       if(Device_Address == DEVICE_MOTOR)
       {

           ADCProcessorTrigger(ADC0_BASE, 3);
           while(!ADCIntStatus(ADC0_BASE, 3, false));
           ADCIntClear(ADC0_BASE, 3);
           ADCSequenceDataGet(ADC0_BASE, 3, analogValues);

           uint32_t controllerHeatValue = analogValues[0];
           uint32_t temp = ( 147.5 - ((75*(3.3)*controllerHeatValue)/4096) ) * 10;

           motorControllerHeat1 = (temp>>8)&0xFF;
           motorControllerHeat2 = (temp>>0)&0xFF;


       }



}



