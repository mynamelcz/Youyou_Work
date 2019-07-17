#include "key.h"

#include "includes.h"
#include "stm32f0xx_hal.h"
#include "timer.h"

#include "cmsis_os.h"



#define Mute_Name		key_mute
static osMutexDef(Mute_Name); 

struct key_hd_t{
	 u8 valbuf[KEY_VAL_CBUF_LEN];	
   struct cbuf_t cbuft; 
   struct key_val_t val;	
	 osMutexId mutex;
};



static struct key_hd_t key_hd_g;


static u8 get_key_id(void);

#define KEY_SCAN_NAME  get_key_id
Def_Key_Scan(KEY_SCAN_NAME);		  //定义，初始化 按键扫描结构 


//static u8 key_val_cbuf[KEY_VAL_CBUF_LEN];
//static struct cbuf_t key_cbuft; 

static u8 get_key_id(void)
{
	if(HAL_GPIO_ReadPin(KEY_TEST_KEY_PORT, KEY_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	KeyScan_TAC8418_TEST_KEY_ID;
	}else if(HAL_GPIO_ReadPin(RGB_TEST_KEY_PORT, RGB_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	Magnetic_ST480M_TEST_KEY_ID;
	}else if(HAL_GPIO_ReadPin(MMA_TEST_KEY_PORT, MMA_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	Acceleration_MMA8653_TEST_KEY_ID;
	}else if(HAL_GPIO_ReadPin(GYR_TEST_KEY_PORT, GYR_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	AngularRate_L3GD20_TEST_KEY_ID;
	}else if(HAL_GPIO_ReadPin(VOL_DEC_KEY_PORT, VOL_DEC_KEY_PIN) == GPIO_PIN_RESET){
		return	VOL_DEC_KEY_ID;
	}else{
		return	__NO_KEY;
	}
}

static u8 key_val_put(struct key_val_t *k_val)
{
	ASSERT(k_val);
	u8 ret = 0;
	osStatus state;
	state = osMutexWait(key_hd_g.mutex, 10);
	if(state != osOK){
		ERR_printf(state);
		return 0;
	}
	ret =  put_fifo(&key_hd_g.cbuft, (const u8*)(k_val), sizeof(struct key_val_t));
	state = osMutexRelease(key_hd_g.mutex);
	if(state != osOK){
		ERR_printf(state);
	}	
	return ret;
}
u8 key_val_get(struct key_val_t *k_val)
{
	ASSERT(k_val);
  u8 ret = 0;
	osStatus state;
	state = osMutexWait(key_hd_g.mutex, 10);
	if(state != osOK){
		ERR_printf(state);
		return 0;
	}
	ret = get_fifo(&key_hd_g.cbuft, (u8*)(k_val), sizeof(struct key_val_t));
	state = osMutexRelease(key_hd_g.mutex);
	if(state != osOK){
		ERR_printf(state);
	}	
	return ret;
}



static void key_scan_isr_loop(void)
{

	
	struct key_val_t k_val;
	
	u8 ret = 0;
	key_state_detect(Key_hd(KEY_SCAN_NAME));
	GetKeyMsg(KEY_SCAN_NAME, k_val.key_id, k_val.state);
	if(k_val.key_id != __NO_KEY){
		  ret = key_val_put(&k_val);
		  if(ret == 0){
				ERR_printf(ret);
			}
	}
}



void key_detect_init(void)
{
	key_hd_g.mutex = osMutexCreate (osMutex(Mute_Name));
  if(key_hd_g.mutex == NULL){
			ERR_printf(0);
	}
	cbuffer_init(&key_hd_g.cbuft, key_hd_g.valbuf, KEY_VAL_CBUF_LEN);
	register_timer1_handler_malloc(key_scan_isr_loop,10);
}






