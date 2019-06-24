#ifndef __APP_CFG_H
#define __APP_CFG_H
#include "stdio.h"


#define __ASSERT_PARAM
#define DBUG_Printf 	printf		// MY_RTT_printf

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
