/*
 * diagnostics.h
 *
 *  Created on: Jul 15, 2017
 *      Author: petros mitseas
 */

#ifndef DIAGNOSTICS_H_
#define DIAGNOSTICS_H_

#include "stm32f4xx_hal.h"

typedef struct {
	float MPUData[6];
	uint32_t inputs[4];
} serial_message;

void sendDiagnostics(uint32_t* inputs);


#endif /* DIAGNOSTICS_H_ */
