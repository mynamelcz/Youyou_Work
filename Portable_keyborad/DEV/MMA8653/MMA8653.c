#include "MMA8653.h"
#include "iic_drv.h"

/*Data Status Register*/
#define MMA8X5X_STATUS_REG 0x00

#define STATUS_ZYXOW_MASK 0x80	//新数据未读取，被覆盖
#define STATUS_ZOW_MASK 	0x40
#define STATUS_YOW_MASK 	0x20
#define STATUS_XOW_MASK 	0x10
#define STATUS_ZYXDR_MASK 0x08	//有新数据已经准备好
#define STATUS_ZDR_MASK 	0x04
#define STATUS_YDR_MASK 	0x02
#define STATUS_XDR_MASK 	0x01

/*X Y Z Data Register */
#define	MMA8X5X_OUT_X_MSB_REG 	0x01
#define	MMA8X5X_OUT_X_LSB_REG 	0x02
#define	MMA8X5X_OUT_Y_MSB_REG 	0x03
#define	MMA8X5X_OUT_Y_LSB_REG 	0x04
#define	MMA8X5X_OUT_Z_MSB_REG 	0x05
#define	MMA8X5X_OUT_Z_LSB_REG  	0x06

/* SYSMOD System Mode REG: 0x0B*/
#define	MMA8X5X_SYSMOD_REG 0x0B

#define FGT_4_MASK 		0x40 	
#define FGT_3_MASK 		0x20 
#define FGT_2_MASK 		0x10 	
#define FGT_1_MASK	  0x08 	
#define FGT_0_MASK 		0x04 

#define FGT_MASK 			0x7C  

#define SYSMOD1_MASK 	0x02
#define SYSMOD0_MASK 	0x01
#define SYSMOD_MASK 	0x03

#define SYSMOD_STANDBY 0x00
#define SYSMOD_WAKE  	(SYSMOD0_MASK)
#define SYSMOD_SLEEP 	(SYSMOD1_MASK)

/* INT_SOURCE 	- 	REG: 0x0C */
#define MMA8X5X_INT_SOURCE_REG	0x0C

#define SRC_ASLP_MASK 	0x80
#define SRC_FIFO_MASK 	0x40
#define SRC_TRANS_MASK 	0x20
#define SRC_LNDPRT_MASK 0x10
#define SRC_PULSE_MASK 	0x08
#define SRC_FF_MT_MASK 	0x04
#define SRC_DRDY_MASK 	0x01

/* WHO_AM_I Device - REG: 0x0D */
#define MMA8X5X_WHO_AM_I_REG 	0x0D

#define MMA8653_WHO_AM_I_Device_ID 0x5A


/* XYZ_DATA_CFG Sensor Data CFG */
#define MMA8X5X_XYZ_DATA_CFG_REG 0x0E

#define FS_MASK 			0x03
#define FULL_SCALE_START_BIT	0
#define FULL_SCALE_2G (0 << FULL_SCALE_START_BIT)
#define FULL_SCALE_4G (1 << FULL_SCALE_START_BIT)
#define FULL_SCALE_8G (2 << FULL_SCALE_START_BIT)


/* PL_STATUS Portrait/Landscape Status Register*/
#define MMA8X5X_PL_STATUS_REG 0x10

#define NEWLP_MASK 	0x80
#define LO_MASK 		0x40 
#define LAPO1_MASK 	0x04
#define LAPO0_MASK 	0x02
#define BAFRO_MASK 	0x01
#define LAPO_MASK 	0x06

/* PL_CFG Portrait/Landscape Configuration Register*/
#define MMA8X5X_PL_CFG_REG 0x11

#define DBCNTM_MASK 0x80
#define PL_EN_MASK  0x40

/* PL_COUNT Portrait/Landscape Debounce Register*/
#define MMA8X5X_PL_COUNT_REG 0x12



/* PL_BF_ZCOMP Back/Front and Z Compensation Register */
#define MMA8X5X_PL_BF_ZCOMP_REG 0x13

