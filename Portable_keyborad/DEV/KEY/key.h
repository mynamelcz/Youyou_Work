#ifndef	__KEY_H
#define __KEY_H
#include "includes.h"

#define KEY_VAL_CBUF_LEN		16


enum KEY_ID{
	KEY_TEST_KEY_ID,
	RGB_TEST_KEY_ID,
	MMA_TEST_KEY_ID,
	GYR_TEST_KEY_ID,
	VOL_DEC_KEY_ID,
	KEY_MAX_ID,
};

struct key_val_t{
	u8 state;
	u8 key_id;
};

#endif








