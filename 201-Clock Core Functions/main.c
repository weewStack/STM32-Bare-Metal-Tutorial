
#include "clock.h"


int pll_value = 0, SysCLK = 0, AHB = 0, APB1 = 0, APB2 = 0;

int main(void){

	ClockMCO1(PLL,MCO_DIV_1);
	
	//ClockMCO2(SYSCLK,MCO_DIV_1);
	
	while(1)
		
	{
		pll_value = ClockPll();
		SysCLK =  ClockSysSpeed();

	}

}