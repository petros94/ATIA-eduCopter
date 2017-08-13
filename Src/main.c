#include <Quadcopter_Settings.h>
#include "stm32f4xx_hal.h"
#include "HW_Init.h"
#include "motor_control.h"
#include "sensors.h"
#include "diagnostics.h"
#include "serial.h"

SD_MPU6050 mpu1;

/***************** Control System variables ******************/

//Analog inputs - Free to use as you wish

__IO uint32_t input_1;
__IO uint32_t input_2;
__IO uint32_t input_3;
__IO uint32_t input_4;


//Motor power - set to 0 for motor off, 1000 for full power. This
// is the plant's input.

uint16_t motor_1_power;
uint16_t motor_2_power;
uint16_t motor_3_power;
uint16_t motor_4_power;

//
/*************************************************************/


int main(void)
{

  hw_init();

  SerialErrorType listen_status;


  while (1)
  {
	/*After initializations, listen() is called*/
	listen_status = listen();

//	/*LED to indicate traffic*/
//	if (listen_status == SERIAL_OK) HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	/*Re-enable timer 3 interrupt*/
	NVIC_EnableIRQ(TIM3_IRQn);
  }
}

void HardFault_Handler(void)
{
   motor_output(MOTOR_1, 0);
   motor_output(MOTOR_2, 0);
   motor_output(MOTOR_3, 0);
   motor_output(MOTOR_4, 0);
   while(1);
}
