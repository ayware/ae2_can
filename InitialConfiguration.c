/*
 * InitialConfiguration.c
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
#include "driverlib/pwm.h"

#include "GlobalVariablesExtern.h"
#include "GlobalDefines.h"


void InitMotorPwm(){

    period = SysCtlClockGet() / (100000/9);
    //Period = 250/18;

    GPIOPinConfigure(GPIO_PC6_WT1CCP0);
    GPIOPinConfigure(GPIO_PC7_WT1CCP1);
    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER1);
    TimerConfigure(WTIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM);

    TimerLoadSet(WTIMER1_BASE, TIMER_A, period);
    TimerLoadSet(WTIMER1_BASE, TIMER_B, period);

    MotorStop();

    TimerEnable(WTIMER1_BASE, TIMER_A);
    TimerEnable(WTIMER1_BASE, TIMER_B);


    //https://sites.google.com/site/luiselectronicprojects/tutorials/tiva-tutorials/tiva-general-purpose-timers/timer-pwm---rgb-led




}


void InitTimer(void)
{


    // Timer setted to 1 second

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE,TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A,SysCtlClockGet());
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER1_BASE,TIMER_A);



}

void InitialConfiguration()
{
	//System Clock
	//SysCtlClockSet( SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);//SYSCTL_SYSDIV_5 - 40MHz//SYSCTL_SYSDIV_2_5 80MHz
	// sistem clock u 25 MHz e set edildi.
	SysCtlClockSet( SYSCTL_SYSDIV_8 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);//SYSCTL_SYSDIV_5 - 40MHz//SYSCTL_SYSDIV_2_5 80MHz // SYSCTL_SYSDIV_8 25Mhz
	// Delay fonksiyonunun istenen deðerde kalamasý için cristal ile ayný deðer seçilir.


    // WDT 2s ye kuruldu.
    //SysCtlPeripheralEnable(SYSCTL_PERIP H_WDOG0);
    //WatchdogReloadSet(WATCHDOG0_BASE,25000000);
    //WatchdogResetEnable(WATCHDOG0_BASE);
   // WatchdogEnable(WATCHDOG0_BASE);

    //Port D konfigürasyonu
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, SW1 | SW2 | SW3 | SW4); // adresleme pinleri input yapýldý

    Device_Address=~(0xFFFFFFF0|GPIOPinRead(GPIO_PORTD_BASE,SW1|SW2|SW3|SW4));

    SysTickPeriodSet(25);

    // Bütün kesmeler aktif edildi
    IntMasterEnable();
    SysTickIntEnable();
    SysTickEnable();
    SysTickDisable();

    //Port A konfigürasyonu
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    if(Device_Address==DEVICE_RPI)
    {
        GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_0 ); // Rx uart input oldu
        GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_1); // Tx uart output oldu


    }
    else
        GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1); // Tx uart output oldu

    //Port B konfigürasyonu
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_4 );   // Rx Can input oldu
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, LED1 | GPIO_PIN_5); // Led çýkýþý ve Tx Can outout oldu
    GPIOPadConfigSet(GPIO_PORTB_BASE, LED1 , GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD); // led çýkýþý 8ma oldu

	//Port C konfigürasyonu
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    if(Device_Address==DEVICE_MOTOR)
    {
        GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);   //  encoder giriþleri input yapýldý
        GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, PWM1 | PWM2); // pwm çýkýþlarý output yalpýldý

        GPIOIntDisable(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5);
        GPIOIntClear(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5);
        GPIOIntRegister(GPIO_PORTC_BASE,PortCIntHandler);
        GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5,GPIO_RISING_EDGE);
        GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);


        InitMotorPwm();


    }else if(Device_Address == DEVICE_RPI)
    {

        GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

        GPIOIntDisable(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5);
        GPIOIntClear(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5);
        GPIOIntRegister(GPIO_PORTC_BASE,PortCIntHandler);
        GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5,GPIO_RISING_EDGE);
        GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);



    }
    else
        GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, INA | INB | PWM1 | PWM2); // pwm çýkýþlarý output yalpýldý


	//Port E konfigürasyonu
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    if(Device_Address==DEVICE_MOTOR)
    {
        GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);


    }
    else  if(Device_Address==DEVICE_RPI)
    {
        GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_3 |  GPIO_PIN_2 |  GPIO_PIN_1);

        GPIOIntDisable(GPIO_PORTE_BASE,GPIO_PIN_1 | GPIO_PIN_2);
        GPIOIntClear(GPIO_PORTE_BASE,GPIO_PIN_1 | GPIO_PIN_2);
        GPIOIntRegister(GPIO_PORTE_BASE,PortEIntHandler);
        GPIOIntTypeSet(GPIO_PORTE_BASE,GPIO_PIN_1 | GPIO_PIN_2,GPIO_BOTH_EDGES);
        GPIOIntEnable(GPIO_PORTE_BASE,GPIO_PIN_1 | GPIO_PIN_2);


        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);


    }
    else if(Device_Address==DEVICE_BMS)
    {
        GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_3 |  GPIO_PIN_2 |  GPIO_PIN_1);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    }

    CanInit();

    if(Device_Address==DEVICE_RPI)
        UartInit();
    else if(Device_Address == DEVICE_BMS)
	    ADCInit(DEVICE_BMS);
	else if(Device_Address==DEVICE_MOTOR)
	    ADCInit(DEVICE_MOTOR);

    InitTimer();

}


void delayMs(uint32_t value)
{
    ui32C=1000*value;
    SysTickEnable();
    while(ui32C);
    SysTickDisable();
}
void delayUs(uint32_t value)
{
    ui32C=value;
    SysTickEnable();
    while(ui32C);
    SysTickDisable();
}

void LedFlash(bool value)
{

    if(value==false)
        GPIOPinWrite(GPIO_PORTB_BASE, LED1, 0 );
    else
        GPIOPinWrite(GPIO_PORTB_BASE, LED1, LED1 );

}






