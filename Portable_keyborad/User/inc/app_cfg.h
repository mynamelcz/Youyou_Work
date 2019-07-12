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


#define DBUG_TB_SCRIPT

#ifdef DBUG_TB_SCRIPT
#define tb_script_printf	DBUG_Printf
#define tb_script_puthex	DBUG_Put_hex
#else
#define tb_script_printf(...)
#define tb_script_puthex(...)
#endif


/***************	Task	**************/
//common
#define TASK_MSG_Q_NUM					4
#define TASK_MSG_MAX_LEN				4

#define TASK_MIN_STACK_SIZE			32

// Sys Task
#define DEF_TASK_NAME   					"defTask"
#define DEF_TASK_STACK  					32
#define DEF_TASK_PRIO			 				5

#define IDEL_TASK_NAME   					"IdelTask"
#define IDEL_TASK_STACK  					TASK_MIN_STACK_SIZE
#define IDEL_TASK_PRIO			 			0


#define TIMER_TASK_NAME   				"TimerTask"
#define TIMER_TASK_STACK  				100
#define TIMER_TASK_PRIO			 			(configMAX_PRIORITIES-1)

// user Task
#define MAIN_TASK_NAME						"MainTask"
#define MAIN_TASK_STACK 					80
#define MAIN_TASK_PRIO						5

#define MSG_ISSUE_TASK_NAME				"MsgTask"
#define MSG_ISSUE_TASK_STACK 			60
#define MSG_ISSUE_TASK_PRIO				4


#define TEST_BOARD_SCRIPT_NAME		"TBScript"
#define TEST_BOARD_SCRIPT_STACK 	128
#define TEST_BOARD_SCRIPT_PRIO		3









#endif
