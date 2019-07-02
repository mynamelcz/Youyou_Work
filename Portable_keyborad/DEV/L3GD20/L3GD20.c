#include "L3GD20.h"
#include "iic_drv.h"

/* REG: ID*/
#define L3GD20H_WHO_AM_I_REG        		0x0FU
/* REG: L3GD20H_CTRL1_REG*/
#define L3GD20H_CTRL1_REG               0x20U
#define DR_START_BIT	6
#define BW_START_BIT	4
#define ODR95HZ_Cut12_5HZ     ((0 << DR_START_BIT)|(0 << BW_START_BIT))
#define ODR95HZ_Cut25HZ       ((0 << DR_START_BIT)|(1 << BW_START_BIT))
#define ODR190HZ_Cut12_5HZ    ((1 << DR_START_BIT)|(0 << BW_START_BIT))
#define ODR190HZ_Cut25HZ      ((1 << DR_START_BIT)|(1 << BW_START_BIT))
#define ODR190HZ_Cut50HZ      ((1 << DR_START_BIT)|(2 << BW_START_BIT))
#define ODR190HZ_Cut70HZ      ((1 << DR_START_BIT)|(3 << BW_START_BIT))
#define ODR380HZ_Cut20HZ    	((2 << DR_START_BIT)|(0 << BW_START_BIT))
#define ODR380HZ_Cut25HZ    	((2 << DR_START_BIT)|(1 << BW_START_BIT))
#define ODR380HZ_Cut50HZ    	((2 << DR_START_BIT)|(2 << BW_START_BIT))
#define ODR380HZ_Cut100HZ   	((2 << DR_START_BIT)|(3 << BW_START_BIT))
#define ODR760HZ_Cut30HZ    	((3 << DR_START_BIT)|(0 << BW_START_BIT))
#define ODR760HZ_Cut35HZ    	((3 << DR_START_BIT)|(1 << BW_START_BIT))
#define ODR760HZ_Cut50HZ    	((3 << DR_START_BIT)|(2 << BW_START_BIT))
#define ODR760HZ_Cut100HZ    	((3 << DR_START_BIT)|(3 << BW_START_BIT))
#define ODR_BW_MASK	(0xf0)
#define POWER_MASK	(1<<3)


#define Zen_MASK		(1<<2)
#define Yen_MASK		(1<<1)
#define Xen_MASK		(1<<0)
#define XYZ_EN_MASK		(Zen_MASK|Yen_MASK|Xen_MASK)


#define POWER_ON	(POWER_MASK)
#define POWER_OFF	(0)

/* REG: */
#define L3GD20H_CTRL2_REG                   0x21U
/* REG: */
#define L3GD20H_CTRL3_REG                   0x22U


/* REG: CTRL4*/
#define L3GD20H_CTRL4_REG                   0x23U
#define BDU_MASK		  (1<<7)
#define BLE_MASK    	(2<<6)
#define FULL_SCALE_MASK		 (3<<4)

#define FULL_SCALE_250DPS	 (0<<4)
#define FULL_SCALE_500DPS	 (1<<4)
#define FULL_SCALE_2000DPS   (2<<4)
#define Big_Endian			 (BLE_MASK)
#define Little_Endian		 (0)

/* REG: CTRL5 */
#define L3GD20H_CTRL5_REG                   0x24U
/* REG: */
#define L3GD20H_REFERENCE_REG               0x25U
/* REG: */
#define L3GD20H_OUT_TEMP_REG                0x26U
/* REG: STATUS*/
#define L3GD20H_STATUS_REG                  0x27U
#define ZYX_OVER_W_MASK	    (1<<7)
#define Z_OVER_W_MASK		(1<<6)
#define Y_OVER_W_MASK		(1<<5)
#define X_OVER_W_MASK		(1<<4)
#define ZYX_DAT_OK_MASK	    (1<<3)
#define Z_DAT_OK_MASK		(1<<2)
#define Y_DAT_OK_MASK		(1<<1)
#define X_DAT_OK_MASK		(1<<0)
/* REG: */
#define L3GD20H_OUT_X_L_REG                 0x28U
#define L3GD20H_OUT_X_H_REG                 0x29U
#define L3GD20H_OUT_Y_L_REG                 0x2AU
#define L3GD20H_OUT_Y_H_REG                 0x2BU
#define L3GD20H_OUT_Z_L_REG                 0x2CU
#define L3GD20H_OUT_Z_H_REG                 0x2DU
/* REG: */
#define L3GD20H_FIFO_CTRL_REG               0x2EU
#define L3GD20H_FIFO_SRC_REG                0x2FU
/* REG: */
#define L3GD20H_IG_CFG_REG                  0x30U
#define L3GD20H_IG_SRC_REG                  0x31U

/* REG: */
#define L3GD20H_IG_THS_XH_REG               0x32U
#define L3GD20H_IG_THS_XL_REG               0x33U
#define L3GD20H_IG_THS_YH_REG               0x34U
#define L3GD20H_IG_THS_YL_REG               0x35U
#define L3GD20H_IG_THS_ZH_REG               0x36U
#define L3GD20H_IG_THS_ZL_REG               0x37U
/* REG: */
#define L3GD20H_IG_DURATION_REG             0x38U


