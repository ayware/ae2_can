/*
 * GlobalVariables.h
 *
 *  Created on: Jan 23, 2018
 *      Author: s3rkan
 */

#include "GlobalDefines.h"
#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_


uint8_t Register_Uart[UART_DATA_SIZE];
uint8_t Received_Uart_Data[UART_DATA_SIZE];
uint8_t Register_Can[8];
uint8_t Received_Can_Data[8];
uint8_t UartPrefix[4];


uint8_t Device_Address = 0;


uint8_t mosfetHeat1 = 0;
uint8_t mosfetHeat2 = 0;
uint8_t motorControllerHeat1 = 0;
uint8_t motorControllerHeat2 = 0;
float speedMotor = 0;
float speedWheel = 0;

uint32_t period =  0;
float speed = 0;
int statBreak = 0;
int statDeadSwitch = 0;
uint32_t motorEncoder = 0;
uint32_t wheelEncoder = 0;

uint32_t speedValue = 0;
uint32_t maxSpeed = 0;
uint32_t minSpeed = 0;
float errSpeed = 0;
float speedResult = 0;


uint8_t batteryCurrent1 = 0;
uint8_t batteryCurrent2 = 0;

uint8_t batteryVoltage1 = 0;
uint8_t batteryVoltage2 = 0;

uint8_t batteryHeat1 = 0;
uint8_t batteryHeat2 = 0;

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
uint32_t loopCounter = 0;
float mVoltage = 13/870; // 870/13

uint32_t ui32C = 0;
uint32_t lastMotorEncoder = 0;
uint32_t lastWheelEncoder = 0;
uint32_t curWheelEncoder = 0;
uint32_t curMotorEncoder = 0;
uint32_t analogValues[4];

uint32_t mSeconds = 0;
bool clearWatchdog = false;


uint32_t crc = 0;

void SysTickIntHandler(void);
void CANIntHandler(void);
void InitialConfiguration(void);
void CanInit (void);
void CanWrite (uint8_t category,uint8_t fromAddress,uint8_t toAddress,uint8_t *dataAddress);
void UartInit(void);
void ADCInit(int address);
void GetADCResults (void);
void PortEIntHandler(void);
void PortCIntHandler(void);
void MotorDrive(float speed);
void MotorStop(void);
void TimerTick(void);
void LoopFunction(void);
void CanReceived(void);
void WatchdogIntHandler(void);
int SpeedControl(void);
int CrcCalc(uint8_t *data,uint32_t length);
#endif /* GLOBALVARIABLES_H_ */





