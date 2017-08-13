/*
 * motor_control.c
 *
 *  Created on: Jul 13, 2017
 *      Author: petros mitseas
 */

#include "motor_control.h"
#include "math.h"

extern TIM_HandleTypeDef htim1;

void motor_output(uint16_t MOTOR, uint16_t value){

  /* convert to microseconds (T-ON duration of the pwm pulse)*/
  uint32_t microseconds = (uint32_t)round(0.9*(double)value) + 1100;

  /*saturate output*/
  if (microseconds < 0) microseconds = 0;
  if (microseconds > 1750) microseconds = 1750;

  /* Calculate the value of the output compare register*/
  uint32_t OC_REG = TIMER1_PERIOD * PWM_FREQUENCY / 1e3;
  OC_REG = OC_REG * microseconds / 1e3;

  switch (MOTOR) {
    case 1:
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, OC_REG);
      break;
    case 2:
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, OC_REG);
      break;
    case 3:
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, OC_REG);
      break;
    case 4:
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, OC_REG);
      break;
  }
}
