#ifndef __DEV_MANAGER_H
#define __DEV_MANAGER_H

typedef enum {
		STATE_NO_ERR = 0,
	  STATE_APPEAR_ERR,
		STATE_INIT_ERR,
	  STATE_DEV_ON_LINE,
		STATE_DEV_OFF_LINE,
}status_t;

status_t bsp_dev_init(void);



#endif
















