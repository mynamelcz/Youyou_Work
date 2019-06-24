#include "common.h"








#ifdef __ASSERT_PARAM
void assert_fail(u8* file, u32 line)
{
	DBUG_Printf("[assert_fail] __file:%s ;__line:%d\n",file,line); 
	while(1);
}
#endif