static int L3gd20h_write_reg(u8 reg, u8 *buf, u16 len)
{
  int res = 0;
	res = L3gd_iic_drv.w_reg(L3GD20_IIC_W_ADDR, reg, buf, len);
  return res;
}

static int L3gd20h_read_reg(u8 reg, u8 *buf, u16 len)
{
  int res = 0;
	res = L3gd_iic_drv.r_reg(L3GD20_IIC_R_ADDR, reg, buf, len);
  return res;
}


/*
 ** Power Dwon / On ..[set]
 */
u32 l3gd20h_dev_power_ctr(u8 val)
{
  u8 ctrl1;
  u32 ret;
  ret = L3gd20h_read_reg(L3GD20H_CTRL1_REG, (u8*)&ctrl1, 1);
  if(ret == 0){
    ctrl1 &= (~POWER_MASK);
	ctrl1 |= val;     
    ret = L3gd20h_write_reg(L3GD20H_CTRL1_REG, (u8*)&ctrl1, 1);
  }
  return ret;
}

u32 l3gd20h_gy_axis_set(u8 val)
{
  u8 ctrl1;
  u32 ret;

  ret = L3gd20h_read_reg(L3GD20H_CTRL1_REG, (u8*)&ctrl1, 1);
  if(ret == 0) {
	ctrl1 &= (~XYZ_EN_MASK);
	ctrl1 |= val; 
    ret = L3gd20h_write_reg(L3GD20H_CTRL1_REG, (u8*)&ctrl1, 1);
  }
  return ret;
}


/*
 ** Big/Little Endian data selection..[set]
 */
u32 l3gd20h_dev_data_format_set(u8 val)
{
  u8 ctrl4;
  u32 ret;
  ret = L3gd20h_read_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  if(ret == 0){
    ctrl4 &= (~BLE_MASK);
	ctrl4 |= val;     
    ret = L3gd20h_write_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  }
  return ret;
}

/*
** 数据更新方式  [set]
*/
u32 l3gd20h_block_data_update_set(u8 val)
{
  u8 ctrl4;
  u32 ret;
  ret = L3gd20h_read_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  if(ret == 0){
    ctrl4 &= (~BDU_MASK);
	ctrl4 |= val; 
    ret = L3gd20h_write_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  }
  return ret;
}


/*
** data rate selection..[set]
*/
static u32 l3gd20h_gy_data_rate_set(u8 val)
{
	u8 r_dat = 0;
  u32 ret;
  ret = L3gd20h_read_reg(L3GD20H_CTRL1_REG, (u8*)&r_dat, 1);
  if(ret == 0){
    r_dat &=  (~ODR_BW_MASK);
		r_dat |= val;
    ret = L3gd20h_write_reg(L3GD20H_CTRL1_REG, (u8*)&r_dat, 1);
  }
  return ret;
}


/*
** data range selection..[set]
*/
static u32 l3gd20h_gy_full_scale_set(u8 val)
{
  u8 ctrl4;
  u32 ret;
  ret = L3gd20h_read_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  if(ret == 0){
    ctrl4 &= (~FULL_SCALE_MASK);
	ctrl4 = val;
    ret = L3gd20h_write_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  }
  return ret;
}
static u32 l3gd20h_gy_full_scale_get(u8 *val)
{
  u8 ctrl4;
  u32 ret;
  ret = L3gd20h_read_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  ctrl4 &= FULL_SCALE_MASK;
  *val = ctrl4;
  return ret;
}
/*
** status reg ..[get]
*/
u32 l3gd20h_dev_status_get(u8 *val)
{

  u32 ret;
  ret = L3gd20h_read_reg(L3GD20H_STATUS_REG, (u8*)val, 1);
  return ret;
}

u32 L3gd20h_temperature_raw_get(u8 *buff)
{
  u32 ret;
  ret = L3gd20h_read_reg(L3GD20H_OUT_TEMP_REG, buff, 1);
  return ret;
}

