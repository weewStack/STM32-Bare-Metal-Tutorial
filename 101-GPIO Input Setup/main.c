#include "stm32f4xx.h"


int main(void)
{
	
	RCC->AHB1ENR |= 0x1F;/* Enabling GPIO port A & B & C & D */
	
	
	GPIOA->MODER &= ~(0b11); // Resetting the values
	GPIOA->MODER |= 0b01; // Setting up Pin 0 as output
	
	GPIOA->OTYPER &= ~0b1; // Set up the pin as pp
	
	
	
	
	/************PB7 Enable******************/
	
	GPIOB->MODER &= ~(0x3<<(7*2)); // Resetting the values
	GPIOB->MODER |= (0x1<<14); // Setting up Pin 7 as output
	
	GPIOB->OTYPER &= ~(0b1<<7); // Set up the pin as pp
	
	
	
	/************PC13 Enable******************/
	
	
	GPIOC->MODER &= ~(0x3<<(13*2)); // Resetting the values
	GPIOC->MODER |= (0x1<<13*2); // Setting up Pin 13 as output
	
	GPIOC->OTYPER &= ~(0b1<<13); // Set up the pin as pp
	
	
	/************PA4 Input******************/
	
	GPIOA->MODER &= ~(0x3<<(4*2)); // Resetting the values
	GPIOA->MODER |= (0x00<<4*2); // Setting up Pin 4 as Input
	GPIOA->OTYPER &= ~(0b1<<4); // Set up the pin as pp
	
	GPIOA->PUPDR &= ~(0x3<<(4*2)); // Resetting the values
	GPIOA->PUPDR |= (0x2<<4*2); // Setting up Pin 4 as PD
	
	/************PD9 Input******************/
	
	GPIOD->MODER &= ~(0x3<<(9*2)); // Resetting the values
	GPIOD->MODER |= (0x00<<9*2); // Setting up Pin 9 as Input
	GPIOD->OTYPER &= ~(0b1<<9); // Set up the pin as pp
	
	GPIOD->PUPDR &= ~(0x3<<(9*2)); // Resetting the values
	GPIOD->PUPDR |= (0x2<<9*2); // Setting up Pin 9 as PD
	
	/************PE11 Input******************/
	
	GPIOE->MODER &= ~(0x3<<(11*2)); // Resetting the values
	GPIOE->MODER |= (0x00<<11*2); // Setting up Pin 11 as Input
	GPIOE->OTYPER &= ~(0b1<<11); // Set up the pin as pp
	
	GPIOE->PUPDR &= ~(0x3<<(11*2)); // Resetting the values
	GPIOE->PUPDR |= (0x2<<11*2); // Setting up Pin 11 as PD
	
	while(1)
	{
		if(GPIOA->IDR & 0x10)
		{
			GPIOA->ODR |= 1; // Should set PA0 to HIGH or on
		}
		else
		{
			GPIOA->ODR &= ~1; // Should set PA0 to LOW or LED off
		}
		
		if(GPIOD->IDR & 0x200)
		{
			GPIOB->ODR |= 1<<7; // Should set PB7 to HIGH or on
		}
		else
		{
			GPIOB->ODR &= ~(1<<7); // Should set PB7 to LOW or LED off
		}
		
		if(GPIOE->IDR & (1<<11))
		{
			GPIOC->ODR &= ~(1<<13); // Should set PB7 to HIGH or on
		}
		else
		{
			GPIOC->ODR |= 1<<13; // Should set P13 to HIGH or on
		}
	
	}
	
	
	
	
}
