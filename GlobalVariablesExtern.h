/*
 * GlobalVariablesExtern.h
 *
 *  Created on: Jan 23, 2018
 *      Author: s3rkan
 */

#include "GlobalDefines.h"
#ifndef GLOBALVARIABLESEXTERN_H_
#define GLOBALVARIABLESEXTERN_H_


extern uint8_t Register_Uart[UART_DATA_SIZE];
extern uint8_t Received_Uart_Data[UART_DATA_SIZE];
extern uint8_t Register_Can[8];
extern uint8_t Received_Can_Data[8];
extern uint8_t UartPrefix[4];

extern uint8_t Device_Address;


extern uint8_t mosfetHeat1;
extern uint8_t mosfetHeat2;
extern uint8_t motorControllerHeat1;
extern uint8_t motorControllerHeat2;
extern float speedMotor;
extern float speedWheel;

extern uint32_t period;
extern float speed;
extern int statBreak;
extern int statDeadSwitch;
extern uint32_t motorEncoder;
extern uint32_t wheelEncoder;
extern uint32_t wheelEncoder;

extern uint32_t speedValue;
extern uint32_t maxSpeed;
extern uint32_t minSpeed;
extern float errSpeed;
extern float speedResult;

extern uint8_t batteryCurrent1;
extern uint8_t batteryCurrent2;

extern uint8_t batteryVoltage1;
extern uint8_t batteryVoltage2;

extern uint8_t batteryHeat1;
extern uint8_t batteryHeat2;

extern uint32_t counter;

extern uint32_t crc;


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
extern uint32_t loopCounter;
extern float mVoltage;

extern uint32_t ui32C;
extern uint32_t lastMotorEncoder;
extern uint32_t lastWheelEncoder;
extern uint32_t curWheelEncoder;
extern uint32_t curMotorEncoder;
extern uint32_t analogValues[4];
extern uint32_t mSeconds;
extern bool clearWatchdog;

extern void SysTickIntHandler(void);
extern void CANIntHandler(void);
extern void InitialConfiguration(void);
extern void CanInit (void);
extern void CanWrite (uint8_t category,uint8_t fromAddress,uint8_t toAddress,uint8_t *dataAddress);
extern void UartInit(void);
extern void ADCInit(int address);
extern void GetADCResults (void);
extern void PortEIntHandler(void);
extern void PortCIntHandler(void);
extern void MotorDrive(float speed);
extern void MotorStop(void);
extern void TimerTick(void);
extern void LoopFunction(void);
extern void CanReceived(void);
extern void WatchdogIntHandler(void);
extern int SpeedControl(void);
extern int CrcCalc(uint8_t *data,uint32_t length);


#endif /* GLOBALVARIABLESEXTERN_H_ */
