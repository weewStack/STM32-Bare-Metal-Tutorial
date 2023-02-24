#include "gpio.h"
#include "time.h"

void ImportantSetupToMakePinReady(void);

int i,j;

int main(void)
{
	ImportantSetupToMakePinReady();
	
	
	
	// A Byte or 8 bits to control our 8 LEDs
	// Using a char for obscure reasons that
	// will be explained in few episodes
	unsigned char myByte = 0B11111111U;  
	
	
	
	
	// Equal operation = 
	GPIOA->ODR = myByte;
	
	myByte = 0B10101010U;
	GPIOA->ODR = myByte;
	
	myByte = 0B01010101U;
	GPIOA->ODR = myByte;
	
	myByte = 0B10000001U;
	GPIOA->ODR = myByte;
	
	/* Careful at the last one*/
	myByte = 0B00000000U;
	GPIOA->ODR = myByte;
	
	// OR Operation |
	//is like adding a bit without possibility 
	// of removing it
	
	myByte = 0B10000001U;
	GPIOA->ODR = GPIOA->ODR | myByte;
	GPIOA->ODR = GPIOA->ODR | myByte;
	
	myByte = 0B00000000U;
	GPIOA->ODR = GPIOA->ODR | myByte;
	
	myByte = 0B01000010U;
	GPIOA->ODR |= myByte;
	
	myByte = 0B00111100U;
	GPIOA->ODR |= myByte;
	
	// AND Operation &
	//is like Removing a bit without  
	// possibility of ADDING it again
	
	myByte = 0B01111110U;
	GPIOA->ODR = myByte & GPIOA->ODR;
	GPIOA->ODR = GPIOA->ODR & myByte;
	
	myByte = 0B00111100U;
	GPIOA->ODR &= myByte;
	
	myByte = 0B11000011U;
	GPIOA->ODR &= myByte;
	
	// Complement Operators ~

	GPIOA->ODR = ~ GPIOA->ODR;
	
	myByte = 0B11000011U;
	GPIOA->ODR &= myByte;
	
	GPIOA->ODR = ~ GPIOA->ODR;
	GPIOA->ODR = ~ GPIOA->ODR;
	
	// Bit-Shift
	// Moving Bits around
	
	myByte = 0B00000001U;
	GPIOA->ODR = myByte;
	
	// Left shift
	GPIOA->ODR = myByte << 1;
	GPIOA->ODR = myByte << 1;
	GPIOA->ODR = GPIOA->ODR << 1;
	GPIOA->ODR = GPIOA->ODR << 1;
	
	GPIOA->ODR = GPIOA->ODR >> 1;
	GPIOA->ODR = GPIOA->ODR >> 2;
	GPIOA->ODR = GPIOA->ODR >> 4;
	// Bit mask
	// Targetting a specific Bit
	
	unsigned char MySuperImportantPin = 5;
	// Don't forget that counting starts from 0
	
	// To Set the Pin HIGH or ON
	
	GPIOA->ODR |= (1<< MySuperImportantPin);
	
	// To Set the pin LOW of OFF
	
	//1 << 5 --> 0010000
	//1 << 5 --> 1101111
	
	GPIOA->ODR &= ~(1<< MySuperImportantPin);
	
	while(1)
	{
		
		
		for(i = 0; i < 8 ; i++)
		{
			if( i == 0)
			{ 
				myByte = 0 ;
				GPIOA->ODR = myByte;
				DelayMs(300);
			}
			
			
			for(j=0;j<(8-i);j++)
			{	
				DelayMs(300);
				GPIOA->ODR = myByte | (1 << (7 - j)) ;
			}
			myByte |= 1 << i;
			GPIOA->ODR = myByte;
			DelayMs(300);
			
			
		
		}
		GPIOA->ODR = 0b01010101 ;
		for(i=0;i<10;i++)
		{
			DelayMs(200);
			GPIOA->ODR = ~GPIOA->ODR;
		}
		
	}
	
	
}


void ImportantSetupToMakePinReady(void){
	PinOutputSet(PA0);
	PinOutputSet(PA1);
	PinOutputSet(PA2);
	PinOutputSet(PA3);
	PinOutputSet(PA4);
	PinOutputSet(PA5);
	PinOutputSet(PA6);
	PinOutputSet(PA7);
}
