#ifndef	__TCA8418_H
#define __TCA8418_H
#include "includes.h"


#define tca_iic_drv		IIC2_DRIVER_HDL


enum tca8418_key_state{
	TCA8418_KEY_RELEASE,
	TCA8418_KEY_PRESS,
};
struct tca8418_keypad{
	u8 k_state;
	u8 k_id;
};


status_t tca8418_init(void);
void tca8418_read_keypad(void);
u8 tca8418_key_val_get(struct tca8418_keypad *k_val);









#endif








