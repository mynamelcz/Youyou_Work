#ifndef __APP_CFG_H
#define __APP_CFG_H
#include "stdio.h"


#define __ASSERT_PARAM
#define DBUG_Printf 	printf		// MY_RTT_printf

//====== ERR  =========//
#define ERR_printf(res)		 DBUG_Printf("[%d][ERR][%s] Res: %d\n",__LINE__,__func__,res)




#define DBUG_APP
#define DBUG_DEV



#ifdef DBUG_DEV
#define dev_printf	DBUG_Printf
#else
#define dev_printf(...)
#endif


#ifdef DBUG_APP
#define app_printf	DBUG_Printf
#else
#define app_printf(...)
#endif








#endif
