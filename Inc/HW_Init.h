/*
 * HW_Init.h
 *
 *  Created on: Jul 13, 2017
 *      Author: petros mitseas
 */

#include <Quadcopter_Settings.h>
#include "stm32f4xx_hal.h"
#include "sensors.h"
#include "motor_control.h"

/* Function to initalize low level periherals (system clock, uart, timers, pwm,
 * adc...)
 */
void hw_init();

/* These function are called by hw_init() */
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);
void MX_TIM1_Init(void);
void MX_TIM3_Init(void);
void MX_ADC1_Init(void);
void MX_USART2_UART_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
