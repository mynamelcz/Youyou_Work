#ifndef __APP_CFG_H
#define __APP_CFG_H
#include "stdio.h"
#include "my_printf.h"



#define __ASSERT_PARAM
#define DBUG_Printf 	printf		// MY_RTT_printf
#define DBUG_Put_hex 	my_printhex	
//====== ERR  =========//
#define ERR_printf(res)		 DBUG_Printf("[%d][ERR][%s] Res: %d\n",__LINE__,__func__,res)
#define ERR_log					   DBUG_Printf




#define DBUG_APP
#define DBUG_DEV



#ifdef DBUG_DEV
#define dev_printf	DBUG_Printf
#define dev_puthex	DBUG_Put_hex
#else
#define dev_printf(...)
#define dev_puthex(...)
#endif


#ifdef DBUG_APP
#define app_printf	DBUG_Printf
#define app_puthex	DBUG_Put_hex
#else
#define app_printf(...)
#define app_puthex(...)
#endif




/***************	Task	**************/
//common
#define TASK_MSG_Q_NUM					4
#define TASK_MSG_MAX_LEN				4




#define MAIN_TASK_NAME							"MainTask"
#define MAIN_TASK_STACK 						128
#define MAIN_TASK_PRIO							5

#define MSG_ISSUE_TASK_NAME					"MsgIssueTask"
#define MSG_ISSUE_TASK_STACK 				64
#define MSG_ISSUE_TASK_PRIO					4


#define TEST_BOARD_SCRIPT_NAME			"TestBoardScript"
#define TEST_BOARD_SCRIPT_STACK 		64
#define TEST_BOARD_SCRIPT_PRIO			3









#endif
