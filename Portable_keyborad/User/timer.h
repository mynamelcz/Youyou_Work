#ifndef __TIMER_H
#define __TIMER_H
#include "includes.h"

typedef struct{
	u32  time;
	u32  cnt;
	void (*hdl_fun)(void);
	struct list_head list;
}__irq_hd_t;



#define __IRQ_HdlTypedef(fun, times) 	   \
 	 __irq_hd_t fun##irq = {			   \
	 .time  = times,					   \
	 .cnt   = 0,						   \
	 .hdl_fun = fun,          			   \
	 .list = LIST_HEAD_INIT(fun##irq.list) \
}



	
	
	
	
void register_timer1_handler(__irq_hd_t *hd_t);
void register_timer1_handler_malloc(void(*fun)(void), u32 time);
	
	
	
#endif





