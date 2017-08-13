/*
 * sensors.h
 *
 *  Created on: Jul 16, 2017
 *      Author: petros
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include "mpu6050.h"
#include "Kalman.h"

/*Interface for getting sensor values. Feel free to modify as you wish.
 */

typedef enum {
	SENSOR_OK = 0,
	SENSOR_ERROR,
} SensorErrorType;

typedef struct {
	/*Filter variables*/
	Kalman roll_filter;
	Kalman pitch_filter;

	/*filtered data*/
	float roll;
	float pitch;
	float yaw;
	float gyro_roll;
	float gyro_pitch;
	float gyro_yaw;
} State;

void initState();
void updateState(float new_roll, float new_gyro_roll, float new_pitch, float new_gyro_pitch, float new_gyro_yaw, float dt);

SensorErrorType MPU6050_getData();

#endif /* SENSORS_H_ */
