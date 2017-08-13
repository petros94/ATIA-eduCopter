/*
 * motor_control.h
 *
 *  Created on: Jul 13, 2017
 *      Author: petros mitseas
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <Quadcopter_Settings.h>
#include "stm32f4xx_hal.h"

/* Motor parameter to be passed as an argument*/
#define MOTOR_1 0x00000001U
#define MOTOR_2 0x00000002U
#define MOTOR_3 0x00000003U
#define MOTOR_4 0x00000004U


/**
 * motor_output: Controls a motor's speed.
 * @param MOTOR: parameter is MOTOR_x, where x = 1...4.
 * @param value: 0 ~ 1000, where 0 is motor off, and 1000 makes motor rotate at full speed.
 */
void motor_output(uint16_t MOTOR, uint16_t value);



#endif /* MOTOR_CONTROL_H_ */