/*
** These functions convert raw-data into engineering units.
*/
static status_t L3gd20h_from_fs_to_mdps(float *ret, s16 lsb)
{
  u8 full_scale;
  l3gd20h_gy_full_scale_get(&full_scale);
  switch(full_scale){
	  case FULL_SCALE_250DPS:
		  *ret = ((float)lsb * 8.75f);
	      break;
	  case FULL_SCALE_500DPS:
		  *ret = ((float)lsb * 17.50f);
	      break;
	  case FULL_SCALE_2000DPS:
		  *ret =  ((float)lsb * 70.0f);
	      break;
	  default:
		  ERR_printf(full_scale);
		  *ret = 0;
          return STATE_APPEAR_ERR;  	  
  }
  return STATE_NO_ERR;  
}
status_t L3gd20h_read_sensor_data(L3gd20_data_t *sensor_dat)
{
	u8 state_reg = 0;
	status_t error = STATE_NO_ERR;
	L3gd20_axis3bit16_t xyz_dat;
	l3gd20h_dev_status_get(&state_reg);
	dev_printf("state :0x%x\n",state_reg);
	if(state_reg & ZYX_DAT_OK_MASK){
		
		  if(state_reg & Z_DAT_OK_MASK){
				L3gd20h_read_reg(L3GD20H_OUT_Z_L_REG, (u8*)(&xyz_dat.u8bit[4]), 1);
				L3gd20h_read_reg(L3GD20H_OUT_Z_H_REG, (u8*)(&xyz_dat.u8bit[5]), 1);			
			}
		  if(state_reg & Y_DAT_OK_MASK){
				L3gd20h_read_reg(L3GD20H_OUT_Y_L_REG, (u8*)(&xyz_dat.u8bit[2]), 1);
				L3gd20h_read_reg(L3GD20H_OUT_Y_H_REG, (u8*)(&xyz_dat.u8bit[3]), 1);			
			}
		  if(state_reg & X_DAT_OK_MASK){
				L3gd20h_read_reg(L3GD20H_OUT_X_L_REG, (u8*)(&xyz_dat.u8bit[0]), 1);
				L3gd20h_read_reg(L3GD20H_OUT_X_H_REG, (u8*)(&xyz_dat.u8bit[1]), 1);			
			}


		  dev_puthex((const char *)xyz_dat.u8bit,6);
      L3gd20h_temperature_raw_get(&sensor_dat->temperature);
	 		dev_printf("[L3GD] T: 0x%x, X: %d, Y: %d, Z: %d\n",
								sensor_dat->temperature,
								xyz_dat.i16bit[0],
	              xyz_dat.i16bit[1],
								xyz_dat.i16bit[2]);		
		
		 error |= L3gd20h_from_fs_to_mdps(&sensor_dat->angular_rateX, xyz_dat.i16bit[0]);
		 error |= L3gd20h_from_fs_to_mdps(&sensor_dat->angular_rateY, xyz_dat.i16bit[1]);
		 error |= L3gd20h_from_fs_to_mdps(&sensor_dat->angular_rateZ, xyz_dat.i16bit[2]);
	}
	if(error != STATE_NO_ERR){
		  ERR_printf(error);
          return STATE_APPEAR_ERR;  	
	}
	return STATE_NO_ERR;

}
















status_t L3gd20h_init(void)
{
	status_t state = STATE_NO_ERR;
	u8 dev_id = 0;
	L3gd20h_read_reg(L3GD20H_WHO_AM_I_REG, (u8*)&dev_id, 1);
	if(dev_id != L3GD20H_ID){
		ERR_printf(dev_id);
		state = STATE_INIT_ERR;
		return state;
	}

	l3gd20h_dev_data_format_set(Little_Endian);
	l3gd20h_block_data_update_set(1);
	l3gd20h_gy_full_scale_set(FULL_SCALE_2000DPS);
	l3gd20h_gy_data_rate_set(ODR95HZ_Cut12_5HZ);
	l3gd20h_gy_axis_set(Xen_MASK|Yen_MASK|Zen_MASK);
	l3gd20h_dev_power_ctr(POWER_ON);
	
	
//	u8 reg = 0;
//	dev_printf("L3GD20H_WHO_AM_I_REG :0x%x\n",dev_id);
//	L3gd20h_read_reg(L3GD20H_CTRL1_REG, (u8*)&reg, 1);
//	dev_printf("L3GD20H_CTRL1_REG :0x%x\n",reg);
//	L3gd20h_read_reg(L3GD20H_CTRL2_REG, (u8*)&reg, 1);
//	dev_printf("L3GD20H_CTRL2_REG :0x%x\n",reg);	
//	L3gd20h_read_reg(L3GD20H_CTRL3_REG, (u8*)&reg, 1);
//	dev_printf("L3GD20H_CTRL3_REG :0x%x\n",reg);	
//	L3gd20h_read_reg(L3GD20H_CTRL4_REG, (u8*)&reg, 1);
//	dev_printf("L3GD20H_CTRL4_REG :0x%x\n",reg);	
//	L3gd20h_read_reg(L3GD20H_CTRL5_REG, (u8*)&reg, 1);
//	dev_printf("L3GD20H_CTRL5_REG :0x%x\n",reg);		
	
	return state;
}









void L3gd20h_test(void)
{   
	L3gd20_data_t sensor_dat;
	static status_t state = STATE_INIT_ERR;
	if(state == STATE_INIT_ERR){
	
		state = L3gd20h_init();
	}

	L3gd20h_read_sensor_data(&sensor_dat);
//	dev_printf("[L3GD] T: 0x%x, X: %4.2f, Y: %4.2f, Z: %4.2f\n",
//								sensor_dat.temperature,
//								sensor_dat.angular_rateX,
//	              sensor_dat.angular_rateY,
//								sensor_dat.angular_rateZ);
	
}







