#ifndef	__MMA8653_H
#define __MMA8653_H

#include "includes.h"


#define mma_iic_drv		IIC2_DRIVER_HDL

typedef struct _mma8653_data
{
    u16 accelX;
    u16 accelY;
    u16 accelZ;
}mma8653_data_t;

/*MMA8653 function configuration*/
#define MMA8653_FULL_SCALE							FULL_SCALE_2G		//Á¿³Ì

#define MMA8653_USE_INT									0
#define MMA8653_Motion_Freefall_Detect	0
#define MMA8653_Auto_Sleep							0









status_t mma8653_init(void);
status_t mma8653_read_sensor_data(mma8653_data_t *sensor_dat);













#endif






