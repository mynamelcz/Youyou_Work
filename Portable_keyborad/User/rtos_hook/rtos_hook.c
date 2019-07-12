#include "rtos_hook.h"
#include "cmsis_os.h"
#include "includes.h"



#if (configUSE_MALLOC_FAILED_HOOK == 1)
void vApplicationMallocFailedHook( void )
{
	ERR_log("vApplication Malloc Failed\n");
	while(1);
}
#endif

































