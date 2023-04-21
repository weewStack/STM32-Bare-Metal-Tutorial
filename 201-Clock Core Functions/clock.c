#include "stm32f4xx.h"
#include "gpio.h"
#include "clock.h"


void ClockHseOn(void){
	RCC->CR |= (1<<16);
	while(!(RCC->CR & (1<<17)));
}

void ClockHseOff(void){
	RCC->CR &= ~(1<<16);
}

void ClockPllOn(void){
	RCC->CR |= (1<<24);
	while(!(RCC->CR & (1<<25)));
}

void ClockPllOff(void){
	RCC->CR &= ~(1<<24);
}

void ClockMCO1(char clk, char div){
	// Activate MCO1
	PinOutputSet(PA8);
	PinModeAF(PA8);
	
	// Reading clk
	RCC->CFGR &= ~(0x3 << 21);
	RCC->CFGR |= (clk << 21);
	// Adding Divs
	RCC->CFGR &= ~(0x7 << 24);
	RCC->CFGR |= (div << 24);

}

void ClockMCO2(char clk, char div){
	// Activate MCO1
	PinOutputSet(PC9);
	PinModeAF(PC9);
	
	// Reading clk
	RCC->CFGR &= ~(0x3 << 30);
	RCC->CFGR |= (clk << 30);
	// Adding Divs
	RCC->CFGR &= ~(0x7 << 27);
	RCC->CFGR |= (div << 27);

}

// Getting the Pll Clock speed function
int ClockPll(void){
	int PllclkSpeed = 0;
	int PLL_SRC = 0,P,N,M, N_Mask;
	if(RCC->PLLCFGR & (1<<22))
	{
		PLL_SRC = HSEClkSpeed;
	}
	else
	{
		PLL_SRC = HSIClkSpeed;
	}
	
	//Getting P
	P = 2*((RCC->PLLCFGR & (0x3 << PLL_P_POS))+1);
	
	// Gettting the N
	for(int i = 6; i <= 14; i++){N_Mask |= (1<<i);}
	
	N = (RCC->PLLCFGR & N_Mask) >> PLL_N_POS;
	
	//Getting the M
	
	M = RCC->PLLCFGR & 0x3F;
	
	
	PllclkSpeed = (PLL_SRC * N) / (P*M);
	
	
	
	
	return PllclkSpeed;
}

// Getting System Clock Speed
int ClockSysSpeed(void){
	char SWS = (RCC->CFGR & 0xc) >> 2;
	int clkSpeed = 0;
	
	if(SWS ==  SWS_HSI)
	{
		clkSpeed = HSIClkSpeed;
	}
	else if(SWS ==  SWS_HSE)
	{
		clkSpeed = HSEClkSpeed;
	}
	else if(SWS ==  SWS_PLL)
	{
		clkSpeed = ClockPll();
	}
	
	return clkSpeed;
	
}

