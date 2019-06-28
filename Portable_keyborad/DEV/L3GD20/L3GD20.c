#include "L3GD20.h"
#include "iic_drv.h"

#define L3GD20H_WHO_AM_I_REG        		0x0FU

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

#define L3GD20H_CTRL2_REG                   0x21U

#define L3GD20H_CTRL3_REG                   0x22U



#define L3GD20H_CTRL4_REG                   0x23U
#define BDU_MASK	(1<<7)
#define BLE_MASK  (2<<6)
#define FULL_SCALE_MASK		 (3<<4)
#define FULL_SCALE_250DPS	 (0<<4)
#define FULL_SCALE_500DPS	 (1<<4)
#define FULL_SCALE_2000DPS (2<<4)



#define L3GD20H_CTRL5_REG                   0x24U

#define L3GD20H_REFERENCE_REG               0x25U

#define L3GD20H_OUT_TEMP_REG                0x26U

#define L3GD20H_STATUS_REG_REG              0x27U
#define ZYX_OVER_W_MASK	(1<<7)
#define Z_OVER_W_MASK		(1<<6)
#define Y_OVER_W_MASK		(1<<5)
#define X_OVER_W_MASK		(1<<4)
#define ZYX_DAT_OK_MASK	(1<<3)
#define Z_DAT_OK_MASK		(1<<2)
#define Y_DAT_OK_MASK		(1<<1)
#define X_DAT_OK_MASK		(1<<0)

#define L3GD20H_OUT_X_L_REG                 0x28U
#define L3GD20H_OUT_X_H_REG                 0x29U
#define L3GD20H_OUT_Y_L_REG                 0x2AU
#define L3GD20H_OUT_Y_H_REG                 0x2BU
#define L3GD20H_OUT_Z_L_REG                 0x2CU
#define L3GD20H_OUT_Z_H_REG                 0x2DU

#define L3GD20H_FIFO_CTRL_REG               0x2EU
#define L3GD20H_FIFO_SRC_REG                0x2FU

#define L3GD20H_IG_CFG_REG                  0x30U
#define L3GD20H_IG_SRC_REG                  0x31U


#define L3GD20H_IG_THS_XH_REG               0x32U
#define L3GD20H_IG_THS_XL_REG               0x33U
#define L3GD20H_IG_THS_YH_REG               0x34U
#define L3GD20H_IG_THS_YL_REG               0x35U
#define L3GD20H_IG_THS_ZH_REG               0x36U
#define L3GD20H_IG_THS_ZL_REG               0x37U

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




/**
  * @brief  These functions convert raw-data into engineering units.
*/
static float l3gd20h_from_fs245_to_mdps(s16 lsb)
{
  return ((float)lsb * 8.75f);
}

static float l3gd20h_from_fs500_to_mdps(s16 lsb)
{
  return ((float)lsb * 17.50f);
}

static float l3gd20h_from_fs2000_to_mdps(s16 lsb)
{
  return ((float)lsb * 70.0f);
}

static float l3gd20h_from_lsb_to_celsius(s16 lsb)
{
  return ((float)lsb +25.0f);
}




/**
  * @brief  Gyroscope data rate selection..[set]
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


/**
  * @brief  Block data update.[set]
  */
u32 l3gd20h_block_data_update_set(u8 val)
{
  u8 ctrl4;
  s32 ret;

  ret = L3gd20h_read_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  if(ret == 0){

    ret = L3gd20h_write_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  }
  return ret;
}



u32 L3gd20h_block_data_update_set(u8 val)
{
  u8 ctrl4;
  u32 ret;
  ret = L3gd20h_read_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  if(ret == 0){
    ret = L3gd20h_write_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  }
  return ret;
}

u32 l3gd20h_gy_full_scale_set(u8 val)
{
  u8 ctrl4;
  u32 ret;
  ret = L3gd20h_read_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  if(ret == 0){
 
    ret = L3gd20h_write_reg(L3GD20H_CTRL4_REG, (u8*)&ctrl4, 1);
  }
  return ret;
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

}









void L3gd20h_test(void)
{
	static status_t state = STATE_INIT_ERR;
	if(state == STATE_INIT_ERR){
		state = L3gd20h_init();
	}
}







