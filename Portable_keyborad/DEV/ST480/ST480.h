#ifndef	__ST480_H
#define __ST480_H
#include "includes.h"

#define st480_iic_drv		IIC2_DRIVER_HDL


typedef struct _st480_data
{
	  u16 temperature;
    u16 magneticX;
    u16 magneticY;
    u16 magneticZ;
}st480_data_t;

status_t st480_read_sensor_data(st480_data_t *sensor_dat);

#endif








