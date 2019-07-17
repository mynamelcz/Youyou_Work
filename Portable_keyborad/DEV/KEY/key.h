#ifndef	__KEY_H
#define __KEY_H
#include "includes.h"
#include "key_dec.h"


#define KEY_VAL_CBUF_LEN		16




enum KEY_ID{
	KeyScan_TAC8418_TEST_KEY_ID,
	Magnetic_ST480M_TEST_KEY_ID,
	Acceleration_MMA8653_TEST_KEY_ID,
	AngularRate_L3GD20_TEST_KEY_ID,
	VOL_DEC_KEY_ID,
	KEY_MAX_ID,
};

struct key_val_t{
	u8 state;
	u8 key_id;
};






struct key_msg_t{
	u16 short_msg[APP_TOTAL_KEY_NUM];
#if(APP_LONG_KEY_EN)
	u16 long_msg[APP_TOTAL_KEY_NUM];
#endif
#if(APP_DOUBLE_KEY_EN)
	u16 double_msg[APP_TOTAL_KEY_NUM];
#endif
#if(APP_REPEAT_KEY_EN)
	u16 repeat_msg[APP_TOTAL_KEY_NUM];
	u16 repeat_up_msg[APP_TOTAL_KEY_NUM];
#endif
};

void key_detect_init(void);
u8 key_val_get(struct key_val_t *k_val);


#endif








