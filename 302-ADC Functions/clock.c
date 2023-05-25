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

int AHBClokSpeed(void){
	int AHBClkSpeed = 0;
	int AHBPres = 0,i,cnt = 1;
	
	AHBPres = (RCC -> CFGR & (0xF << AHBPrescalerPos)) >> AHBPrescalerPos;
	if(AHBPres  > 7)
	{
		for(i=0;i < (AHBPres-7);i++)
		{
			cnt = cnt *2;
		}
		
	}
	AHBClkSpeed = ClockSysSpeed()/cnt;
	return AHBClkSpeed;
}
int APB1ClockSpeed(void){
	int APB1clkSpeed = 0;
	int APB1pres = 0,i,cnt = 1;
	
	APB1pres = (RCC -> CFGR & (0x7 << APB1PrescalerPos)) >> APB1PrescalerPos;
	if(APB1pres  > 3)
	{
		for(i=0;i < (APB1pres-3);i++)
		{
			cnt = cnt *2;
		}
		
	}
	APB1clkSpeed = ClockSysSpeed()/cnt;
	return APB1clkSpeed;
}
int APB2ClockSpeed(void){
	int APB2clkSpeed = 0;
	int APB2pres = 0,i,cnt = 1;
	
	APB2pres = (RCC -> CFGR & (0x7 << APB2PrescalerPos)) >> APB2PrescalerPos;
	if(APB2pres  > 3)
	{
		for(i=0;i < (APB2pres-3);i++)
		{
			cnt = cnt *2;
		}
		
	}
	APB2clkSpeed = ClockSysSpeed()/cnt;
	return APB2clkSpeed;
}

void ClockSpeedSetHSE(int M,int N, int P,  int Q, int AHBPrescaler, int APB1Prescaler, int APB2Prescaler){
	int N_Mask=0;
	int tot_div = 0;
	
	// Enbling HSE
	ClockHseOn();
	
	// POWER on for the clock
	RCC -> APB1ENR |= RCC_APB1ENR_PWREN;
	PWR ->CR |= PWR_CR_VOS;
	
	
	//Flash Prameter setup
	FLASH -> ACR |= FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_DCEN  |FLASH_ACR_LATENCY_3WS;
	
	
	// Configuration of the Buses after system clock 
	
	//***********************AHB1****************************
	if(AHBPrescaler>1){
		while((AHBPrescaler/2) != 1)
		{
			AHBPrescaler = AHBPrescaler /2;
			tot_div++;
		}
		tot_div += 7;
	}
	
	RCC -> CFGR &= ~(0xF << AHBPrescalerPos);
	RCC -> CFGR |= tot_div << AHBPrescalerPos;
	
	/***********************APB1****************************/
	tot_div = 0;
	if(APB1Prescaler>1){
	while((APB1Prescaler & 1)==0)
	{
		tot_div ++;
		APB1Prescaler = APB1Prescaler >> 1;
	}
	  tot_div += 3;
	}
	RCC -> CFGR &= ~(0x7 << APB1PrescalerPos);
	RCC -> CFGR |= tot_div << APB1PrescalerPos;
	
	/***********************APB2****************************/
	tot_div = 0;
	if(APB2Prescaler>1){
	while((APB2Prescaler & 1)==0)
	{
		tot_div ++;
		APB2Prescaler = APB2Prescaler >> 1;
	}
	  tot_div += 3;
	}
	RCC -> CFGR &= ~(0x7 << APB2PrescalerPos);
	RCC -> CFGR |= tot_div << APB2PrescalerPos;
	


// Configuration of the PLL Parameters 
	
	// Config the PLL Parameters
	for (int i = 6; i <= 14; i++) 
		{
			N_Mask |= (1 << i);
		}	
	
	RCC->PLLCFGR &= ~((0xF << PLL_Q_POS) | (0x3 << PLL_P_POS) | (N_Mask) | (0x3F << 0));
	RCC->PLLCFGR |= ((Q << PLL_Q_POS) | (((P/2)-1) << PLL_P_POS) | (N << PLL_N_POS) | (M << 0));
	//
	
	
	// Selecting HSE as PLL source 
	RCC -> PLLCFGR |= 1<<22; 
	
	// PLL is on 
	ClockPllOn();
	
	// Selecting the clock source 
	RCC -> CFGR |= RCC_CFGR_SW_PLL;
	while((RCC -> CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
	
}


/**************

STM32F407
HSE = 8 Mhz

****************/
void Clk_STM32F407_168Mhz(void){
	int M = 4;
	int N = 168;
	int P = 2;
	int Q = 4;
	int AHBPrescaler = 1;
	int APB1Prescaler = 4;
	int APB2Prescaler = 2;
ClockSpeedSetHSE(M,N, P, Q, AHBPrescaler, APB1Prescaler, APB2Prescaler);

}
/**************

STM32F411
HSE = 25 Mhz

****************/
void Clk_STM32F411_100Mhz(void){
	int M = 12;
	int N = 96;
	int P = 2;
	int Q = 4;
	int AHBPrescaler = 1;
	int APB1Prescaler = 2;
	int APB2Prescaler = 1;
ClockSpeedSetHSE(M,N, P, Q, AHBPrescaler, APB1Prescaler, APB2Prescaler);

}
