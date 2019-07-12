#ifndef __MSG_H
#define __MSG_H





enum __msg{
	/*System Msg*/
	HALF_SEC_MSG,
	
	
	/*Main Task Msg*/
	MAIN_TASK_MSG_MIN,
	
	
	
	
	MAIN_TASK_MSG_MAX,
	
	
	/*Key Msg*/
	TEST_KeyScan_TCA8418_MSG,
	TEST_Magnetic_ST480M_MSG,
	TEST_Acceleration_MMA8653_MSG,
	TEST_AngularRate_L3GD20_MSG,
	TEST_IO_KEY_MSG,




	
	
	NO_ANY_MSG	=	0xff,

};


























#endif
















