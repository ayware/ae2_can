/*
 * GlobalVariables.h
 *
 *  Created on: Jan 23, 2018
 *      Author: s3rkan
 */

#include "GlobalDefines.h"
#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_


uint16_t Register_Uart[UART_DATA_SIZE];
uint16_t Received_Uart_Data[UART_DATA_SIZE];
uint8_t Register_Can[8];
uint8_t Received_Can_Data[8];


uint8_t Device_Address = 0;


uint8_t mosfetHeat1 = 0;
uint8_t mosfetHeat2 = 0;
uint8_t motorControllerHeat1 = 0;
uint8_t motorControllerHeat2 = 0;
uint8_t speedMotor1 = 0;
uint8_t speedMotor2 = 0;

uint32_t period =  0;
float speed = 0;
int statBreak = 0;
int statDeadSwitch = 0;
uint32_t speedEncoder = 0;
uint32_t speedValue = 0;


uint8_t BatteryCurrent1 = 0;
uint8_t BatteryCurrent2 = 0;
uint8_t BatteryVoltage1 = 0;
uint8_t BatteryVoltage2 = 0;
uint8_t BatteryHeat1 = 0;
uint8_t BatteryHeat2 = 0;


uint32_t counter = 0;


bool isRxFlag = 0;
bool isErrFlag = 0;
tCANMsgObject canTxMessage;
tCANMsgObject canRxMessage;
uint8_t *canTxBuffer;
uint8_t *canRxBuffer;
uint8_t canCategory = 0;
uint8_t canAddressTo = 0;
uint8_t canAddressFrom = 0;



bool Uart_Data_received = 0;
uint32_t uartDataCounter = 0;

uint32_t ui32C = 0;
uint32_t lastEncoder = 0;
uint32_t curEncoder = 0;
uint32_t analogValues[4];
uint32_t wheelCounter = 0;
uint32_t mSeconds = 0;

void SysTickIntHandler(void);
void CANIntHandler(void);
void delayUs(uint32_t value);
void delayMs(uint32_t value);
void InitialConfiguration(void);
void CanInit (void);
void CanPacketEvaluate(void);
void CanWrite (uint8_t category,uint8_t fromAddress,uint8_t toAddress,uint8_t *dataAddress);
void UartInit(void);
void UartReceived(void);
void ADCInit(int address);
void GetADCResults (void);
void LedFlash(bool value);
void PortEIntHandler(void);
void PortCIntHandler(void);
void MotorDrive(float speed);
void MotorStop(void);
void TimerTick(void);
void LoopFunction(void);
void CanReceived(void);


#endif /* GLOBALVARIABLES_H_ */





