#include "task_manager.h"

#include "stm32f0xx_hal.h"
#include "cmsis_os.h"

#include "includes.h"
#include "led.h"
#include "board.h"



#define  TEST_TASK_NAME				 TEST_TASK
#define  TEST_TASK_PRIO        osPriorityNormal 
#define  TEST_TASK_STACK_SIZE  128
osThreadId test_task_hd = NULL;


static void all_led_test(void);

void test_task(void const *param)
{
	(void)param;
	SGM_1V8_EN(1);
  all_led_test();
  for(;;)
  {
		

		RGB_TEST_LED_TOL();
		KEY_TEST_LED_TOL();		
		MMA_TEST_LED_TOL();		
		GYR_TEST_LED_TOL();		
		KEY_BORAD_LED_TOL();	
		osDelay(500);	
			

  }
}




static void all_led_test(void)
{
	for(u8 i=0;i<3;i++){

	}
}
void task_startup(void)
{
 //   app_printf(">>>>   FUN:%s <<<<\n",__func__);
    osThreadDef(TEST_TASK_NAME, test_task, TEST_TASK_PRIO, 0, TEST_TASK_STACK_SIZE);
    test_task_hd = osThreadCreate(osThread(TEST_TASK_NAME),(void *)1); 		
}