#define BKFR1_MASK 	0x80
#define BKFR0_MASK 	0x40
#define ZLOCK2_MASK 0x04
#define ZLOCK1_MASK 0x02
#define ZLOCK0_MASK 0x01
#define BKFR_MASK 	0xC0
#define ZLOCK_MASK 	0x07

/*PL_P_L_THS Portrait to Landscape Threshold Register*/
#define MMA8X5X_PL_THS_REG 0x14

#define P_L_THS4_MASK 0x80
#define P_L_THS3_MASK 0x40
#define P_L_THS2_MASK 0x20
#define P_L_THS1_MASK 0x10
#define P_L_THS0_MASK 0x08
#define HYS2_MASK 0x04
#define HYS1_MASK 0x02
#define HYS0_MASK 0x01
#define P_L_THS_MASK 0xF8
#define HYS_MASK 0x07

/*FF_MT_CFG Freefall and Motion Configuration Register*/
#define MMA8X5X_FF_MT_CFG_REG 0x15

#define ELE_MASK 0x80
#define OAE_MASK 0x40
#define ZEFE_MASK 0x20
#define YEFE_MASK 0x10
#define XEFE_MASK 0x08

/*FF_MT_SRC Freefall and Motion Source Registers*/
#define MMA8X5X_FF_MT_SRC_REG 0x16

#define EA_MASK 0x80
#define ZHE_MASK 0x20
#define ZHP_MASK 0x10
#define YHE_MASK 0x08
#define YHP_MASK 0x04
#define XHE_MASK 0x02
#define XHP_MASK 0x01

/*
 *  FF_MT_THS Freefall and Motion Threshold Registers
 *  TRANSIENT_THS Transient Threshold Register
 */
#define MMA8X5X_FT_MT_THS_REG 0x17

#define DBCNTM_MASK 0x80
#define THS6_MASK 0x40
#define THS5_MASK 0x20
#define THS4_MASK 0x10
#define THS3_MASK 0x08
#define THS2_MASK 0x04
#define TXS1_MASK 0x02
#define THS0_MASK 0x01
#define THS_MASK  0x7F

/* FF_MT_COUNT Freefall Motion Count Registers */
#define MMA8X5X_FF_MT_COUNT_REG 0x18

/* ASLP_COUNT Auto Sleep Inactivity Timer Register */
#define MMA8X5X_ASLP_COUNT_REG 0x29


/* CTRL_REG1 System Control 1 Register */
#define MMA8X5X_CTRL_REG1 0x2A


#define FREAD_MASK 			0x02
#define ACTIVE_MASK 	  0x01
#define ASLP_RATE_MASK  0xC0
#define DR_MASK 			  0x38

#define ASLP_RATE_START_BIT		6
#define ASLP_RATE_50HZ 		(0 << ASLP_RATE_START_BIT)
#define ASLP_RATE_12_5HZ 	(1 << ASLP_RATE_START_BIT)
#define ASLP_RATE_6_25HZ 	(2 << ASLP_RATE_START_BIT)
#define ASLP_RATE_1_56HZ 	(3 << ASLP_RATE_START_BIT)
#define DATA_RATE_STRAT_BIT		3
#define DATA_RATE_800HZ 	(0 << DATA_RATE_STRAT_BIT)
#define DATA_RATE_400HZ 	(1 << DATA_RATE_STRAT_BIT)
#define DATA_RATE_200HZ 	(2 << DATA_RATE_STRAT_BIT)
#define DATA_RATE_100HZ 	(3 << DATA_RATE_STRAT_BIT)
#define DATA_RATE_50HZ   	(4 << DATA_RATE_STRAT_BIT)
#define DATA_RATE_12_5HZ 	(5 << DATA_RATE_STRAT_BIT)
#define DATA_RATE_6_25HZ 	(6 << DATA_RATE_STRAT_BIT)
#define DATA_RATE_1_56HZ 	(7 << DATA_RATE_STRAT_BIT)




