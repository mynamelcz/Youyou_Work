#include "timer_task.h"
#include "task_manager.h"
#include "cmsis_os.h"
#include "includes.h"


#if (configUSE_TIMERS==1)

struct __timer_task{
	osTimerId half_sec_id;

};
struct __os_inf_t{
	UBaseType_t task_num;
  TaskStatus_t *StatusArray;
};

struct __timer_task Timer_Task_t;
struct __os_inf_t os_inf;


static void half_second_task(TimerHandle_t Timer_hd)
{
	  task_msg_put(&Main_Task, 1, HALF_SEC_MSG);
	
	
	
//	  u32 TotalRunTime;
//		UBaseType_t ArraySize , i;
//    os_inf.task_num = uxTaskGetNumberOfTasks();	
//	  os_inf.StatusArray = pvPortMalloc(os_inf.task_num*sizeof(TaskStatus_t));
//		if(os_inf.StatusArray != NULL){
//				ArraySize = uxTaskGetSystemState((TaskStatus_t* 	)os_inf.StatusArray, 	
//									   (UBaseType_t		)os_inf.task_num, 	
//								       (uint32_t*		)&TotalRunTime);
//			app_printf("TaskName\t\tPriority\t\tTaskNumber\t\t\r\n");
//			for(i = 0; i < ArraySize; i++)
//			{
//				app_printf("%s\t\t%d\t\t\t%d\t\t\t\r\n",				
//						os_inf.StatusArray[i].pcTaskName,
//						(int)os_inf.StatusArray[i].uxCurrentPriority,
//						(int)os_inf.StatusArray[i].xTaskNumber);		
//			}
//		}





	vPortFree(os_inf.StatusArray);	
}



void init_timer_taask_fun(void)
{
	osStatus state = osOK;

	Timer_Task_t.half_sec_id = xTimerCreate((const char *)"Half Sec",
																				500, pdTRUE,(void *) 1,half_second_task);
	ASSERT(Timer_Task_t.half_sec_id);
	state = xTimerStart(Timer_Task_t.half_sec_id, 500);
	if(state == osErrorOS){
		ERR_printf(state);
	}
}






















#endif






























