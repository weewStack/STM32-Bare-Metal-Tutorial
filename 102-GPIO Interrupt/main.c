#include "gpio.h"
#include "stm32f4xx.h"


/*




//5- NVIC Enable
// 6- Start the thread function
// 7- Example of Interrupt
*/


int main(void)
{
	//1- Enable IRQ clock 
	RCC->APB2ENR |= (1 <<14);
//2- Enable external interrupt configuration register
	// PD1 & PA8 as setup as interrupt
	PinInputSet(PA8);
	PinInputSet(PD1);
	
	SYSCFG->EXTICR[2] &= (0xFFF0);
	
	SYSCFG->EXTICR[0] &= (0xFF0F);
	SYSCFG->EXTICR[0] |= (0x0030);
	// 3 Enable the Interrupt Mask register
	EXTI->IMR |= 0x100;
	EXTI->IMR |= 0x2;
	//4- Select the Interrupt Trigger
	EXTI->RTSR |= 0x100; // PA8 as Rising trigger
	EXTI->FTSR |= 0x2; // PD1 as Falling trigger
	//5- NVIC Enable
	__disable_irq();
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	__enable_irq();
	
	PinOutputSet(PA0);
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
	// Do something
	EXTI->PR |= 0x100;
	PinToggle(PA4);

}