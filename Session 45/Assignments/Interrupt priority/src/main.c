#include "../include/LIB/STD_Types.h"
#include "../include/LIB/BIT_MATH.h"


#include "../include/MCAL/RCC/RCC_Interface.h"
#include "../include/MCAL/RCC/RCC_Private.h"
#include "../include/MCAL/GPIO/GPIO_Interface.h"
#include "../include/MCAL/SYS_TICK/SYS_TICK_Interface.h"
#include "../include/MCAL/NVIC/NVIC_Interface.h"
#include "../include/MCAL/EXTI/EXTI_Interface.h"

#include "../include/HAL/SSD/SSD_Interface.h"

void App_delayMs(u32 Copy_u32Delay);
void app_init(void);

EXTI_t my_EXTI_4 = {.EXTI = 4,
				  .EXTI_MASK = Unmaskable,
				  .EXTI_SRC_Port = EXTI_SOURCE_GPIOA,
				  .Trigger = FALLING_EDGE
};

int main()
{
	app_init();

	//EXTI pin configuration
	GPIO_void_Set_Pin_Mode(GPIOA , PIN_4 , INPUT);
	GPIO_void_Set_Pin_Pull_State(GPIOA , PIN_4 ,PULL_UP);

	//configuring output pins for led animation
	for(u8 i = PIN_0 ; i <= PIN_7 ; i++)
	{
		GPIO_void_Set_Pin_Mode(GPIOB , i , OUTPUT);
		GPIO_void_Set_Pin_Type(GPIOB , i , push_pull);
		GPIO_void_Set_Pin_Speed(GPIOB , i , Medium_speed );
	}

	//GPIO_void_Set_Pin_Value_Atomic(GPIOB , PIN_3 , SET);

	EXTI_void_EXTIx_enable(&my_EXTI_4);

  while (1)
    {


	  for(u8 i = PIN_0 ; i <= PIN_7 ; i++)
	  {
		  //SYS_TICK_void_Set_Busy_Wait(1000000);
		  App_delayMs(600);
		  GPIO_void_Set_Pin_Value_Atomic(GPIOB , i , SET);

	  }
	  for(s8 i = PIN_7 ; i >= 0 ; i--)
	  {
		  App_delayMs(600);
	  	  GPIO_void_Set_Pin_Value_Atomic(GPIOB , i , RST);
	  }

	  NVIC_void_Set_pending_Flag(37);

    }



  return 0;
}



void app_init(void)
{
	RCC_void_Init_Sys_Clk();

	RCC_void_Enable_Peripheral_Clk( AHB1,  RCC_AHB1ENR_GPIOAEN);
	RCC_void_Enable_Peripheral_Clk( AHB1,  RCC_AHB1ENR_GPIOBEN);

	//SYS_TICK_void_Init();

	NVIC_void_set_Priority_Config(NVIC_Priority_4G_4SG);
	//USART1 in group
	NVIC_void_Set_Priority(37 , 3 , 2);


	NVIC_void_Set_Priority(4, 1 , 0);


	SSD_void_Initialize();
	//NVIC_void_Enable_PerInt(6);
	NVIC_void_Enable_PerInt(37);

	EXTI_void_EXTI_init();
}

void EXTI4_IRQHandler()
{
//	for(u8 l_counter = 0 ; l_counter<=9 ; l_counter++)
//	{
//		//SYS_TICK_void_Set_Busy_Wait(1110000);
//		App_delayMs(6000);
//		SSD_void_write(l_counter);
//		if( 6 == l_counter)
//		{
//			NVIC_void_Set_pending_Flag(37);
//		}
//	}
	//==========================================
	for(s8 i = PIN_7 ; i >= 0 ; i--)
			  {
			(*((volatile u32 *)(0x40020400 + 0X14))) = 0x00ff;

			App_delayMs(6000);
			(*((volatile u32 *)(0x40020400 + 0X14))) = 0x0000;
			App_delayMs(6000);
			  }

	//NVIC_void_CLR_Pending_Flag(4);
	(*((volatile u32*)(0x40013C00 + 0x14))) = 0x01 << 4;
}

void App_delayMs(u32 Copy_u32Delay)
{
	for(u32 Local_u32Counter = 0; Local_u32Counter < Copy_u32Delay*300; Local_u32Counter++)
	{
		asm("NOP");
	}
}

void USART1_IRQHandler()
{



	//========================
	for(u8 l_counter = 0 ; l_counter<=9 ; l_counter++)
		{
			//SYS_TICK_void_Set_Busy_Wait(1110000);
			App_delayMs(6000);
			SSD_void_write(l_counter);
			if( 6 == l_counter)
			{
				//NVIC_void_Set_pending_Flag(37);
			}
		}
}
