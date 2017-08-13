/*
 * sensors.c
 *
 *  Created on: Jul 16, 2017
 *      Author: petros
 */


#include "sensors.h"
#include "math.h"

extern SD_MPU6050 mpu1;
extern I2C_HandleTypeDef hi2c1;
extern uint32_t tick;


State quad_state;

/************************Quadcopter State variables******************************/

/*initialize state variables*/
void initState()
{
	quad_state.pitch=0;
	quad_state.roll=0;
	quad_state.yaw=0;
	quad_state.gyro_pitch=0;
	quad_state.gyro_roll=0;
	quad_state.gyro_yaw=0;

	initKalman(&(quad_state.roll_filter));
	initKalman(&(quad_state.pitch_filter));
}

/*Update variables*/
void updateState(float new_roll, float new_gyro_roll, float new_pitch, float new_gyro_pitch, float new_gyro_yaw, float dt)
{
	/*Update roll*/
	float temp_roll = quad_state.roll;
	quad_state.roll = getAngle(&(quad_state.roll_filter), new_roll, new_gyro_roll, dt);

	/*Update pitch*/
	float temp_pitch = quad_state.pitch;
	quad_state.pitch = getAngle(&(quad_state.pitch_filter), new_pitch, new_gyro_pitch, dt);

	/*Update yaw*/
	quad_state.yaw += new_gyro_yaw*dt;

	/*Update angular speeds*/
	if (dt>0)
	{
		quad_state.gyro_roll = 0.5*quad_state.gyro_roll + 0.5*(quad_state.roll - temp_roll)/dt;
		quad_state.gyro_pitch = 0.5*quad_state.gyro_pitch + 0.5*(quad_state.pitch - temp_pitch)/dt;
		quad_state.gyro_yaw = new_gyro_yaw;

	}
}


/*************************MPU 6050*********************************/

SensorErrorType MPU6050_getData(){

	SD_MPU6050_Result result = SD_MPU6050_Result_Ok;
	if (HAL_GPIO_ReadPin(MPU6050_PORT, MPU6050_INT_PIN) == GPIO_PIN_SET)
		{
			result = SD_MPU6050_ReadAll(&hi2c1, &mpu1);
			if (result != SD_MPU6050_Result_Ok) return SENSOR_ERROR;

			/* Convert values to real values */
			mpu1.Accelerometer_X_conv = 0.00059855041*mpu1.Accelerometer_X;
			mpu1.Accelerometer_Y_conv = 0.00059855041*mpu1.Accelerometer_Y;
			mpu1.Accelerometer_Z_conv = 0.00059855041*mpu1.Accelerometer_Z;

			mpu1.Gyroscope_X_conv = (0.00026630827*mpu1.Gyroscope_X);
			mpu1.Gyroscope_Y_conv = (-0.00026630827*mpu1.Gyroscope_Y);
			mpu1.Gyroscope_Z_conv = -0.00026630827*mpu1.Gyroscope_Z;


			float T = (HAL_GetTick()- tick)*0.001;

			/*Get angles from accelerometer*/
			mpu1.rpy[1] = atan2((float)(-mpu1.Accelerometer_X), (float)(mpu1.Accelerometer_Z));
			mpu1.rpy[0] = atan2((float)(mpu1.Accelerometer_Y), (float)(mpu1.Accelerometer_Z));
			mpu1.rpy[2] = mpu1.rpy[2]+ mpu1.Gyroscope_Z_conv*T;

			/*Rotate to get euler angle velocity*/
//			mpu1.Gyroscope_X_conv = 0.00026630827*mpu1.Gyroscope_X
//					-0.00026630827*mpu1.Gyroscope_Y*tan(mpu1.rpy[1])*sin(mpu1.rpy[0])
//					-0.00026630827*mpu1.Gyroscope_Z*tan(mpu1.rpy[1])*cos(mpu1.rpy[0]);
//
//			mpu1.Gyroscope_Y_conv = -0.00026630827*mpu1.Gyroscope_Y*cos(mpu1.rpy[0]) +
//					0.00026630827*mpu1.Gyroscope_Z*sin(mpu1.rpy[0]);
//
//			mpu1.Gyroscope_Z_conv = -0.00026630827*mpu1.Gyroscope_Y*sin(mpu1.rpy[0])/cos(mpu1.rpy[1]) +
//					0.00026630827*mpu1.Gyroscope_Z*cos(mpu1.rpy[0])/cos(mpu1.rpy[1]);

			return SENSOR_OK;

		}
	else return SENSOR_OK;
}

