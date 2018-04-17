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
    if(address == DEVICE_BMS)
    {
        GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3 |  GPIO_PIN_2 |  GPIO_PIN_1); // analog giriþler input yapýldý
        ADCSequenceDisable(ADC0_BASE, 1); //Sample Sequencer 1 ile iþlem yapacaðýmýz için öncelikle kapatýyoruz.
        ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
        ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0); //Sequencer Adým 0 : PE3
        ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH1); //Sequencer Adým 1 : PE2
        ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH2); //Sequencer Adým 2 : PE1
        ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END); //Sequencer Adým 3 : Sýcaklýk sensörünün deðeri ve
        ADCSequenceEnable(ADC0_BASE, 1);
        ADCIntClear(ADC0_BASE, 1);
    }
    else if (address == DEVICE_MOTOR)
    {
        GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_1); // analog giriþler input yapýldý
        ADCSequenceDisable(ADC0_BASE, 1); //Sample Sequencer 1 ile iþlem yapacaðýmýz için öncelikle kapatýyoruz.
        ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
        ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH2); //Sequencer Adým 2 : PE1
        ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END); //Sequencer Adým 3 : Sýcaklýk sensörünün deðeri ve
        ADCSequenceEnable(ADC0_BASE, 1);
        ADCIntClear(ADC0_BASE, 1);
    }

}
void GetADCResults (void)
{
        uint8_t i;

        for(i=0;i<4;i++)
            analogValues[i]=0;

        ADCProcessorTrigger(ADC0_BASE, 1);
        while(!ADCIntStatus(ADC0_BASE, 1, false));
        ADCIntClear(ADC0_BASE, 1);
        ADCSequenceDataGet(ADC0_BASE, 1, analogValues);

}
