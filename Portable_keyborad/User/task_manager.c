#include "task_manager.h"

#include "stm32f0xx_hal.h"
#include "cmsis_os.h"

#include "includes.h"
#include "led.h"
#include "board.h"
#include "stdarg.h"



struct __script_hd_t *Current_Script_ptr = NULL;




void task_msg_put(struct __task_hd_t *task, u8 num,...)
{
	osStatus res = osOK;
	task_com_msg_t *msg_ptr;
	u8 i = 0;
	
	ASSERT(task);
	if((num ==0)||(num > TASK_MSG_MAX_LEN)){
		ERR_printf(num);
		return;
	}
	if(task->T_mail == NULL){
		ERR_printf(0);
		return;
	}
	msg_ptr = osMailAlloc(task->T_mail, osWaitForever);
	if(msg_ptr == NULL){
		ERR_printf(0);
		return;
	}
	msg_ptr->len = num;
  va_list p_arg;
  va_start(p_arg, num);	
	for(i = 0; i < num; i++){
		 msg_ptr->msg[i] = va_arg(p_arg, u32);
	}
	va_end(p_arg);

  res = osMailPut(task->T_mail, msg_ptr); 
  if(res != osOK){
		ERR_printf(0);
		return;		
	}	
}
	
void task_msg_pend(struct __task_hd_t *task, task_com_msg_t *msg_ptr)
{
	u8 i = 0;
  osEvent event;
  event.status = osOK;
	task_com_msg_t *msg;
  event = osMailGet(task->T_mail, portMAX_DELAY);
  if (event.status == osEventMail){
			msg = (task_com_msg_t *)(event.value.p);
  }else{
		ERR_printf(event.status);
	}
	msg_ptr->len = msg->len;
	for(i = 0; i < msg_ptr->len; i++){
		msg_ptr->msg[i] = msg->msg[i];
	}

	osMailFree(task->T_mail, (void *)event.value.p);
}
		
	
void task_create(struct __task_hd_t *task,
								TaskFunction_t fun,
								void *private_arg,
								const char * const pcName,
								const uint16_t usStackDepth,
								UBaseType_t uxPriority,
								u8 need_msg)
{
  if (xTaskCreate(fun, pcName, usStackDepth, 
									private_arg, uxPriority, &(task->T_hd))!= pdPASS){
		ERR_printf(0);
		ERR_log("TASK:[%s] Great ERR\n",pcName);
    return;
  }   

	if(need_msg){
		osMailQDef(task_queue, TASK_MSG_Q_NUM, task_com_msg_t);
		task->T_mail = osMailCreate(osMailQ(task_queue), NULL);	
		if(task->T_mail == NULL){
			ERR_printf(0);
		}	
	}else{
		task->T_mail = NULL;
		task->T_queue = NULL;
	}
}



void switch_to_spec_script(void)
{


}
void switch_to_next_script(void)
{


}




















//#define  TEST_TASK_NAME				 TEST_TASK
//#define  TEST_TASK_PRIO        osPriorityNormal 
//#define  TEST_TASK_STACK_SIZE  128
//osThreadId test_task_hd = NULL;


//static void all_led_test(void);





//void test_task(void const *param)
//{
//	(void)param;
//	SGM_1V8_EN(1);
//  all_led_test();

//  for(;;)
//  {

//		RGB_TEST_LED_TOL();
//		KEY_TEST_LED_TOL();		
//		MMA_TEST_LED_TOL();		
//		GYR_TEST_LED_TOL();		
//		KEY_BORAD_LED_TOL();	
//		osDelay(500);	
//			

//  }
//}




//static void all_led_test(void)
//{
//	for(u8 i=0;i<3;i++){

//	}
//}
//void task_startup(void)
//{
// //   app_printf(">>>>   FUN:%s <<<<\n",__func__);
//    osThreadDef(TEST_TASK_NAME, test_task, TEST_TASK_PRIO, 0, TEST_TASK_STACK_SIZE);
//    test_task_hd = osThreadCreate(osThread(TEST_TASK_NAME),(void *)1); 		
//}










