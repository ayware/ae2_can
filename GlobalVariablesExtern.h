/*
 * GlobalVariablesExtern.h
 *
 *  Created on: Jan 23, 2018
 *      Author: s3rkan
 */

#include "GlobalDefines.h"
#ifndef GLOBALVARIABLESEXTERN_H_
#define GLOBALVARIABLESEXTERN_H_


extern uint16_t Register_Uart[UART_DATA_SIZE];
extern uint16_t Received_Uart_Data[UART_DATA_SIZE];
extern uint8_t Register_Can[8];
extern uint8_t Received_Can_Data[8];


extern uint8_t Device_Address;


extern uint8_t mosfetHeat1;
extern uint8_t mosfetHeat2;
extern uint8_t motorControllerHeat1;
extern uint8_t motorControllerHeat2;
extern uint8_t speedMotor1;
extern uint8_t speedMotor2;

extern uint32_t period;
extern float speed;
extern int statBreak;
extern int statDeadSwitch;
extern uint32_t speedEncoder;
extern uint32_t speedValue;


extern uint8_t BatteryCurrent1;
extern uint8_t BatteryCurrent2;
extern uint8_t BatteryVoltage1;
extern uint8_t BatteryVoltage2;
extern uint8_t BatteryHeat1;
extern uint8_t BatteryHeat2;


extern uint32_t counter;


extern bool isRxFlag;
extern bool isErrFlag;
extern tCANMsgObject canTxMessage;
extern tCANMsgObject canRxMessage;
extern uint8_t *canTxBuffer;
extern uint8_t *canRxBuffer;
extern uint8_t canCategory;
extern uint8_t canAddressTo;
extern uint8_t canAddressFrom;



extern bool Uart_Data_received;
extern uint32_t uartDataCounter;

extern uint32_t ui32C;
extern uint32_t lastEncoder;
extern uint32_t curEncoder;
extern uint32_t analogValues[4];
extern uint32_t wheelCounter;
extern uint32_t mSeconds;

extern void SysTickIntHandler(void);
extern void CANIntHandler(void);
extern void delayUs(uint32_t value);
extern void delayMs(uint32_t value);
extern void InitialConfiguration(void);
extern void CanInit (void);
extern void CanPacketEvaluate(void);
extern void CanWrite (uint8_t category,uint8_t fromAddress,uint8_t toAddress,uint8_t *dataAddress);
extern void UartInit(void);
extern void UartReceived(void);
extern void ADCInit(int address);
extern void GetADCResults (void);
extern void LedFlash(bool value);
extern void PortEIntHandler(void);
extern void PortCIntHandler(void);
extern void MotorDrive(float speed);
extern void MotorStop(void);
extern void TimerTick(void);
extern void LoopFunction(void);
extern void CanReceived(void);


#endif /* GLOBALVARIABLESEXTERN_H_ */
