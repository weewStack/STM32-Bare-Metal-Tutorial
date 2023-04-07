#include "gpio.h"
#include "stm32f4xx.h"
/*
Input Pins Connection: 


PD1 --> Red Push Button
PA8 --> Yellow Push Button 
PB5 --> Black Push Button
PB15 --> Orange Push Button


Output Pins connection:

PA0 -->LED1
PA1 -->LED2
PA2 -->LED3
PA3 -->LED4
PA4 -->LED5


*/

int main(void)
{
	
	PinIrqRE(PA8);
	PinIrqFE(PD1);
	
	PinIrqFE(PB5);
	PinIrqFE(PB15);
	
	PinOutputSet(PA0);
	PinOutputSet(PA1);
	PinOutputSet(PA2);
	PinOutputSet(PA4);
	
	
	while(1)
	{
	
		
	
	}
	

	


}

void EXTI1_IRQHandler()
{
	EXTI->PR |= 2;
	PinToggle(PA0);
}
void EXTI9_5_IRQHandler ()
{
	// handling PA8
	if(EXTI->PR & 0x100)
	{
		EXTI->PR |= 0x100;
		PinToggle(PA4);
	}
	// Handling PB5
	else if (EXTI->PR & 0x20)
	{
		EXTI->PR |= 0x20;
		PinToggle(PA2);
	}
}

void EXTI15_10_IRQHandler (){
	EXTI->PR |= 0x8000;
	PinToggle(PA1);

}