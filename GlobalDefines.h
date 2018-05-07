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


#define PWM1 GPIO_PIN_7  //Port C
#define PWM2 GPIO_PIN_6  //Port C
#define INA GPIO_PIN_5  //Port C
#define INB GPIO_PIN_4  //Port C


#define ACK 0x55
#define NACK 0xAA
#define CATEGORY_STOP 0x00
#define CATEGORY_SPEED 0x01
#define CATEGORY_CHECK 0x02

#define DEVICE_MOTOR 0x00
#define DEVICE_RPI  0x01
#define DEVICE_BMS 0x03

#define UART_DATA_SIZE 30
#define DELAY_CAN_WRITE 3
#define CAN_RX_OBJECT_ID 1
#define CAN_TX_OBJECT_ID 2
#define SPEED_LIMIT 10



#endif /* GLOBALDEFINES_H_ */
