#ifndef __TASK_MANAGER_H
#define __TASK_MANAGER_H
#include "cmsis_os.h"
#include "includes.h"



typedef struct {
    u8 len;
    u32 msg[TASK_MSG_MAX_LEN];
}task_com_msg_t;

struct __task_hd_t{
	TaskHandle_t    T_hd;
  QueueHandle_t 	T_queue;
	osMailQId     	T_mail;
};
struct __script_hd_t{
  struct __task_hd_t task;
	const struct key_msg_t  *key_msg;
};


extern struct __script_hd_t *Current_Script_ptr;

extern struct __task_hd_t Main_Task;
extern struct __task_hd_t MsgIssue_Task;

extern struct __script_hd_t Test_Board_Script;




extern struct __task_hd_t TEST_BOARD_TASK;





void task_startup(void);






void task_msg_pend(struct __task_hd_t *task, task_com_msg_t *msg_ptr);
void task_msg_put(struct __task_hd_t *task, u8 num,...);
void task_create(struct __task_hd_t *task,
								TaskFunction_t fun,
								void *private_arg,
								const char * const pcName,
								const uint16_t usStackDepth,
								UBaseType_t uxPriority,
								u8 need_msg);


#endif



