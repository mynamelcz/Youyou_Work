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


#define KEY_NUM_TOTAL		10
struct key_msg_t{
	u16 short_msg[KEY_NUM_TOTAL];
	u16 long_msg[KEY_NUM_TOTAL];
	u16 double_msg[KEY_NUM_TOTAL];
	u16 repeat_msg[KEY_NUM_TOTAL];
	u16 repeat_up_msg[KEY_NUM_TOTAL];
};

void key_detect_init(void);
u8 key_val_get(struct key_val_t *k_val);
#endif








