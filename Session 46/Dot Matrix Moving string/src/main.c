#include "STD_Types.h"
#include "BIT_MATH.h"


#include "RCC_Interface.h"
#include "RCC_Private.h"
#include "GPIO_Interface.h"
#include "SYS_TICK_Interface.h"
#include "Dot_Matrix_Interface.h"

void App_delayMs(u32 Copy_u32Delay);
void app_init(void);


 u8 GLOB_u8DataArr[160] = {

		 	0, 0, 6, 73, 73, 73, 48, 0, // s
		    0, 0, 0, 127, 73, 73, 65, 0, // e
			0, 0, 0, 253, 0, 0, 0, 0,  //i
			0, 0, 0, 254, 18, 18, 2, 0, //f

};


int main()
{
	app_init();

  while (1)
    {

	  Dot_Matrix_void_Display_sliding(GLOB_u8DataArr);

	  //Dot_Matrix_void_Display_sliding(GLOB_u8DataArr_2);


    }



  return 0;
}



void app_init(void)
{
	RCC_void_Init_Sys_Clk();

	RCC_void_Enable_Peripheral_Clk( AHB1,  RCC_AHB1ENR_GPIOAEN);
	RCC_void_Enable_Peripheral_Clk( AHB1,  RCC_AHB1ENR_GPIOBEN);

	Dot_Matrix_void_Init();

}


void App_delayMs(u32 Copy_u32Delay)
{
	for(u32 Local_u32Counter = 0; Local_u32Counter < Copy_u32Delay*300; Local_u32Counter++)
	{
		asm("NOP");
	}
}