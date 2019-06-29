#include "TCA8418.h"
#include "iic_drv.h"




/* TCA8418 register offsets */
#define REG_CFG							0x01
#define REG_INT_STAT				0x02
#define REG_KEY_LCK_EC			0x03		/*BIT[3:0]:Event Num*/

#define REG_KEY_EVENT_A			0x04		/*Event*/
#define REG_KEY_EVENT_B			0x05
#define REG_KEY_EVENT_C			0x06
#define REG_KEY_EVENT_D			0x07
#define REG_KEY_EVENT_E			0x08
#define REG_KEY_EVENT_F			0x09
#define REG_KEY_EVENT_G			0x0A
#define REG_KEY_EVENT_H			0x0B
#define REG_KEY_EVENT_I			0x0C
#define REG_KEY_EVENT_J			0x0D

#define REG_KP_LCK_TIMER		0x0E

#define REG_UNLOCK1					0x0F		/*设置解锁 KEY1 */
#define REG_UNLOCK2					0x10		/*设置解锁 KEY2 */

#define REG_GPIO_INT_STAT1	0x11
#define REG_GPIO_INT_STAT2	0x12
#define REG_GPIO_INT_STAT3	0x13

#define REG_GPIO_DAT_STAT1	0x14
#define REG_GPIO_DAT_STAT2	0x15
#define REG_GPIO_DAT_STAT3	0x16

#define REG_GPIO_DAT_OUT1		0x17
#define REG_GPIO_DAT_OUT2		0x18
#define REG_GPIO_DAT_OUT3		0x19

#define REG_GPIO_INT_EN1		0x1A
#define REG_GPIO_INT_EN2		0x1B
#define REG_GPIO_INT_EN3		0x1C

#define REG_KP_GPIO1				0x1D		/*Enable Row & Col Pin*/
#define REG_KP_GPIO2				0x1E
#define REG_KP_GPIO3				0x1F

#define REG_GPI_EM1					0x20		/*Enable GPI Event */
#define REG_GPI_EM2					0x21
#define REG_GPI_EM3					0x22

#define REG_GPIO_DIR1				0x23		/*	0: Input					1: Output	*/
#define REG_GPIO_DIR2				0x24
#define REG_GPIO_DIR3				0x25

#define REG_GPIO_INT_LVL1		0x26		/*	0: 下降沿/低电平	1: 上升沿/高电平 */
#define REG_GPIO_INT_LVL2		0x27   
#define REG_GPIO_INT_LVL3		0x28

#define REG_DEBOUNCE_DIS1		0x29		/* 0： 使能消抖  */
#define REG_DEBOUNCE_DIS2		0x2A
#define REG_DEBOUNCE_DIS3		0x2B

#define REG_GPIO_PULL1			0x2C		/* 0:	 使能上拉 */
#define REG_GPIO_PULL2			0x2D
#define REG_GPIO_PULL3			0x2E

/* TCA8418 bit definitions */
#define CFG_AI						BIT(7)		/* 写寄存器的模式 1：地址自动递增*/
#define CFG_GPI_E_CFG			BIT(6)
#define CFG_OVR_FLOW_M		BIT(5)		/* 溢出模式选择 */
#define CFG_INT_CFG				BIT(4)
#define CFG_OVR_FLOW_IEN	BIT(3)		/* FIFO 溢出中断*/
#define CFG_K_LCK_IEN			BIT(2)		/* Unlock INT		*/
#define CFG_GPI_IEN				BIT(1)		/* IO按键	INT   */
#define CFG_KE_IEN				BIT(0)		/* 矩阵按键 INT */

#define INT_STAT_CAD_INT			BIT(4)
#define INT_STAT_OVR_FLOW_INT	BIT(3)
#define INT_STAT_K_LCK_INT		BIT(2)
#define INT_STAT_GPI_INT			BIT(1)
#define INT_STAT_K_INT				BIT(0)

/* TCA8418 register masks */
#define KEY_LCK_EC_KEC		0x7
#define KEY_EVENT_CODE		0x7f
#define KEY_EVENT_VALUE		0x80


#define KEY_ARRY_ROW				0x3f			//    0011 1111
#define KEY_ARRY_COL_L		  0x1f			//    0001 1111	
#define KEY_ARRY_COL_H		  0x00			//    



#define TCA_EVENT_BUF_LEN				(16)
static u8 tca_event_buf[TCA_EVENT_BUF_LEN];
static struct cbuf_t event_cbuft;





