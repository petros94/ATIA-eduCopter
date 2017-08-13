/*
 * serial.c
 *
 *  Created on: Jul 18, 2017
 *      Author: petros
 */


#include "serial.h"
#include "sensors.h"
#include "motor_control.h"

extern UART_HandleTypeDef huart2;
extern SD_MPU6050 mpu1;
extern State quad_state;
uint32_t tick;

extern __IO uint32_t input_1;
extern __IO uint32_t input_2;
extern __IO uint32_t input_3;
extern __IO uint32_t input_4;

/* Low Level functions*/

SerialErrorType ReceiveIT(UART_HandleTypeDef* huart, uint8_t* buffer)
{
	HAL_UART_Receive_IT(huart, buffer, sizeof(master_message));
	return SERIAL_OK;
}

SerialErrorType CheckReceive(UART_HandleTypeDef* huart)
{
	return (HAL_UART_GetState(huart) == HAL_UART_STATE_READY ? SERIAL_OK : SERIAL_WAIT);
}

SerialErrorType Transmit(UART_HandleTypeDef* huart, uint8_t* buffer)
{
	HAL_UART_Transmit(huart, buffer, sizeof(serial_message), 4);
	return SERIAL_OK;
}


/*API*/

SerialErrorType listen()
{
	uint8_t rxbuffer[sizeof(master_message)];
	ReceiveIT(&huart2, rxbuffer);
	uint32_t safety_timer= HAL_GetTick();

	while(CheckReceive(&huart2) != SERIAL_OK)
	{
		/* Get data from MPU6050 sensor*/
		SensorErrorType status = MPU6050_getData();

		/*If MPU stops working, cut off power*/
		while (status == SENSOR_ERROR)
		{
			motor_output(MOTOR_1, 0);
			motor_output(MOTOR_2, 0);
			motor_output(MOTOR_3, 0);
			motor_output(MOTOR_4, 0);

			status = MPU6050_getData();
		}

		/*Update Kalman filter*/
		float T = (HAL_GetTick() - tick)*0.001;
		updateState(mpu1.rpy[0], mpu1.Gyroscope_X_conv, mpu1.rpy[1], mpu1.Gyroscope_Y_conv, mpu1.Gyroscope_Z_conv, T);
		tick = HAL_GetTick();

		if (status != SENSOR_OK) HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

		/*If the user's application does not send data within 2 seconds,
		 * shut off the motors.
		 */
		if (HAL_GetTick() - safety_timer > 2000)
		{
			motor_output(MOTOR_1, 0);
			motor_output(MOTOR_2, 0);
			motor_output(MOTOR_3, 0);
			motor_output(MOTOR_4, 0);
		}
	}

	/*Update safety timer*/
	safety_timer = HAL_GetTick();

	/*Disable timer 3 interrupt*/
	NVIC_DisableIRQ(TIM3_IRQn);

	master_message recv_msg = *(master_message*)rxbuffer;
	return message_handler(&recv_msg);
}


SerialErrorType message_handler(master_message* recv_message)
{
	if (recv_message->message_header.en == SERIAL_READ)
	{
		return readResponse();
	}
	else if (recv_message->message_header.en == SERIAL_WRITE)
	{
		return writeResponse(recv_message);
	}
	else return SERIAL_ERROR;
}


SerialErrorType readResponse()
{

	serial_message new_message;

	new_message.MPUData[0] = quad_state.roll;
	new_message.MPUData[1] = quad_state.pitch;
	new_message.MPUData[2] = quad_state.yaw;
	new_message.MPUData[3] = quad_state.gyro_roll;
	new_message.MPUData[4] = quad_state.gyro_pitch;
	new_message.MPUData[5] = quad_state.gyro_yaw;

	new_message.inputs[0] = input_1;
	new_message.inputs[1] = input_2;
	new_message.inputs[2] = input_3;
	new_message.inputs[3] = input_4;

	return Transmit(&huart2, (uint8_t*)&new_message);
}


SerialErrorType writeResponse(master_message* recv_message)
{
  	/* Output desired power to motors */
    motor_output(MOTOR_1, recv_message->motor_1);
    motor_output(MOTOR_2, recv_message->motor_2);
    motor_output(MOTOR_3, recv_message->motor_3);
    motor_output(MOTOR_4, recv_message->motor_4);

    return SERIAL_OK;
}


