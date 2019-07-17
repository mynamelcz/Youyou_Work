#include "msg_issue_task.h"
#include "task_manager.h"
#include "cmsis_os.h"

#include "key.h"

struct __task_hd_t MsgIssue_Task;
static struct __task_hd_t *const __this_task	=	&MsgIssue_Task;



static void msg_issue_task(void *pram);

void msg_issue_task_init(void *pram)
{
	task_create(__this_task, msg_issue_task, pram,
							MSG_ISSUE_TASK_NAME, MSG_ISSUE_TASK_STACK, MSG_ISSUE_TASK_PRIO, 0);	
}



static void msg_issue_task(void *pram)
{
 (void)pram;
	struct key_val_t k_val;
	

	u32 k_msg = NO_ANY_MSG;
	while(1)
	{
		osDelay(10);
		if(Current_Script_ptr == NULL){
			return;
		}
		if(key_val_get(&k_val) != 0){
			switch(k_val.state){
				case KEY_SHORT:
				  k_msg = Current_Script_ptr->key_msg->short_msg[k_val.key_id];
					break;
#if(APP_LONG_KEY_EN)
				case KEY_LONG:	
					k_msg = Current_Script_ptr->key_msg->long_msg[k_val.key_id];
					break;
#endif
#if(APP_DOUBLE_KEY_EN)
				case KEY_DOUBLE:
					k_msg = Current_Script_ptr->key_msg->double_msg[k_val.key_id];
					break;
#endif
#if(APP_REPEAT_KEY_EN)
				case KEY_REPEAT:
					k_msg = Current_Script_ptr->key_msg->repeat_msg[k_val.key_id];
					break;
				case KEY_REPEAT_UP: 
					k_msg = Current_Script_ptr->key_msg->repeat_up_msg[k_val.key_id];
					break;
#endif
				default:
						ERR_printf(0);
					break;
			
			}
			app_printf("key_id:%d  state: %d\n",k_val.key_id, k_val.state);
			if((k_msg > MAIN_TASK_MSG_MIN)&&(k_msg < MAIN_TASK_MSG_MAX)){
				 task_msg_put(&Main_Task, 1, k_msg);
			}else{
				 task_msg_put(&Current_Script_ptr->task, 1, k_msg);
			}					
		}
	
	}

}
