/* CTRL_REG2 System Control 2 Register */
#define MMA8X5X_CTRL_REG2 0x2B

#define ST_MASK 0x80
#define RST_MASK 0x40
#define SLPE_MASK 0x04


#define SMOD_STRAT_BIT		3
#define SMOD_NORMAL 			(0 << SMOD_STRAT_BIT)
#define SMOD_LOW_NOISE 		(1 << SMOD_STRAT_BIT)
#define SMOD_HIGH_RES 		(2 << SMOD_STRAT_BIT)
#define SMOD_LOW_POWER 		(3 << SMOD_STRAT_BIT)

#define MODS_STRAT_BIT		0
#define MODS_NORMAL				(0 << MODS_STRAT_BIT)
#define MODS_LOW_NOISE 		(1 << MODS_STRAT_BIT)
#define MODS_HIGH_RES 		(2 << MODS_STRAT_BIT)
#define MODS_LOW_POWER 		(3 << MODS_STRAT_BIT)




/* CTRL_REG3 Interrupt Control Register */
#define MMA8X5X_CTRL_REG3 0x2C

#define FIFO_GATE_MASK 0x80
#define WAKE_TRANS_MASK 0x40
#define WAKE_LNDPRT_MASK 0x20
#define WAKE_PULSE_MASK 0x10
#define WAKE_FF_MT_MASK 0x08
#define IPOL_MASK 0x02
#define PP_OD_MASK 0x01

/* CTRL_REG4 Interrupt Enable Register */
#define MMA8X5X_CTRL_REG4 0x2D

#define INT_EN_ASLP_MASK 		0x80
#define INT_EN_FIFO_MASK 		0x40
#define INT_EN_TRANS_MASK 	0x20
#define INT_EN_LNDPRT_MASK 	0x10
#define INT_EN_PULSE_MASK 	0x08
#define INT_EN_FF_MT_MASK 	0x04
#define INT_EN_DRDY_MASK 		0x01

/* CTRL_REG5  */
#define MMA8X5X_CTRL_REG5 0x2E

#define INT_CFG_ASLP_MASK 	0x80
#define INT_CFG_FIFO_MASK 	0x40
#define INT_CFG_TRANS_MASK 	0x20
#define INT_CFG_LNDPRT_MASK 0x10
#define INT_CFG_PULSE_MASK 	0x08
#define INT_CFG_FF_MT_MASK 	0x04
#define INT_CFG_DRDY_MASK 	0x01


/* XYZ Offset Correction Registers */
#define MMA8X5X_OFFSET_X_REG 0x2F
#define MMA8X5X_OFFSET_Y_REG 0x30
#define MMA8X5X_OFFSET_Z_REG 0x31


/*Write a byte to the MMA8653*/
static int mma8653_write_byte(int reg, u8 val)
{
	int error;
	u8 buf[1];
	buf[0] = val;
	error = mma_iic_drv.w_reg(MMA8653_IIC_W_ADDR, reg, buf, 1);
	return error;
}

/*Read a byte from the MMA8653*/
static int mma8653_read_byte(int reg, u8 *val)
{
	int error;
  error = mma_iic_drv.r_reg(MMA8653_IIC_R_ADDR, reg, val, 1);
	return error;
}
static int mma8653_read_buf(int reg, u8 *buf, u8 len)
{
	int error;
  error = mma_iic_drv.r_reg(MMA8653_IIC_R_ADDR, reg, buf, len);
	return error;
}



