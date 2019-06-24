#include "timer.h"
#include "stm32f0xx_hal.h"
#include "includes.h"




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static u16 timer1_cnt = 0;
	if(htim->Instance == TIM1){
		if(timer1_cnt++ == 1000){
			timer1_cnt = 0;
			app_printf("timer1\n");
		}
	}

}




