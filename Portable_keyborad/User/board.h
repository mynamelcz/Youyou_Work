#ifndef __BOARD_H
#define __BOARD_H

//#include "stm32f0xx_hal.h"
struct  __sys_inf{
	unsigned int sys_clk;
};
extern struct __sys_inf sys_inf_g;

#define DBUG_UART						USART2


/*	Device IIC Addr */
#define TC8418_IIC_W_ADDR			0x68		//键盘
#define TC8418_IIC_R_ADDR			0x69

#define ST480MF_IIC_W_ADDR		0x1E		//地磁
#define ST480MF_IIC_R_ADDR		0x1F

#define L3GD20_IIC_W_ADDR			0xD4		//陀螺仪：角速度
#define L3GD20_IIC_R_ADDR			0xD5

#define MMA8653_IIC_W_ADDR		0x3A		//加速度：g sensor
#define MMA8653_IIC_R_ADDR		0x3B


/*	LED	*/
#define KEY_TEST_LED_PORT		GPIOA
#define KEY_TEST_LED_PIN		GPIO_PIN_6

#define	RGB_TEST_LED_PORT		GPIOA
#define	RGB_TEST_LED_PIN		GPIO_PIN_7

#define	MMA_TEST_LED_PORT		GPIOB
#define	MMA_TEST_LED_PIN		GPIO_PIN_0

#define GYR_TEST_LED_PORT		GPIOB
#define GYR_TEST_LED_PIN		GPIO_PIN_1

#define KEY_BORAD_LED_PORT  GPIOA
#define KEY_BORAD_LED_PIN 	GPIO_PIN_12

/* IO KEY  */
#define KEY_TEST_KEY_PORT		GPIOC
#define KEY_TEST_KEY_PIN		GPIO_PIN_15

#define	RGB_TEST_KEY_PORT		GPIOC
#define	RGB_TEST_KEY_PIN		GPIO_PIN_13

#define	MMA_TEST_KEY_PORT		GPIOC
#define	MMA_TEST_KEY_PIN		GPIO_PIN_14

#define GYR_TEST_KEY_PORT		GPIOA
#define GYR_TEST_KEY_PIN		GPIO_PIN_8

#define VOL_DEC_KEY_PORT  	GPIOA
#define VOL_DEC_KEY_PIN 		GPIO_PIN_9


/* SGM2032 */
#define SGM_1V8_EN_PORT			GPIOA
#define	SGM_1V8_EN_PIN			GPIO_PIN_15
	




































#endif





