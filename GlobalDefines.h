/*
 * GlobalDefines.h
 *
 *  Created on: 8 May 2015
 *      Author: arge16
 */

#ifndef GLOBALDEFINES_H_
#define GLOBALDEFINES_H_

#define LED1    GPIO_PIN_2	//Port B

#define SW1	GPIO_PIN_0	//Port D
#define SW2	GPIO_PIN_1	//Port D
#define SW3	GPIO_PIN_2	//Port D
#define SW4	GPIO_PIN_3	//Port D


#define ACK 0x55
#define NACK 0xAA
#define COMMAND_STOP 0x00
#define COMMAND_SPEED 0x01
#define COMMAND_CHECK 0x02

#define DEVICE_MOTOR 0x00
#define DEVICE_RPI  0x01
#define DEVICE_BMS 0x03

#define UART_DATA_SIZE 30
#define DELAY_CAN_WRITE 3
#define CAN_RX_OBJECT_ID 1
#define CAN_TX_OBJECT_ID 2

#define SPEED_VALUE_LIMIT 10
#define SPEED_MAX 35


enum COMMAND
{

    COMMAND_DATA_CHECKER


};


enum COMMAND_TYPE
{

    COMMAND_TYPE_DATA_REQUEST,
    COMMAND_TYPE_DATA_RESPONSE

};


#endif /* GLOBALDEFINES_H_ */
