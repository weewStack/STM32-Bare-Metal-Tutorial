#include "clock.h"
#include "gpio.h"


short clock_speed = 16;
short APB1_clock_speed_div =1;

#if defined(stm32f411xe)
	
#endif


void Clock_MCO1(char clock, char div){
	
	// Define the Pin PA8 as AF 
	Pin_OutputSet(PortA,8);
	Pin PA8 =Pin_AFSet(PortA,8);
	
	// Set the Pre-scaler for MCO1
	char pres = div + 2;
	if(pres > 7){pres = 7;}
	RCC->CFGR |= (pres << 24);
	
	// Enabling the MCO1
	RCC->CFGR |= (clock<< 21);
}

void Clock_MCO2(char clock, char div){
	
	// Define the Pin PA8 as AF 
	Pin_OutputSet(PortC,9);
	Pin PC9 =Pin_AFSet(PortC,9);
	GPIOC->OTYPER &= ~(3<<9);
	GPIOC->OSPEEDR |= 3<< (9*2);

	
	// Set the Pre-scaler for MCO1
	char pres = div + 2;
	if(pres > 7){pres = 7;}
	RCC->CFGR |= (pres << 27);	
	
	// Enabling the MCO2
	RCC->CFGR |= (clock<< 30);
}

void Clock_F411_96MHZ(void){
		// Enbling HSE
	RCC->CR |= 1<<16;  
	while (!(RCC->CR & (1<<17)));
	
	
	
	// POWER on for the clock
	RCC -> APB1ENR |= RCC_APB1ENR_PWREN;
	PWR ->CR |= PWR_CR_VOS;
	
	// Flash Prameter setup
	FLASH -> ACR |= FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_DCEN  |FLASH_ACR_LATENCY_3WS;
	
	// Configuration after system clock 
	RCC -> CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC -> CFGR |= RCC_CFGR_PPRE1_DIV2;
	RCC -> CFGR |= RCC_CFGR_PPRE2_DIV1;
	
	// Config the PLL Parameters
	RCC->PLLCFGR |= (PLL_411_Q << 24) | (PLL_411_P << 16) | (PLL_411_N << 6) | (PLL_411_M << 0);
	RCC -> PLLCFGR |= 1<<22; // Selecting HSE as PLL source 
	
	
	
	// PLL is on 
	RCC->CR |= (1<<24);
	while (!(RCC->CR & (1<<25)));
	
	// Selecting the clock source 
	RCC -> CFGR |= RCC_CFGR_SW_PLL;
	while((RCC -> CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
	clock_speed =96;
}

void Clock_F407_168MHZ(void){
		// Enbling HSE
	RCC->CR |= 1<<16;  
	while (!(RCC->CR & (1<<17)));
	
	
	
	// POWER on for the clock
	RCC -> APB1ENR |= RCC_APB1ENR_PWREN;
	PWR ->CR |= PWR_CR_VOS;
	
	// Flash Prameter setup
	FLASH -> ACR |= FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_DCEN  |FLASH_ACR_LATENCY_3WS;
	
	// Configuration after system clock 
	// AHB PR
		RCC->CFGR &= ~(1<<4);
		
		// APB1 PR
		RCC->CFGR |= (5<<10);
			
		// APB2 PR
		RCC->CFGR |= (4<<13);
	
	// Config the PLL Parameters
	//RCC->PLLCFGR &= ~ (0xf<<24);
	//RCC->PLLCFGR |= (PLL_407_Q << 24);
	RCC->PLLCFGR &= ~(0x3<<16);
	RCC->PLLCFGR |= (PLL_407_P << 16);
	RCC->PLLCFGR &= ~ (0xff<<6);
	RCC->PLLCFGR &= ~ (0x1<<14);
	RCC->PLLCFGR |= (PLL_407_N << 7) ;
	RCC->PLLCFGR &= ~ (0x3f<<0);
	RCC->PLLCFGR |= (PLL_407_M << 0);
	
	
	
	RCC -> PLLCFGR |= 1<<22; // Selecting HSE as PLL source 
	
	
	
	// PLL is on 
	RCC->CR |= (1<<24);
	while (!(RCC->CR & (1<<25)));
	
	// Selecting the clock source 
	RCC -> CFGR |= RCC_CFGR_SW_PLL;
	while((RCC -> CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
	
	clock_speed =168;
	APB1_clock_speed_div =2;
}

