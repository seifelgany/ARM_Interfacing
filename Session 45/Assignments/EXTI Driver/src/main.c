#include "../include/LIB/STD_Types.h"
#include "../include/LIB/BIT_MATH.h"


#include "../include/MCAL/RCC/RCC_Interface.h"
#include "../include/MCAL/RCC/RCC_Private.h"
#include "../include/MCAL/GPIO/GPIO_Interface.h"
#include "../include/MCAL/SYS_TICK/SYS_TICK_Interface.h"
#include "../include/MCAL/NVIC/NVIC_Interface.h"
#include "../include/MCAL/EXTI/EXTI_Interface.h"

#include "../include/HAL/SSD/SSD_Interface.h"

void app_init(void);

EXTI_t my_EXTI_11 = {.EXTI = 0,
				  .EXTI_MASK = Unmaskable,
				  .EXTI_SRC_Port = EXTI_SOURCE_GPIOA,
				  .Trigger = FALLING_EDGE
};

int main()
{
	app_init();

	GPIO_void_Set_Pin_Mode(GPIOA , PIN_0 , INPUT);
	GPIO_void_Set_Pin_Pull_State(GPIOA , PIN_0 ,PULL_UP);

	GPIO_void_Set_Pin_Mode(GPIOA , PIN_7 , OUTPUT);
	GPIO_void_Set_Pin_Type(GPIOA , PIN_7 , push_pull);
	GPIO_void_Set_Pin_Speed(GPIOA , PIN_7 , Medium_speed );
	//GPIO_void_Set_Pin_Value_Atomic(GPIOA , PIN_7 , SET);

	EXTI_void_EXTIx_enable(&my_EXTI_11);

  while (1)
    {

    }



  return 0;
}



void app_init(void)
{
	RCC_void_Init_Sys_Clk();

	RCC_void_Enable_Peripheral_Clk( AHB1,  RCC_AHB1ENR_GPIOAEN);

	SYS_TICK_void_Init();


	//SSD_void_Initialize();
	//NVIC_void_Enable_PerInt(6);

	EXTI_void_EXTI_init();
}

void EXTI0_IRQHandler()
{
	static u8 counter = 0;
	if((counter % 2) == 0)
	{
		GPIO_void_Set_Pin_Value_Atomic(GPIOA , PIN_7 , SET);
	}
	else
	{
		GPIO_void_Set_Pin_Value_Atomic(GPIOA , PIN_7 , RST);
	}
	counter++;
}
