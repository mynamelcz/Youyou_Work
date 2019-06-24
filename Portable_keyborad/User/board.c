#include "board.h"
#include "stm32f0xx_hal.h"
#include "includes.h"

u8  get_cpu_reset_source(void)
{
	uint8_t ret = 0;
	if(__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST)){
		ret =	1;
	}
  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST)){
		ret =	2;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)){
		ret =	3;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)){
		ret =	4;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST)){
		ret =	5;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST)){
		ret =	6;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_OBLRST)){
		ret =	7;
	}else{}
	__HAL_RCC_CLEAR_RESET_FLAGS();
	return ret;
}


















