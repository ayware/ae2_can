/*
 * CAN_Function.c
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




void CanInit (void)
{
	//CAN Settings

	GPIOPinConfigure(GPIO_PB4_CAN0RX); // can çýkýþlarýný b portuna yönlendiriyor
	GPIOPinConfigure(GPIO_PB5_CAN0TX); // can çýkýþlarýný b portuna yönlendiriyor

	GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5); // can çýkýþlarýný b portuna yönlendiriyor

    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0); // can çýkýþlarýný aktif ediyor.

    CANInit(CAN0_BASE); // Can0 modülünü kullanýdýðýný belli ediyor

	//CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000); // can modülüne clock hýzý ve haberleþme hýzý veriliyor
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS); // can kesmesi aktif edildi
    IntEnable(INT_CAN0); // genel kesme aktif edildi
    CANEnable(CAN0_BASE); // Can modülünü aktif ediyor

    canRxMessage.ui32MsgID = 0;
    canRxMessage.ui32MsgIDMask = 0;
    canRxMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    canRxMessage.ui32MsgLen = 8;
    canRxMessage.pui8MsgData = canRxBuffer;

	CANMessageSet(CAN0_BASE, CAN_RX_OBJECT_ID, &canRxMessage, MSG_OBJ_TYPE_RX); // Can receive paketini ayarlýyorsun


}


void
CANIntHandler(void)
{
    uint32_t canStatus;

    canStatus = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    if(canStatus == CAN_INT_INTID_STATUS)
    {
        canStatus = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        isErrFlag = 1;
        isRxFlag = 0;

    }
    else if(canStatus == 1)
    {

        isErrFlag = 0;
        isRxFlag = 1;

        canRxMessage.pui8MsgData = (uint8_t *)&Received_Can_Data[0];
        CANMessageGet(CAN0_BASE,CAN_RX_OBJECT_ID, &canRxMessage, 0);

        canCategory = canRxMessage.ui32MsgID >> 16;
        canAddressFrom = (canRxMessage.ui32MsgID >> 8) & 0x00000007;
        canAddressTo = (canRxMessage.ui32MsgID) & 0x000000FF;

        if(canAddressTo == Device_Address)
            CanReceived();


    }

    else if(canStatus == 2)
    {
        isErrFlag = 0;


    }
    else
    {

        isErrFlag = 0;

    }

    CANIntClear(CAN0_BASE, canStatus); // clear interrupt

}


void CanReceived()
{


    // ---------- MOTOR ----------------
    if(canAddressTo == DEVICE_MOTOR)
    {

        if(canAddressFrom == DEVICE_RPI)
        {

                if(canCategory == COMMAND_CHECK)
                {


                    Register_Can[0] = speedMotor;
                    Register_Can[1] = speedWheel;
                    Register_Can[2] = motorControllerHeat1;
                    Register_Can[3] = motorControllerHeat1;
                    Register_Can[4] = mosfetHeat1;
                    Register_Can[5] = mosfetHeat2;
                    Register_Can[6] = 0;
                    Register_Can[7] = 0;

                    CanWrite(COMMAND_CHECK, DEVICE_MOTOR, DEVICE_RPI, &Register_Can[0]);

                }
                else if(canCategory == COMMAND_SPEED)
                {

                    statBreak = Received_Can_Data[0];
                    statDeadSwitch = Received_Can_Data[1];
                    speedValue = Received_Can_Data[2];

                    speed = period*speedValue/SPEED_VALUE_LIMIT;

                    if(speed == period)
                        speed = period - 1;
                    else if(speed == 0)
                        speed = 1;

                }

        }

    }
    // ---------- BMS ----------------
    else if(canAddressTo == DEVICE_BMS)
    {


        if(canAddressFrom == DEVICE_RPI)
        {


            if(canCategory == COMMAND_CHECK)
            {

                Register_Can[0] = batteryCurrent1;
                Register_Can[1] = batteryCurrent2;
                Register_Can[2] = batteryVoltage1;
                Register_Can[3] = batteryVoltage2;
                Register_Can[4] = batteryHeat1;
                Register_Can[5] = batteryHeat2;
                Register_Can[6] = 0;
                Register_Can[7] = 0;

                CanWrite(COMMAND_CHECK, DEVICE_BMS, DEVICE_RPI, &Register_Can[0]);


            }


        }

    }
    // ---------- RPI ----------------
    else if(canAddressTo == DEVICE_RPI)
    {


        if(canAddressFrom == DEVICE_MOTOR)
        {

            if(canCategory == COMMAND_CHECK)
            {

                Register_Uart[0] = Received_Can_Data[0]; // speedMotor
                Register_Uart[1] = Received_Can_Data[1]; // speedWheel
                Register_Uart[2] = Received_Can_Data[2]; // motorControllerHeat1
                Register_Uart[3] = Received_Can_Data[3]; // motorControllerHeat2
                Register_Uart[4] = Received_Can_Data[4]; // mosfetHeat1
                Register_Uart[5] = Received_Can_Data[5]; // mosfetHeat2
                Register_Uart[6] = Received_Can_Data[6]; // -
                Register_Uart[7] = Received_Can_Data[7]; // -

                Register_Uart[8] = 1; // Cihaz baðlý bilgisi

            }


        }
        else if(canAddressFrom == DEVICE_BMS)
        {

                Register_Uart[9]  = Received_Can_Data[0]; // batteryCurrent1
                Register_Uart[10] = Received_Can_Data[1]; // batteryCurrent2
                Register_Uart[11] = Received_Can_Data[2]; // batteryVoltage1
                Register_Uart[12] = Received_Can_Data[3]; // batteryVoltage2
                Register_Uart[13] = Received_Can_Data[4]; // batteryHeat1
                Register_Uart[14] = Received_Can_Data[5]; // batteryHeat2
                Register_Uart[15] = Received_Can_Data[6]; // -
                Register_Uart[16] = Received_Can_Data[7]; // -

                Register_Uart[17] = 1; // Cihaz baðlý bilgisi

        }


    }

    // --------------------------------------------------







}





void CanWrite (uint8_t command,uint8_t fromAddress,uint8_t toAddress,uint8_t *dataAddress)
{

	volatile uint32_t id = 0;

	id = command;
	id = id << 8;
	id |= fromAddress;
	id = id << 8;
	id |= toAddress;

	canTxMessage.ui32MsgID = id;
	canTxMessage.ui32MsgIDMask = 0;
	canTxMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
	canTxMessage.ui32MsgLen = 8;
	canTxMessage.pui8MsgData = dataAddress;

	CANMessageSet(CAN0_BASE, CAN_TX_OBJECT_ID, &canTxMessage, MSG_OBJ_TYPE_TX);
	SysCtlDelay(DELAY_CAN_WRITE);


}







