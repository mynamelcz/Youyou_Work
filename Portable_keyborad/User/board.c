#include "board.h"
#include "stm32f0xx_hal.h"
#include "includes.h"

struct __sys_inf sys_inf_g;

static void printf_mem_information(void)
{
	extern unsigned int Image$$ER_IROM1$$Base;
	extern unsigned int Image$$ER_IROM1$$Limit;
	extern unsigned int Image$$ER_IROM1$$Length;   

	extern unsigned int Image$$RW_IRAM1$$Base;
	extern unsigned int Image$$RW_IRAM1$$Limit;
	extern unsigned int Image$$RW_IRAM1$$Length;     
	
	extern unsigned int Image$$RW_IRAM1$$ZI$$Base;
	extern unsigned int Image$$RW_IRAM1$$ZI$$Limit;
	extern unsigned int Image$$RW_IRAM1$$ZI$$Length;    
	
	
	unsigned int base,limit,length;
	base = (unsigned int )&Image$$ER_IROM1$$Base;
	limit = (unsigned int )&Image$$ER_IROM1$$Limit;
	length = (unsigned int )&Image$$ER_IROM1$$Length;
	app_printf("\nER_IROM1 Base = 0x%x\nER_IROM1 Limit = 0x%x\nER_IROM1 Length = %d\n",base,limit,length);
	
	base = (unsigned int )&Image$$RW_IRAM1$$Base;
	limit = (unsigned int )&Image$$RW_IRAM1$$Limit;
	length = (unsigned int )&Image$$RW_IRAM1$$Length;
	app_printf("\nRW_IRAM1 Base = 0x%x\nRW_IRAM1 Limit = 0x%x\nRW_IRAM1 Length = %d\n",base,limit,length);
	
	base = (unsigned int )&Image$$RW_IRAM1$$ZI$$Base;
	limit = (unsigned int )&Image$$RW_IRAM1$$ZI$$Limit;
	length = (unsigned int )&Image$$RW_IRAM1$$ZI$$Length;  
	app_printf("\nRW_IRAM1_ZI Base = 0x%x\nRW_IRAM1_ZI Limit = 0x%x\nRW_IRAM1_ZI Length = %d\n",base,limit,length);
}

static u8  get_cpu_reset_source(void)
{
	uint8_t ret = 0;
	if(__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST)){
		ret =	1;
	}
  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST)){
		ret =	2;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)){
		ret =	3;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)){
		ret =	4;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST)){
		ret =	5;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST)){
		ret =	6;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_OBLRST)){
		ret =	7;
	}else{}
	__HAL_RCC_CLEAR_RESET_FLAGS();
	return ret;
}



void board_printf_sys_information(void)
{
	
  app_printf(">>******** 	Power On 	********<<\n");
	app_printf(">>******** System_Information ********<<\n");
	app_printf("Code date: "__DATE__" "__TIME__"\n\r"); 
  app_printf("CPU Reset SRC: %d\n",get_cpu_reset_source());
  app_printf("SystemCoreClock£º%dHz.\n\r",SystemCoreClock);
	
	printf_mem_information();
	sys_inf_g.sys_clk = SystemCoreClock;
}
















