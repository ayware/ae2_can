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



void
EnablePeriph(){


    // T�m kartlar i�in ortak peripheraller ----

    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0); // Watchdog 0 aktif edildi
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // Port B aktif edildi
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1); // Timer1 aktif edildi
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0); // Can ��k��lar�n� aktif ediyor.

    // ------------------------------------------


    switch(Device_Address){


    case DEVICE_RPI:

        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); // Uart mod�l� aktif edildi
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);  // Port A aktif edildi
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);  // Port C aktif edildi
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);  // Port E aktif edildi


        break;

    case DEVICE_BMS:

        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); // Uart mod�l� aktif edildi
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); // Port A Aktif edildi
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // Port E aktif edildi
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); // Port C aktif edildi
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // ADC0 modul� aktif edildi



        break;


    case DEVICE_MOTOR:

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); // Port C aktif edildi
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // Port E aktif edildi
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // ADC0 modul� aktif edildi
        SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER1); // Pwm �retmek i�in timer aktif edildi

        break;


    }


}

void InitMotorPwm(){

    period = SysCtlClockGet() / (100000/9);

    GPIOPinConfigure(GPIO_PC6_WT1CCP0);
    GPIOPinConfigure(GPIO_PC7_WT1CCP1);
    GPIOPinTypeTimer(GPIO_PORTC_BASE,GPIO_PIN_6 | GPIO_PIN_7);

    TimerConfigure(WTIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM);

    TimerLoadSet(WTIMER1_BASE, TIMER_A, period);
    TimerLoadSet(WTIMER1_BASE, TIMER_B, period);

    TimerEnable(WTIMER1_BASE, TIMER_A);
    TimerEnable(WTIMER1_BASE, TIMER_B);


    //https://sites.google.com/site/luiselectronicprojects/tutorials/tiva-tutorials/tiva-general-purpose-timers/timer-pwm---rgb-led

}


void TimerInit(void)
{

    // Timer 1 sn. ye set edildi
    TimerConfigure(TIMER1_BASE,TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A,SysCtlClockGet());
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER1_BASE,TIMER_A);


}

void
WatchdogInit(void)
{


    // 1 sn. de watchdog kuruldu
    WatchdogReloadSet(WATCHDOG0_BASE,SysCtlClockGet()); // System saati ile set edildi
    WatchdogIntClear(WATCHDOG0_BASE); // Interrupt clear edildi
    WatchdogIntRegister(WATCHDOG0_BASE,WatchdogIntHandler); // Register edildi
    WatchdogIntTypeSet(WATCHDOG0_BASE, WATCHDOG_INT_TYPE_INT); // IntType set edildi
    WatchdogResetEnable(WATCHDOG0_BASE); // Reset enable edildi
    WatchdogIntEnable(WATCHDOG0_BASE); // Interrupt enable edildi
    WatchdogEnable(WATCHDOG0_BASE); // Watchdog enable edildi



}

void InitialConfiguration()
{


    // B�t�n kesmeler aktif edildi
    IntMasterEnable();
    SysTickIntEnable();
    SysTickEnable();
    SysTickDisable();


    if(Device_Address == DEVICE_RPI)
    {

        // Port A conf.
        GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_0); // Rx uart input oldu
        GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_1); // Tx uart output oldu

        //Port C conf.
        GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5); // Speed+ ve Speed- pinleri input edildi
        GPIOIntDisable(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5); // Interrupt disable edildi
        GPIOIntClear(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5); // Interrupt clear edildi
        GPIOIntRegister(GPIO_PORTC_BASE,PortCIntHandler); // Interrupt register edildi
        GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5,GPIO_RISING_EDGE); // Interrupt type set edildi
        GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);  // Interrupt aktif edildi

        // Port E conf. """"""
        GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,GPIO_PIN_2 |  GPIO_PIN_1);  // Deadman ve Fren pinleri input edildi
        GPIOIntDisable(GPIO_PORTE_BASE,GPIO_PIN_1 | GPIO_PIN_2);        // Interrupt disable edildi
        GPIOIntClear(GPIO_PORTE_BASE,GPIO_PIN_1 | GPIO_PIN_2);          // Interrupt clear edildi
        GPIOIntRegister(GPIO_PORTE_BASE,PortEIntHandler);                // Interrupt register edildi
        GPIOIntTypeSet(GPIO_PORTE_BASE,GPIO_PIN_1 | GPIO_PIN_2,GPIO_BOTH_EDGES); // Interrupt type set edildi
        GPIOIntEnable(GPIO_PORTE_BASE,GPIO_PIN_1 | GPIO_PIN_2);     // Interrupt aktif edildi


        UartInit(); // Uart init yap�ld�


    }
    else if(Device_Address == DEVICE_MOTOR)
    {

        // Port C conf.
        GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);  // Motor Pwm pinleri output yap�ld�
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7, 0); // ilk ba�ta 0 pwm versin
        GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);   // Encoder pinleri input yap�ld�( MotorEncoder ve WheelEncoder)

        GPIOIntDisable(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5);  // Encoder pin interrupt disable edildi
        GPIOIntClear(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5); //Encoder pin interrupt clear edildi
        GPIOIntRegister(GPIO_PORTC_BASE,PortCIntHandler); // Encoder pin interrupt register edildi
        GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5,GPIO_RISING_EDGE); // Encoder pin interrupt type set edildi
        GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5); // Encoder pin interrupt enable edildi


        InitMotorPwm(); // Motor Pwm ayarlar� yap�ld�

        ADCInit(DEVICE_MOTOR); // Motor ADC ayarlar� yap�ld�


    }
    else if(Device_Address == DEVICE_BMS)
    {

        // Port E conf.
        GPIOPinTypeGPIOInput(GPIO_PORTE_BASE ,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
        GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

        //Port C
        GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5);

        UartInit(); // Arduino �zerinden data almak i�in uart enable yap�ld�


    }

        // T�m kartlar i�in ortak conf. yap�ld�



        // Port B conf.
        GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_4 );   // Rx Can input oldu
        GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, LED1 | GPIO_PIN_5); // Led ��k��� ve Tx Can outout oldu
        GPIOPadConfigSet(GPIO_PORTB_BASE, LED1 , GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD); // led ��k��� 8ma oldu


        CanInit();
        TimerInit();


}

void LedFlash(bool value)
{

    if(value==false)
        GPIOPinWrite(GPIO_PORTB_BASE, LED1, 0 );
    else
        GPIOPinWrite(GPIO_PORTB_BASE, LED1, LED1 );

}






