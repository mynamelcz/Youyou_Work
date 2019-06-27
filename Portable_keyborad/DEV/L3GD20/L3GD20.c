#include "L3GD20.h"
#include "iic_drv.h"

#define FULL_SCALE_250_DPS
#define FULL_SCALE_500_DPS
#define FULL_SCALE_2000_DPS

#define SPI_INTERFACE_MODE
#define IIC_INTERFACE_MODE




#define FIFO_CTRL_REG		








typedef struct _L3gd20_data
{
	  u8  temperature;
    u16 angular_rateX;
    u16 angular_rateY;
    u16 angular_rateZ;
}L3gd20_data_t;


