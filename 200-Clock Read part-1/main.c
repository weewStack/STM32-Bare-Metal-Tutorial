#include "gpio.h"
#include "stm32f4xx.h"
#include "clock.h"




int M,N,P,APB1_Prescaler,APB2_Prescaler;
int clkspeed = 0, Sysclk = 0;


int main(void)
{
	//PLL on
	//RCC->CR |= (1<<24);
	//ClockPllOn();
	// HSE On
	//RCC->CR |= (1<<16);
	//Clk_STM32F407_168Mhz();
	Clk_STM32F411_100Mhz();
	ClockHseOn();
	
	//MCO1
	//PinOutputSet(PA8);
	//PinModeAF(PA8);
	//RCC->CFGR |= (2<< 21);
	//RCC->CFGR |= (6 << 24);
	
	Clock_MCO1(PLL, 0);
	
	//MCO2
	/*
	PinOutputSet(PC9);
	PinModeAF(PC9);
	RCC->CFGR |= (0x3<< 30);
	RCC->CFGR |= (4 << 27);
	*/
	//Clock_MCO2(SYSCLK,MCO_DIV_1);
	
	
	while(1)
	{
		clkspeed =  ClockPll();
		Sysclk = ClockSysSpeed();
	}
	
	
	
	
	
	
	

	
}

