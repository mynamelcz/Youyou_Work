#ifndef __IIC_DRV_H
#define __IIC_DRV_H
#include "includes.h"

struct iic_master_drv{
  u32 (*write)(u16 addr, u8 *buf, u16 len);
	u32 (*read )(u16 addr, u8 *buf, u16 len);
	u32 (*w_reg)(u16 addr, u16 reg, u8 *buf, u16 len);
	u32 (*r_reg)(u16 addr, u16 reg, u8 *buf, u16 len);
};



extern const struct iic_master_drv IIC2_DRIVER_HDL;

#endif





