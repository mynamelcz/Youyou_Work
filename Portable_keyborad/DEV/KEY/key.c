#include "key.h"
#include "includes.h"
#include "stm32f0xx_hal.h"

enum KEY_ID{
	KEY_TEST_KEY_ID,
	RGB_TEST_KEY_ID,
	MMA_TEST_KEY_ID,
	GYR_TEST_KEY_ID,
	VOL_DEC_KEY_ID,
	KEY_MAX_ID,
};

u8 get_key_id(void)
{
	if(HAL_GPIO_ReadPin(KEY_TEST_KEY_PORT, KEY_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	KEY_TEST_KEY_ID;
	}else if(HAL_GPIO_ReadPin(RGB_TEST_KEY_PORT, RGB_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	RGB_TEST_KEY_ID;
	}else if(HAL_GPIO_ReadPin(MMA_TEST_KEY_PORT, MMA_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	MMA_TEST_KEY_ID;
	}else if(HAL_GPIO_ReadPin(GYR_TEST_KEY_PORT, GYR_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	GYR_TEST_KEY_ID;
	}else if(HAL_GPIO_ReadPin(VOL_DEC_KEY_PORT, VOL_DEC_KEY_PIN) == GPIO_PIN_RESET){
		return	VOL_DEC_KEY_ID;
	}else{
		return	0xFF;
	}
}








