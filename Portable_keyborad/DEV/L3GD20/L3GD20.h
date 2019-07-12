#ifndef	__L3GD20_H
#define __L3GD20_H
#include "includes.h"


#define L3gd_iic_drv		IIC2_DRIVER_HDL

#define L3GD20H_ID       0xD4U

typedef struct _L3gd20_data
{
	u8  temperature;
    float angular_rateX;
    float angular_rateY;
    float angular_rateZ;
}L3gd20_data_t;

typedef union{
  s16 i16bit[3];
  u8 u8bit[6];
}L3gd20_axis3bit16_t;

typedef union{
  s16 i16bit;
  u8  u8bit[2];
}L3gd20_axis1bit16_t;

typedef union{
  s32 i32bit[3];
  u8 u8bit[12];
}L3gd20_axis3bit32_t;

typedef union{
  s32 i32bit;
  u8 u8bit[4];
}L3gd20_axis1bit32_t;





status_t L3gd20h_init(void);































#endif