status_t mma8653_init(void)
{

	u8 r_dat = 0;
  mma8653_read_byte(MMA8X5X_WHO_AM_I_REG, &r_dat);
	if(r_dat != MMA8653_WHO_AM_I_Device_ID){
		ERR_printf(r_dat);
		return STATE_INIT_ERR;
	}

	mma8653_read_byte (MMA8X5X_CTRL_REG1, &r_dat);
	mma8653_write_byte(MMA8X5X_CTRL_REG1, r_dat & (~ACTIVE_MASK));
	mma8653_read_byte (MMA8X5X_CTRL_REG1, &r_dat);
	if(r_dat & ACTIVE_MASK){
		ERR_printf(r_dat);
		return STATE_INIT_ERR;
	}
	
	mma8653_write_byte(MMA8X5X_CTRL_REG2, MODS_HIGH_RES);		//高分辨率

#if(MMA8653_Motion_Freefall_Detect)	
//	mma8653_write_byte(MMA8X5X_FF_MT_CFG_REG, 0);						//自由落体 和 运动检测配置	
//	mma8653_write_byte(MMA8X5X_FF_MT_SRC_REG, 0);
//	mma8653_write_byte(MMA8X5X_FT_MT_THS_REG, 0);
//	mma8653_write_byte(MMA8X5X_FF_MT_COUNT_REG, 0);
#endif //MMA8653_Motion_Freefall_Detect

#if(MMA8653_Auto_Sleep)
	
	
	
#endif	//MMA8653_Auto_Sleep

#if(MMA8653_USE_INT)

#else
		mma8653_write_byte(MMA8X5X_CTRL_REG1, DATA_RATE_400HZ|ACTIVE_MASK);
#endif //MMA8653_USE_INT


   
  mma8653_write_byte(MMA8X5X_XYZ_DATA_CFG_REG, MMA8653_FULL_SCALE);			// 设置量程


	mma8653_read_byte(MMA8X5X_CTRL_REG1, &r_dat);
	if((r_dat & ACTIVE_MASK) != ACTIVE_MASK){
		ERR_printf(r_dat);
		return STATE_INIT_ERR;
	}	
	return STATE_NO_ERR;
}



status_t mma8653_read_sensor_data(mma8653_data_t *sensor_dat)
{
	status_t status = STATE_NO_ERR;	
	u8 sensor_range = MMA8653_FULL_SCALE;
	
	u8 tmp_buff[6] = {0};
	
	mma8653_read_buf(MMA8X5X_STATUS_REG, tmp_buff, 1);
	if(tmp_buff[0] & STATUS_ZYXDR_MASK){
		
		mma8653_read_buf(MMA8X5X_OUT_X_MSB_REG, tmp_buff, 6);
		switch(sensor_range){
			case FULL_SCALE_2G:
					sensor_range = 2;
				break;
			case FULL_SCALE_4G:
					sensor_range = 4;
				break;
			case FULL_SCALE_8G:
					sensor_range = 8;
				break;
			default:
				ERR_printf(0);
				status = STATE_APPEAR_ERR;
			  return status;
		}
		sensor_dat->accelX = (u16)((u16)((u16)tmp_buff[0] << 8) | (u16)tmp_buff[1])/64U;
		sensor_dat->accelY = (u16)((u16)((u16)tmp_buff[2] << 8) | (u16)tmp_buff[3])/64U;
		sensor_dat->accelZ = (u16)((u16)((u16)tmp_buff[4] << 8) | (u16)tmp_buff[5])/64U;
		
		sensor_dat->accelX *= sensor_range;
		sensor_dat->accelY *= sensor_range;
		sensor_dat->accelZ *= sensor_range;	
    status = STATE_NO_ERR;		
		
	}else{
		status = STATE_APPEAR_ERR;	
	}
	return status;
}

void mma8653_test(void)
{
	static status_t init_state = STATE_INIT_ERR;
	if(init_state != STATE_NO_ERR){
		init_state = mma8653_init();
	}
	
	mma8653_data_t sensor_dat;
	
	mma8653_read_sensor_data(&sensor_dat);
	dev_printf("accelX: %d, ",sensor_dat.accelX);
	dev_printf("accelY: %d, ",sensor_dat.accelY);
	dev_printf("accelZ: %d\n",sensor_dat.accelZ);
		
}




























