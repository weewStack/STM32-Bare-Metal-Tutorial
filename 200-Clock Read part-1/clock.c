#include "stm32f4xx.h"
#include "gpio.h"
#include "clock.h"


void ClockPllOn(void){
	RCC->CR |= (1<<24);
	while (!(RCC->CR & (1<<25)));
}
void ClockPllOff(void){RCC->CR &= ~(1<<24);}
void ClockHseOn(void){
	RCC->CR |= (1<<16);
	while (!(RCC->CR & (1<<17)));
}
void ClockHseOff(void){RCC->CR &= ~(1<<16);}
void Clock_MCO1(char clock, char div){
	
	// Define the Pin PA8 as AF 
	PinOutputSet(PA8);
	PinModeAF(PA8);
	
	// Set the Pre-scaler for MCO1
	RCC->CFGR &= ~(7 << 24);
	RCC->CFGR |= (div << 24);
	
	// Enabling the MCO1
	RCC->CFGR |= (clock<< 21);
}

void Clock_MCO2(char clock, char div){
	
	// Define the Pin PC9 as AF 
	PinOutputSet(PC9);
	PinModeAF(PC9);
		
	// Set the Pre-scaler for MCO2
	RCC->CFGR &= ~(7 << 27);	
	RCC->CFGR |= (div << 27);	
	
	// Enabling the MCO2
	RCC->CFGR |= (clock<< 30);
}


int ClockPll(void){
	
	int PLL_SRC = 0,M,N,P,N_Mask=0;
	int PllclckSpeed = 0;
	
	if(RCC->PLLCFGR & (1<<22))
		{
		PLL_SRC = HSEClkSpeed;
		}
	else
		{
		PLL_SRC = HSIClkSpeed;
		}
		// Getting P
		P = 2*((RCC->PLLCFGR & (0x3 << PLL_P_POS)) + 1);
		
	
	// Getting N
		
		for (int i = 6; i <= 14; i++) 
		{
			N_Mask |= (1 << i);
		}		
		N = (RCC->PLLCFGR &  N_Mask) >> PLL_N_POS;
		
		
		// Getting M
		
		M = RCC->PLLCFGR & 0x3F;
		
		
		PllclckSpeed = (PLL_SRC * N) / (P*M);
		
		return PllclckSpeed;
}


int ClockSysSpeed(void){
	
	char SWS = (RCC->CFGR & 0xC) >> 2;
	int PLL_SRC = 0,M,N,P,N_Mask;
	int clckSpeed = 0;
			
	if(SWS == SWS_HSI)
	{
		return HSIClkSpeed ;
	}
	else if (SWS == SWS_HSE)
	{
		return HSEClkSpeed ;
	}else
	{
		return  ClockPll();
	}
	
	return clckSpeed;
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
HSE = 8

****************/
void Clk_STM32F407_168Mhz(void){ClockSpeedSetHSE(4,168, 2, 4, 1, 4, 2);}
/**************

STM32F411
HSE = 25

****************/
void Clk_STM32F411_100Mhz(void){ClockSpeedSetHSE(12,96, 2, 4, 1, 2, 2);}
