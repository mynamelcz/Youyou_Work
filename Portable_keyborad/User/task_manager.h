#ifndef __TASK_MANAGER_H
#define __TASK_MANAGER_H
#include "cmsis_os.h"



struct __task_hd_t{
	osThreadId    T_hd;
  QueueHandle_t T_queue;
	osMailQId     T_mail;
};


extern struct __task_hd_t TEST_BOARD_TASK;





void task_startup(void);


#endif



