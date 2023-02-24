#include "stm32f4xx.h"


int main(void)
{
	
	RCC->AHB1ENR |= 0x7;/* Enabling GPIO port A & B & C */
	
	
	GPIOA->MODER &= ~(0b11); // Resetting the values
	GPIOA->MODER |= 0b01; // Setting up Pin 0 as output
	
	GPIOA->OTYPER &= ~0b1; // Set up the pin as pp
	
	GPIOA->ODR |= 1; // Should set PA0 to HIGH or on
	
	
	/************PB7 Enable******************/
	
	GPIOB->MODER &= ~(0x3<<(7*2)); // Resetting the values
	GPIOB->MODER |= (0x1<<14); // Setting up Pin 7 as output
	
	GPIOB->OTYPER &= ~(0b1<<7); // Set up the pin as pp
	
	GPIOB->ODR |= 1<<7; // Should set PB7 to HIGH or on
	
	/************PC13 Enable******************/
	
	
	GPIOC->MODER &= ~(0x3<<(13*2)); // Resetting the values
	GPIOC->MODER |= (0x1<<13*2); // Setting up Pin 13 as output
	
	GPIOC->OTYPER &= ~(0b1<<13); // Set up the pin as pp
	
	//GPIOC->ODR |= 1<<13; // Should set P13 to HIGH or on
	
	
}

