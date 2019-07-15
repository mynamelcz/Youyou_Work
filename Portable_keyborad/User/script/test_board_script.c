#include "test_board_script.h"
#include "task_manager.h"
#include "dev_manager.h"
#include "stm32f0xx_hal.h"
#include "led.h"
#include "key.h"
#include "l3gd20.h"
#include "mma8653.h"
#include "st480.h"
#include "tca8418.h"

static const struct key_msg_t task_key_msg;
static struct __script_hd_t *const __this_script_hd	=	&Test_Board_Script;




enum __led_state{
	LED_ON,
	LED_OFF,
	LED_TOGGLE,
};




void led_control(u8 state, u8 who)
{
	switch(state){
		case LED_ON:
		  switch(who){
				case TEST_KeyScan_TCA8418_MSG:
					RGB_TEST_LED(0);KEY_TEST_LED(1);MMA_TEST_LED(0);GYR_TEST_LED(0);
					break;
				case TEST_Magnetic_ST480M_MSG:
					RGB_TEST_LED(1);KEY_TEST_LED(0);MMA_TEST_LED(0);GYR_TEST_LED(0);
					break;
				case TEST_Acceleration_MMA8653_MSG:
					RGB_TEST_LED(0);KEY_TEST_LED(0);MMA_TEST_LED(1);GYR_TEST_LED(0);
					break;
				case TEST_AngularRate_L3GD20_MSG:
					RGB_TEST_LED(0);KEY_TEST_LED(0);MMA_TEST_LED(0);GYR_TEST_LED(1);
					break;
				default:
					break;
			}
			break;
		case LED_OFF:
			RGB_TEST_LED(0);
		  KEY_TEST_LED(0);
		  MMA_TEST_LED(0);
		  GYR_TEST_LED(0);
		  KEY_BORAD_LED(0);
			break;		
		case LED_TOGGLE:
		  switch(who){
				case TEST_KeyScan_TCA8418_MSG:
					KEY_TEST_LED_TOL();
				  KEY_BORAD_LED_TOL();
					break;
				case TEST_Magnetic_ST480M_MSG:
					RGB_TEST_LED_TOL();
					break;
				case TEST_Acceleration_MMA8653_MSG:
					MMA_TEST_LED_TOL();
					break;
				case TEST_AngularRate_L3GD20_MSG:
					GYR_TEST_LED_TOL();
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}



static void test_board_script(void *pram)
{
	(void)pram;
	osStatus state;
	status_t dev_st = STATE_NO_ERR;
	static volatile u8 test_mode = 0xff;
	/*sensor dat*/
  struct tca8418_keypad k_val;	
	L3gd20_data_t  l3gd20_dat;
	mma8653_data_t mma8653_dat;
	st480_data_t   st480_dat;
	
	task_com_msg_t msg;
	tb_script_printf("FUN:%s\n",__FUNCTION__);
	
	
	SGM_1V8_EN(1);
	led_control(LED_OFF, 0);
	while(1)
	{
		state = task_msg_pend(&__this_script_hd->task, &msg, 100);
    if(state == osEventMail){
			if(msg.msg[0] != HALF_SEC_MSG){
				tb_script_printf("TstBd Tsk:");
				tb_script_puthex((const char *)(&msg),msg.len*4+1);
			}
			switch(msg.msg[0]){
				case HALF_SEC_MSG:
				//	 tb_script_printf("script HF_MSG\n");
				   
					 break;
				
				case TEST_IO_KEY_MSG:
					tb_script_printf("TEST_IO_KEY_MSG\n");
					KEY_BORAD_LED_TOL();
					break;
				case TEST_KeyScan_TCA8418_MSG:
					tb_script_printf("KeyScan_TCA8418\n");
					dev_st = tca8418_init();
					if(dev_st != STATE_NO_ERR){
						test_mode = 0xff;
						ERR_printf(dev_st);
					}else{
						test_mode = TEST_KeyScan_TCA8418_MSG;
						led_control(LED_ON, test_mode);
					}
					break;
				case TEST_Magnetic_ST480M_MSG:
					tb_script_printf("Magnetic_ST480M\n");
					test_mode = TEST_Magnetic_ST480M_MSG;
				  led_control(LED_ON, test_mode);
					break;
				case TEST_Acceleration_MMA8653_MSG:
					tb_script_printf("Acceleration_MMA8653\n");
					dev_st = mma8653_init();
					if(dev_st != STATE_NO_ERR){
						test_mode = 0xff;
						ERR_printf(dev_st);
					}else{
						test_mode = TEST_Acceleration_MMA8653_MSG;
						led_control(LED_ON, test_mode);
					}
					break;
				case TEST_AngularRate_L3GD20_MSG:
					tb_script_printf("AngularRate_L3GD20\n");
					dev_st = L3gd20h_init();
					if(dev_st != STATE_NO_ERR){
						test_mode = 0xff;
						ERR_printf(dev_st);
					}else{
						test_mode = TEST_AngularRate_L3GD20_MSG;
						led_control(LED_ON, test_mode);
					}
					break;
				default:
				 break;
			 }		
		}
		if(state == osEventTimeout){
			 switch(test_mode){
				case TEST_KeyScan_TCA8418_MSG:
					 tca8418_read_keypad();
					 if(tca8418_key_val_get(&k_val) != 0){
						 tb_script_printf("KEY: %d ,%d\n",k_val.k_state,k_val.k_id);
						 led_control(LED_TOGGLE, test_mode);
					 }
					break;
				case TEST_Magnetic_ST480M_MSG:
			     dev_st = st480_read_sensor_data(&st480_dat);
				   if(dev_st == STATE_NO_ERR){
						 led_control(LED_TOGGLE, test_mode);
						 tb_script_printf("[ST480] T: 0x%x, X: %x, Y: %x, Z: %x\n",
															st480_dat.temperature,
															st480_dat.magneticX,
															st480_dat.magneticY,
															st480_dat.magneticZ);					 
					 }else{
					 
					 }
					break;
				case TEST_Acceleration_MMA8653_MSG:
						dev_st = mma8653_read_sensor_data(&mma8653_dat);
						if(dev_st == STATE_NO_ERR){
							led_control(LED_TOGGLE, test_mode);
							tb_script_printf("[MMA] X: %d, Y: %d, Z: %d\n",
														mma8653_dat.accelX,
														mma8653_dat.accelY,
														mma8653_dat.accelZ);		
						}		
					break;
				case TEST_AngularRate_L3GD20_MSG:
						dev_st = L3gd20h_read_sensor_data(&l3gd20_dat);
						if(dev_st == STATE_NO_ERR){
							led_control(LED_TOGGLE, test_mode);
							tb_script_printf("[L3GD] T: 0x%x, X: %4.2f, Y: %4.2f, Z: %4.2f\n",
														l3gd20_dat.temperature,
														l3gd20_dat.angular_rateX,
														l3gd20_dat.angular_rateY,
														l3gd20_dat.angular_rateZ);
							
						}
					break;	
				default:
					break;
			 } 
		 }
	}
}



static u32 test_board_script_checkin(void *pram)
{
	 tb_script_printf("FUN:%s\n",__FUNCTION__);
		return true;
}

static u32 test_board_script_init(void *pram)
{  
	tb_script_printf("FUN:%s\n",__FUNCTION__);
	task_create(&__this_script_hd->task,
								test_board_script,
								pram,
								TEST_BOARD_SCRIPT_NAME,
								TEST_BOARD_SCRIPT_STACK,
								TEST_BOARD_SCRIPT_PRIO,
								1);
	return true;
}

static u32 test_board_script_exit(void *pram)
{
  tb_script_printf("FUN:%s\n",__FUNCTION__);
	return true;
}




struct __script_hd_t Test_Board_Script = {
	.init = test_board_script_init,
	.exit = test_board_script_exit,
	.check= test_board_script_checkin,
	.key_msg = &task_key_msg,
};



static const struct key_msg_t task_key_msg = {
	.short_msg	={
/*00*/		TEST_KeyScan_TCA8418_MSG,
/*01*/		TEST_Magnetic_ST480M_MSG,
/*02*/		TEST_Acceleration_MMA8653_MSG,
/*03*/		TEST_AngularRate_L3GD20_MSG,
/*04*/		TEST_IO_KEY_MSG,
/*05*/		NO_ANY_MSG,
/*06*/		NO_ANY_MSG,
/*07*/		NO_ANY_MSG,
/*08*/		NO_ANY_MSG,
/*09*/		NO_ANY_MSG,
	},
#if(APP_LONG_KEY_EN)
	.long_msg		={
/*00*/		NO_ANY_MSG,
/*01*/		NO_ANY_MSG,
/*02*/		NO_ANY_MSG,
/*03*/		NO_ANY_MSG,
/*04*/		NO_ANY_MSG,
/*05*/		NO_ANY_MSG,
/*06*/		NO_ANY_MSG,
/*07*/		NO_ANY_MSG,
/*08*/		NO_ANY_MSG,
/*09*/		NO_ANY_MSG,	
	},
#endif
#if(APP_DOUBLE_KEY_EN)
	.double_msg	={
/*00*/		NO_ANY_MSG,
/*01*/		NO_ANY_MSG,
/*02*/		NO_ANY_MSG,
/*03*/		NO_ANY_MSG,
/*04*/		NO_ANY_MSG,
/*05*/		NO_ANY_MSG,
/*06*/		NO_ANY_MSG,
/*07*/		NO_ANY_MSG,
/*08*/		NO_ANY_MSG,
/*09*/		NO_ANY_MSG,	
	},
#endif
#if(APP_REPEAT_KEY_EN)
	.repeat_msg	={
/*00*/		NO_ANY_MSG,
/*01*/		NO_ANY_MSG,
/*02*/		NO_ANY_MSG,
/*03*/		NO_ANY_MSG,
/*04*/		NO_ANY_MSG,
/*05*/		NO_ANY_MSG,
/*06*/		NO_ANY_MSG,
/*07*/		NO_ANY_MSG,
/*08*/		NO_ANY_MSG,
/*09*/		NO_ANY_MSG,	
	},
	.repeat_up_msg={
/*00*/		NO_ANY_MSG,
/*01*/		NO_ANY_MSG,
/*02*/		NO_ANY_MSG,
/*03*/		NO_ANY_MSG,
/*04*/		NO_ANY_MSG,
/*05*/		NO_ANY_MSG,
/*06*/		NO_ANY_MSG,
/*07*/		NO_ANY_MSG,
/*08*/		NO_ANY_MSG,
/*09*/		NO_ANY_MSG,	
	},
#endif



};































































