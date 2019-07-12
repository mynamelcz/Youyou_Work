#include "test_board_script.h"
#include "task_manager.h"

static const struct key_msg_t task_key_msg;
static struct __script_hd_t *const __this_script_hd	=	&Test_Board_Script;



static void test_board_script(void *pram)
{
	(void)pram;
	task_com_msg_t msg;
	tb_script_printf("FUN:%s\n",__FUNCTION__);
	while(1)
	{
		task_msg_pend(&__this_script_hd->task, &msg);
		if(msg.msg[0] != HALF_SEC_MSG){
			tb_script_printf("TstBd Tsk:");
			tb_script_puthex((const char *)(&msg),msg.len+1);
		}
		switch(msg.msg[0]){
			case HALF_SEC_MSG:
				 tb_script_printf("script HF_MSG\n");
				 break;
			case TEST_L3GD20_MSG:
				tb_script_printf("TEST_L3GD20_MSG\n");
				break;
			case TEST_MMA8653_MSG:
				tb_script_printf("TEST_MMA8653_MSG\n");
				break;
			case TEST_ST480_MSG:
				tb_script_printf("TEST_ST480_MSG\n");
				break;
			case TEST_TCA8418_MSG:
				tb_script_printf("TEST_TCA8418_MSG\n");
				break;
			default:
			 break;
		 }
	}
}



static u32 test_board_script_checkin(void *pram)
{
	 tb_script_printf("FUN:%s\n",__FUNCTION__);
		return true;
}

static u32 test_board_script_init(void *pram)
{  
	tb_script_printf("FUN:%s\n",__FUNCTION__);
	task_create(&__this_script_hd->task,
								test_board_script,
								pram,
								TEST_BOARD_SCRIPT_NAME,
								TEST_BOARD_SCRIPT_STACK,
								TEST_BOARD_SCRIPT_PRIO,
								1);
	//__this_script_hd->key_msg = &task_key_msg;
	return true;
}

static u32 test_board_script_exit(void *pram)
{
  tb_script_printf("FUN:%s\n",__FUNCTION__);
	return true;
}




struct __script_hd_t Test_Board_Script = {
	.init = test_board_script_init,
	.exit = test_board_script_exit,
	.check= test_board_script_checkin,
	.key_msg = &task_key_msg,
};



static const struct key_msg_t task_key_msg = {
	.short_msg	={
/*00*/		TEST_L3GD20_MSG,
/*01*/		TEST_MMA8653_MSG,
/*02*/		TEST_ST480_MSG,
/*03*/		TEST_TCA8418_MSG,
/*04*/		NO_KYE_MSG,
/*05*/		NO_KYE_MSG,
/*06*/		NO_KYE_MSG,
/*07*/		NO_KYE_MSG,
/*08*/		NO_KYE_MSG,
/*09*/		NO_KYE_MSG,
	},
	.long_msg		={
/*00*/		NO_KYE_MSG,
/*01*/		NO_KYE_MSG,
/*02*/		NO_KYE_MSG,
/*03*/		NO_KYE_MSG,
/*04*/		NO_KYE_MSG,
/*05*/		NO_KYE_MSG,
/*06*/		NO_KYE_MSG,
/*07*/		NO_KYE_MSG,
/*08*/		NO_KYE_MSG,
/*09*/		NO_KYE_MSG,	
	},
	.double_msg	={
/*00*/		NO_KYE_MSG,
/*01*/		NO_KYE_MSG,
/*02*/		NO_KYE_MSG,
/*03*/		NO_KYE_MSG,
/*04*/		NO_KYE_MSG,
/*05*/		NO_KYE_MSG,
/*06*/		NO_KYE_MSG,
/*07*/		NO_KYE_MSG,
/*08*/		NO_KYE_MSG,
/*09*/		NO_KYE_MSG,	
	},
	.repeat_msg	={
/*00*/		NO_KYE_MSG,
/*01*/		NO_KYE_MSG,
/*02*/		NO_KYE_MSG,
/*03*/		NO_KYE_MSG,
/*04*/		NO_KYE_MSG,
/*05*/		NO_KYE_MSG,
/*06*/		NO_KYE_MSG,
/*07*/		NO_KYE_MSG,
/*08*/		NO_KYE_MSG,
/*09*/		NO_KYE_MSG,	
	},
	.repeat_up_msg={
/*00*/		NO_KYE_MSG,
/*01*/		NO_KYE_MSG,
/*02*/		NO_KYE_MSG,
/*03*/		NO_KYE_MSG,
/*04*/		NO_KYE_MSG,
/*05*/		NO_KYE_MSG,
/*06*/		NO_KYE_MSG,
/*07*/		NO_KYE_MSG,
/*08*/		NO_KYE_MSG,
/*09*/		NO_KYE_MSG,	
	},
};































































