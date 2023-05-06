
#include "clock.h"


int pll_value = 0, SysCLK = 0, AHB = 0, APB1 = 0, APB2 = 0;

int main(void){
	Clk_STM32F411_100Mhz();
	//Clk_STM32F407_168Mhz();
	ClockMCO1(PLL,MCO_DIV_1);
	
	//ClockMCO2(SYSCLK,MCO_DIV_1);
	
	while(1)
		
	{
		pll_value = ClockPll();
		SysCLK =  ClockSysSpeed();
		AHB = AHBClokSpeed();
		APB1 = APB1ClockSpeed();
		APB2 = APB2ClockSpeed();
	}

}