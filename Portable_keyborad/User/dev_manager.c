#include "dev_manager.h"
#include "key.h"
#include "l3gd20.h"
#include "mma8653.h"
#include "st480.h"
#include "tca8418.h"




status_t bsp_dev_init(void)
{
	status_t state = STATE_NO_ERR;
	
	state = L3gd20h_init();
	if(state != STATE_NO_ERR){
		ERR_printf(state);
	}
	state = mma8653_init();
	if(state != STATE_NO_ERR){
		ERR_printf(state);
	}
  state = tca8418_init();
	if(state != STATE_NO_ERR){
		ERR_printf(state);
	}	
	
	key_detect_init();
	return state;

}








