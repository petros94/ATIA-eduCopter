/*
 * serial.h
 *
 *  Created on: Jul 18, 2017
 *      Author: petros
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "stm32f4xx_hal.h"
#include "diagnostics.h"

typedef enum {
	SERIAL_OK = 0,
	SERIAL_WAIT,
	SERIAL_ERROR
} SerialErrorType;


typedef union{
	uint16_t n;
	enum{
		SERIAL_READ = 0,
		SERIAL_WRITE
	}en;
} SerialMsgType;

typedef struct master_message master_message;

struct master_message {
	SerialMsgType message_header;
	uint16_t motor_1;
	uint16_t motor_2;
	uint16_t motor_3;
	uint16_t motor_4;
};

/*Serial API*/
SerialErrorType listen();
SerialErrorType message_handler(master_message* recv_message);

SerialErrorType readResponse();
SerialErrorType writeResponse(master_message* recv_message);

/*Low level connections to HAL*/
SerialErrorType ReceiveIT(UART_HandleTypeDef* huart, uint8_t* buffer);
SerialErrorType CheckReceive(UART_HandleTypeDef* huart);
SerialErrorType Transmit(UART_HandleTypeDef* huart, uint8_t* new_message);

#endif /* SERIAL_H_ */
