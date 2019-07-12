#include "timer.h"
#include "stm32f0xx_hal.h"
#include "includes.h"
#include "stdlib.h"

extern TIM_HandleTypeDef htim1;

#define IRQ_HdlList(fun, time)	&(fun##irq.list)
#define IRQ_Hdl(fun)	    	&(fun##irq)	


LIST_HEAD(TIM1_IRQHandler_ListHead);
	
void register_timer1_handler(__irq_hd_t *hd_t)
{	
	HAL_TIM_Base_Stop_IT(&htim1);
	list_add_tail(&hd_t->list, &TIM1_IRQHandler_ListHead);		
	HAL_TIM_Base_Start_IT(&htim1);
}	
	
void register_timer1_handler_malloc(void(*fun)(void), u32 time)
{
	__irq_hd_t *hd_t = malloc(sizeof(__irq_hd_t));
	ASSERT(hd_t);
	hd_t->cnt = 0;
	hd_t->time = time;
	hd_t->hdl_fun = fun;
	hd_t->list.next = &(hd_t->list);
	hd_t->list.prev = &(hd_t->list);
	
	register_timer1_handler(hd_t);
//	list_add_tail(&hd_t->list, &TIM1_IRQHandler_ListHead);	
}	
	





void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	__irq_hd_t *pos = NULL;
	if(htim->Instance == TIM1){
		list_for_each_entry(pos, &TIM1_IRQHandler_ListHead, list)
		{
			if(pos->hdl_fun){
				if(++pos->cnt >= pos->time){
					pos->hdl_fun();
					pos->cnt = 0;
				}
			}else{
				DBUG_Printf("TIM2_IRQHandler err\n");
			}	
		}	  	
	}
}