struct tca8418_keypad{
	u8 key_id;
};

/*
 * Write a byte to the TCA8418
 */
static int tca8418_write_byte(int reg, u8 val)
{
	int error;
	u8 buf[1];
	buf[0] = val;
	error = tca_iic_drv.w_reg(TC8418_IIC_W_ADDR, reg, buf, 1);
	return error;
}

/*
 * Read a byte from the TCA8418
 */
static int tca8418_read_byte(int reg, u8 *val)
{
	int error;
  error = tca_iic_drv.r_reg(TC8418_IIC_R_ADDR, reg, val, 1);
	return error;
}

static void tca8418_read_keypad(struct tca8418_keypad *keypad_data)
{

	u8 error = 0;
	u8 ret = 0;
	u8 event_cnt = 0;
	/* Initial read of the key event FIFO */
	error |= tca8418_read_byte(REG_INT_STAT, &ret);
	if(ret)
		dev_printf("error = %d, REG_INT_STAT: 0x%x\n",error, ret);

	/* Matrix Key Event */
	if(ret & INT_STAT_K_INT){			
		 error |= tca8418_write_byte(REG_INT_STAT, INT_STAT_K_INT);		//clear
		 error |= tca8418_read_byte(REG_KEY_LCK_EC, &ret);
		 event_cnt = ret & 0x0F;
		 dev_printf("event_cnt: %d\n", event_cnt);
		 if(event_cnt){
				while(event_cnt--){
						error |= tca8418_read_byte(REG_KEY_EVENT_A, &ret);
            if(ret&KEY_EVENT_VALUE){
								dev_printf("Press   Key ID: %d\n", ret&KEY_EVENT_CODE);	
						}else{
								dev_printf("Release Key ID: %d\n", ret&KEY_EVENT_CODE);
						}
					  
				}
		 }
	}
	/* GPI Key Event */
	if(ret & INT_STAT_GPI_INT){
		tca8418_write_byte(REG_INT_STAT, INT_STAT_GPI_INT);	
	}
	/* Keypad Lock INT */
	if(ret & INT_STAT_K_LCK_INT){
		tca8418_write_byte(REG_INT_STAT, INT_STAT_K_LCK_INT);	
	}
	/* FIFO Overflow INT */
	if(ret & INT_STAT_OVR_FLOW_INT){
		tca8418_write_byte(REG_INT_STAT, INT_STAT_OVR_FLOW_INT);		
	}
	/* CTRL-ALT-DEL key  */
	if(ret & INT_STAT_CAD_INT){
		tca8418_write_byte(REG_INT_STAT, INT_STAT_CAD_INT);		
	}
}


/*
 * Configure the TCA8418 for keypad operation
 */
status_t tca8418_configure(void)
{
	
  status_t error = STATE_NO_ERR;
	/* Write config register, if this fails assume device not present */
	tca8418_write_byte(REG_CFG,
														 CFG_INT_CFG |				
														 CFG_OVR_FLOW_IEN |		
														 CFG_KE_IEN);

	tca8418_write_byte(REG_INT_STAT, 0x1F);			//clear
	/* Set registers to keypad mode */
	tca8418_write_byte(REG_KP_GPIO1, KEY_ARRY_ROW);
	tca8418_write_byte(REG_KP_GPIO2, KEY_ARRY_COL_L);
	tca8418_write_byte(REG_KP_GPIO3, KEY_ARRY_COL_H);

	/* Enable column debouncing */
	tca8418_write_byte(REG_DEBOUNCE_DIS1, KEY_ARRY_ROW);
	tca8418_write_byte(REG_DEBOUNCE_DIS2, KEY_ARRY_COL_L);
	tca8418_write_byte(REG_DEBOUNCE_DIS3, KEY_ARRY_COL_H);

	return error;
}

status_t tca8418_init(void)
{
	status_t ret = STATE_NO_ERR;
	ret = tca8418_configure();
	if(ret != STATE_NO_ERR){
		ERR_printf(ret);
		return ret;
	}
	if(cbuffer_init(&event_cbuft, tca_event_buf, TCA_EVENT_BUF_LEN)){
		ERR_printf(ret);
		return ret;
	}
	return ret;
}



void test_tca8418(void)
{
	static status_t state = STATE_INIT_ERR;
	if(state == STATE_INIT_ERR){
	  state = tca8418_init();
	}
	tca8418_read_keypad(NULL);
}
























