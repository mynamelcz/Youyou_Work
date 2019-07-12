#include "test_board_script.h"
#include "task_manager.h"

//static const struct key_msg_t task_key_msg;

struct __script_hd_t Test_Board_Script;
//static struct __script_hd_t *const __this_script_hd	=	&Test_Board_Script;

/* Function Declareation*/
//static void test_board_script(void *pram);
//static void test_board_script_init(void *pram);
//static void test_board_script_exit(void *pram);
//static u8 test_board_script_checkin(void *pram);



//static u8 test_board_script_checkin(void *pram)
//{
//		return 1;
//}

//static void test_board_script_init(void *pram)
//{  
//	task_create(&__this_script_hd->task,
//								test_board_script,
//								pram,
//								TEST_BOARD_SCRIPT_NAME,
//								TEST_BOARD_SCRIPT_STACK,
//								TEST_BOARD_SCRIPT_PRIO,
//								1);
//	__this_script_hd->key_msg = &task_key_msg;
//}

//static void test_board_script_exit(void *pram)
//{

//}

//static void test_board_script(void *pram)
//{
//	(void)pram;
//	task_com_msg_t *msg_ptr;
//	
//	while(1)
//	{
//		task_msg_pend(&__this_script_hd->task, msg_ptr);
//		 switch(msg_ptr->msg[0]){
//			 case HALF_SEC_MSG:
//				 app_printf("HALF_SEC_MSG\n");
//				 break;
//			 default:
//				 break;
//		 }
//	}
//}





static const struct key_msg_t task_key_msg = {
	.short_msg	={
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































































