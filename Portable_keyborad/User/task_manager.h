#ifndef __TASK_MANAGER_H
#define __TASK_MANAGER_H
#include "cmsis_os.h"
#include "includes.h"



typedef struct {
    u32 len;
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
	
	u32 (*init)(void *pram);
	u32 (*exit)(void *pram);
	u32 (*check)(void *pram);	
};


extern struct __script_hd_t *Current_Script_ptr;

extern struct __task_hd_t Main_Task;
extern struct __task_hd_t MsgIssue_Task;

extern struct __script_hd_t Test_Board_Script;








void task_startup(void);






osStatus task_msg_pend(struct __task_hd_t *task, task_com_msg_t *msg_ptr, uint32_t millisec);
void task_msg_put(struct __task_hd_t *task, u8 num,...);
void task_create(struct __task_hd_t *task,
								TaskFunction_t fun,
								void *private_arg,
								const char * const pcName,
								const uint16_t usStackDepth,
								UBaseType_t uxPriority,
								u8 need_msg);

u32 switch_to_spec_script(struct __script_hd_t *script);
#endif



