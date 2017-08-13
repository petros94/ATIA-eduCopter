#ifndef __MAIN_H
#define __MAIN_H


#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define P_GAIN_Pin GPIO_PIN_0
#define P_GAIN_GPIO_Port GPIOA
#define I_GAIN_Pin GPIO_PIN_1
#define I_GAIN_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define INPUT_Pin GPIO_PIN_0
#define INPUT_GPIO_Port GPIOB
#define INPUT_2_Pin GPIO_PIN_7
#define INPUT_2_GPIO_PORT GPIOA
#define MOTOR1_Pin GPIO_PIN_8
#define MOTOR1_GPIO_Port GPIOA
#define MOTOR2_Pin GPIO_PIN_9
#define MOTOR2_GPIO_Port GPIOA
#define MOTOR3_Pin GPIO_PIN_10
#define MOTOR3_GPIO_Port GPIOA
#define MOTOR4_Pin GPIO_PIN_11
#define MOTOR4_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

#define MPU6050_INT_PIN GPIO_PIN_4
#define MPU6050_POWER_PIN GPIO_PIN_5
#define MPU6050_PORT GPIOB


#define SYSTEM_CLOCK 84000000


/************************ PWM Settings******************************/

/* Configures PWM frequency*/
#define PWM_FREQUENCY 300 //Hz

#define TIMER1_PERIOD 0x2710     // Formula to calculate prescaller and period:
#define TIMER1_PRESCALLER 28     //TIMER1_PRESCALLER * TIMER1_PERIOD = SYSTEM_CLOCK / PWM_FREQUENCY


/******************** Data Aquisition Settings *****************/

/*Configures how often the quadcopter sends telemetry data to the serial port*/
#define SERIAL_FREQUENCY 100 //Hz

#define TIMER3_PERIOD 0x6D60
#define TIMER3_PRESCALLER 30


void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

#endif /* __MAIN_H */
