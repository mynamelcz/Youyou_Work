#include "timer_task.h"
#include "task_manager.h"
#include "cmsis_os.h"
#include "includes.h"


#if (configUSE_TIMERS==1)

struct __timer_task{
	osTimerId half_sec_id;     
};
struct __os_inf_t{
	u8 task_num;
	u32 TotalRunTime;
  TaskStatus_t *StatusArray;
};

struct __timer_task Timer_Task_t;
struct __os_inf_t os_inf;


static void half_second_task(TimerHandle_t Timer_hd)
{
	  task_msg_put(&Main_Task, 1, HALF_SEC_MSG);
	
	  if(Current_Script_ptr != NULL){
			task_msg_put(&Current_Script_ptr->task, 1, HALF_SEC_MSG);
		}else{
			 app_printf("Current_Script_ptr NULL\n");
		}
		
		
	  u32 TotalRunTime;
		UBaseType_t ArraySize , i;
    os_inf.task_num = uxTaskGetNumberOfTasks();	
	  app_printf("task_num: %d\n",os_inf.task_num);
	  os_inf.StatusArray = pvPortMalloc(os_inf.task_num*sizeof(TaskStatus_t));
		if(os_inf.StatusArray != NULL){
				ArraySize = uxTaskGetSystemState((TaskStatus_t* 	)os_inf.StatusArray, 	
									   (UBaseType_t		)os_inf.task_num, 	
								       (uint32_t*		)&TotalRunTime);

			app_printf("TaskName \tPriority\tTaskNum\t\tStack\t\r\n");
			for(i = 0; i < ArraySize; i++)
			{
				app_printf("%s     \t%d\t\t%d\t\t%d\t\r\n",				
						os_inf.StatusArray[i].pcTaskName,
						(int)os_inf.StatusArray[i].uxCurrentPriority,
						(int)os_inf.StatusArray[i].xTaskNumber,
						(int)os_inf.StatusArray[i].usStackHighWaterMark);				
			}
		}
		vPortFree(os_inf.StatusArray);	
}



void init_timer_taask_fun(void)
{
	osStatus state = osOK;

	Timer_Task_t.half_sec_id = xTimerCreate((const char *)"Half Sec",
																				500, pdTRUE,(void *) 1,half_second_task);
	ASSERT(Timer_Task_t.half_sec_id);
	state = xTimerStart(Timer_Task_t.half_sec_id, 1000);
	if(state == osErrorOS){
		ERR_printf(state);
	}
}






















#endif






























