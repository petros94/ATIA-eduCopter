/*
 * diagnostics.c
 *
 *  Created on: Jul 15, 2017
 *      Author: petros mitseas
 */

#include "diagnostics.h"
#include "mpu6050.h"

uint32_t diagnostics_timer;

extern UART_HandleTypeDef huart2;

extern SD_MPU6050 mpu1;


void sendDiagnostics(uint32_t* inputs)
{
	if (HAL_GetTick() - diagnostics_timer > 10 )
	{
		/* Create message*/
		serial_message new_message;

		new_message.MPUData[0] = mpu1.Gyroscope_X;
		new_message.MPUData[1] = mpu1.Gyroscope_Y;
		new_message.MPUData[2] = mpu1.Gyroscope_Z;
		new_message.MPUData[3] = mpu1.Accelerometer_X;
		new_message.MPUData[4] = mpu1.Accelerometer_Y;
		new_message.MPUData[5] = mpu1.Accelerometer_Z;

		new_message.inputs[0] = 0;
		new_message.inputs[1] = 0;
		new_message.inputs[2] = 0;
		new_message.inputs[3] = 0;

		for (int i=0; i<4; i++)
		{
			new_message.inputs[i] = 255;//inputs[i];
		}

		/* Enter Critical region - Transmit mustn't be interrupted*/
		NVIC_DisableIRQ(TIM3_IRQn);

		/*Send through UART*/
		HAL_UART_Transmit(&huart2, (uint8_t*)&new_message, sizeof(serial_message), 5);

		/* Exit region*/
		NVIC_EnableIRQ(TIM3_IRQn);

		/*Reset counter*/
		diagnostics_timer=HAL_GetTick();
	}
}
