#include "ST480.h"
#include "iic_drv.h"
#include "includes.h"

#define MEASURE_T_MASK	(1<<0)
#define MEASURE_X_MASK	(1<<1)
#define MEASURE_Y_MASK	(1<<2)
#define MEASURE_Z_MASK	(1<<3)

#define ST480_BURST_MODE		(1<<4)
#define ST480_WAKEUP_MODE		(2<<4)
#define ST480_SINGLE_MODE		(3<<4)

/* State */
#define STATE_BURST_MODE_MASK		(1<<7)
#define STATE_WAKEUP_MODE_MASK	(1<<6)
#define STATE_SINGLE_MODE_MASK	(1<<5)
#define	STATE_MODE_MASK	    		(0x7<<5)

#define STATE_ERROR_MASK	(1<<4)
#define STATE_SED_MASK	  (1<<3)
#define STATE_RS_MASK	    (1<<2)

#define STATE_Dx_MASK			(3<<0)		//ÏìÓ¦×Ö½ÚÊý





#define MEASUREMENT_ELEMENT	 (MEASURE_T_MASK|\
															MEASURE_X_MASK|\
															MEASURE_Y_MASK|\
															MEASURE_Z_MASK)




#define MEASUREMENT_MODE_CMD	(ST480_SINGLE_MODE|MEASUREMENT_ELEMENT)
#define READ_MEASUREMENT_CMD 	(0x40|MEASUREMENT_ELEMENT)
#define WRITE_REGISTER_CMD 		 0x60
#define READ_REGISTER_CMD 		 0x50
#define EXIT_REGISTER_CMD 		 0x80
#define MEMORY_RECALL_CMD 		 0xD0
#define MEMORY_STORE_CMD 			 0xE0
#define RESET_CMD 						 0xF0


typedef struct _st480_data
{
	  u16 temperature;
    u16 magneticX;
    u16 magneticY;
    u16 magneticZ;
}st480_data_t;





static int st480_write_buf(u8 *buf, u8 len)
{
	int error;
	error = st480_iic_drv.write(ST480MF_IIC_W_ADDR, buf, len);
	return error;
}
static int st480_read_buf(u8 *buf, u8 len)
{
	int error;
  error = st480_iic_drv.read(ST480MF_IIC_R_ADDR, buf, len);
	return error;
}




static status_t st480_read_measure(st480_data_t *sensor_dat)
{
	  u8 w_temp[2]={0};
	  u8 r_temp[10]={0};
		u8 state = 0;
		
		w_temp[0] = READ_MEASUREMENT_CMD;
		st480_write_buf(w_temp,1);
		st480_read_buf(r_temp, 9);
		

		state = r_temp[0];
		sensor_dat->temperature = ((u16)(r_temp[1]) << 8) + (u16)(r_temp[2]);
		sensor_dat->magneticX   = ((u16)(r_temp[3]) << 8) + (u16)(r_temp[4]);		
		sensor_dat->magneticY   = ((u16)(r_temp[5]) << 8) + (u16)(r_temp[6]);	
		sensor_dat->magneticZ   = ((u16)(r_temp[7]) << 8) + (u16)(r_temp[8]);		
		
		dev_printf("state: 0x%x\n",state);
		dev_printf("ST480---");
		dev_printf("T: 0x%x, ",sensor_dat->temperature);
		dev_printf("m_X: 0x%x, ",sensor_dat->magneticX);
		dev_printf("m_Y: 0x%x, ",sensor_dat->magneticY);
		dev_printf("m_Z: 0x%x\n",sensor_dat->magneticZ);
		
		if(state & STATE_ERROR_MASK){
			ERR_printf(state);
			return STATE_APPEAR_ERR;
		}
		return STATE_NO_ERR;
		
}
static status_t st480_read_register(u8 reg_addr, u16 *reg_dat)
{
	  u8 w_temp[2] ={0};
	  u8 r_temp[10]={0};
		u8 state = 0;
		w_temp[0] = READ_REGISTER_CMD;
		w_temp[1] = reg_addr;
		st480_write_buf(w_temp,2);		
		st480_read_buf(r_temp, 3);
		
		state = r_temp[0];

		*reg_dat = ((u16)(r_temp[1]) << 8) + (u16)(r_temp[2]);
 		
		if(state & STATE_ERROR_MASK){
			ERR_printf(state);
			return STATE_APPEAR_ERR;
		}		
		
		return STATE_NO_ERR;
		
}


static status_t st480_send_cmd(u8 cmd)
{
	  u8 w_temp[2] ={0};
	  u8 r_temp[2]={0};
		u8 state = 0;
		w_temp[0] = cmd;
		st480_write_buf(w_temp,1);		
		st480_read_buf(r_temp, 1);
		
		state = r_temp[0];
 		
		if(state & STATE_ERROR_MASK){
			ERR_printf(state);
			return STATE_APPEAR_ERR;
		}				
		return STATE_NO_ERR;
}

void st480_test(void)
{
	u8 static flg = 0;
	flg++;
	st480_data_t sensor_dat;
	if(flg&0x1){
		st480_send_cmd(MEASUREMENT_MODE_CMD);
	}else{
		st480_read_measure(&sensor_dat);
	}
	
	
	//
}









