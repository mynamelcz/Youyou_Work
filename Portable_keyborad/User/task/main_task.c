#include "main_task.h"
#include "task_manager.h"
#include "stm32f0xx_hal.h"

#include "timer_task.h"
#include "msg_issue_task.h"

extern TIM_HandleTypeDef htim1;

struct __task_hd_t Main_Task;
static struct __task_hd_t *const __this_task	=	&Main_Task;

static void main_task(void *pram);

void main_task_init(void *pram)
{
	task_create(__this_task, main_task, pram,
							MAIN_TASK_NAME, MAIN_TASK_STACK, MAIN_TASK_PRIO, 1);	
}

static void main_task(void *pram)
{
	(void)pram;
  task_com_msg_t msg;
	
  msg_issue_task_init(NULL);
#if  (configUSE_TIMERS==1)	
	init_timer_taask_fun();
#endif
	HAL_TIM_Base_Start_IT(&htim1);
	while(1)
	{
		task_msg_pend(__this_task, &msg);
		if(msg.msg[0] != HALF_SEC_MSG){
			app_printf("Main Tsk:");
			app_puthex((const char *)(&msg),msg.len+1);
		}
		
		switch(msg.msg[0]){
			 case HALF_SEC_MSG:
				 app_printf("HALF_SEC_MSG\n");
				 break;
			 default:
				 break;
		 }
	}
}

























