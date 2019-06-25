#include "iic_drv.h"
#include "stm32f0xx_hal.h"





extern I2C_HandleTypeDef hi2c2;
extern DMA_HandleTypeDef hdma_i2c2_rx;
extern DMA_HandleTypeDef hdma_i2c2_tx;



u32 static iic2_write(u16 addr, u8 *buf, u16 len)
{
	 ASSERT(buf);
	 HAL_StatusTypeDef res; 
	 res = HAL_I2C_Master_Transmit(&hi2c2, addr, buf, len, 0xFF);
	 if(HAL_OK != res){
			ERR_printf(res);
	 }
	 return res;
}
u32 static iic2_read(u16 addr, u8 *buf, u16 len)
{
	ASSERT(buf);
	HAL_StatusTypeDef res; 
	res = HAL_I2C_Master_Receive(&hi2c2, addr, buf, len, 0xFF);
  if(HAL_OK != res){
	   ERR_printf(res);
	}
	return res;
}

u32 static iic2_write_reg(u16 addr, u16 reg, u8 *buf, u16 len)
{
	ASSERT(buf);
	HAL_StatusTypeDef res; 
  res = HAL_I2C_Mem_Write(&hi2c2, addr, reg, I2C_MEMADD_SIZE_8BIT, buf, len, 0xFF);
  if(HAL_OK != res){
	   ERR_printf(res);
	}
	return res;
}
u32 static iic2_read_reg(u16 addr, u16 reg, u8 *buf, u16 len)
{
	ASSERT(buf);
	HAL_StatusTypeDef res; 
  res = HAL_I2C_Mem_Read(&hi2c2, addr, reg, I2C_MEMADD_SIZE_8BIT, buf, len, 0xFF);
  if(HAL_OK != res){
	   ERR_printf(res);
	}
	return res;
}



const struct iic_master_drv IIC2_DRIVER_HDL = {
	.write = iic2_write,
	.read  = iic2_read, 
	.w_reg = iic2_write_reg,
	.r_reg = iic2_read_reg,
};











































