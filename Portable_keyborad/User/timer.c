#include "timer.h"
#include "stm32f0xx_hal.h"
#include "includes.h"
#include "stdlib.h"

extern TIM_HandleTypeDef htim1;

#define T_IRQ_HdlList(fun, time)	&(fun##irq.list)
#define T_IRQ_Hdl(fun)	    	   &(fun##irq)	


LIST_HEAD(TIM1_IRQHandler_ListHead);
	
void register_timer1_handler(Tirq_hd_t *hd_t)
{	
	HAL_TIM_Base_Stop_IT(&htim1);
	list_add_tail(&hd_t->list, &TIM1_IRQHandler_ListHead);		
	HAL_TIM_Base_Start_IT(&htim1);
}	
	
void register_timer1_handler_malloc(void(*fun)(void), u32 time)
{
	Tirq_hd_t *hd_t = malloc(sizeof(Tirq_hd_t));
	ASSERT(hd_t);
	hd_t->cnt = 0;
	hd_t->time = time;
	hd_t->hdl_fun = fun;
	hd_t->list.next = &(hd_t->list);
	hd_t->list.prev = &(hd_t->list);
	
	register_timer1_handler(hd_t);
}	

static void loop_timer_fun_list(struct list_head *head)
{
	Tirq_hd_t *pos = NULL;
	list_for_each_entry(pos, head, list)
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





#if 1
#define T_SecIRQ_Hdl(fn,Tx)   &(__timer##Tx##fn)

#define INIT_TIMER_LOOP_FUN(fn, time, Tx, level)                                          \
            __USED  Tirq_sec_hd_t __timer##Tx##fn __AT_SEC(".timer_fun."level) = \
            { time,0, fn};
						


						
void timer1_test_loop(void)
{
	app_printf("FUN:%s\n",__FUNCTION__);
}


INIT_TIMER_LOOP_FUN(timer1_test_loop,1000,1, "1");						
						
static void timer1_fun_start(void)
{
	  app_printf("FUN:%s\n",__FUNCTION__);
    return;
}
INIT_TIMER_LOOP_FUN(timer1_fun_start,1000,1, "0");	
static void timer1_fun_end(void)
{
	  app_printf("FUN:%s\n",__FUNCTION__);
    return;
}
INIT_TIMER_LOOP_FUN(timer1_fun_end,1000,1, "1.end");	



static void loop_timer_fun_sec(void)
{
	Tirq_sec_hd_t *pos = NULL;
	for(pos = T_SecIRQ_Hdl(timer1_fun_start, 1)+1;pos < T_SecIRQ_Hdl(timer1_fun_end, 1); pos++ ){
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

#endif




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1){
		loop_timer_fun_list(&TIM1_IRQHandler_ListHead);
	}
}




