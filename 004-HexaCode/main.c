#include "gpio.h"
#include "time.h"

void ImportantSetupToMakePinReady(void);

int i,j, myRegisterValue;
unsigned char MySuperImportantBitPosition;
unsigned char MyDesiredBitConfig;



int main(void)
{
	ImportantSetupToMakePinReady();
	
	
	
	// A Byte or 8 bits to control our 8 LEDs
	// Using int for obscure reasons that
	// will be explained in few episodes
	
	unsigned int myByteInbits = 0B11111111111111111111111111111111U;  
	unsigned int myByteHex = 0xFFFFFFFF;  
	
	
	
	
	
	
	
	char myByte = 0xFF;
	GPIOA->ODR = myByte;
	
	
	
	//myByte = 0B10101010U;
	myByte = 0xAA;
	GPIOA->ODR = myByte;
		
	//myByte = 0B01000010U;
	myByte = 0x42;
	GPIOA->ODR = myByte;
	
	//myByte = 0B00111100U;
	myByte = 0x3C;
	GPIOA->ODR |= myByte;
	
	
	//myByte = 0B11000011U;
	myByte = 0xC3;
	GPIOA->ODR &= myByte;
	
	
	
	GPIOA->ODR = 0;
	// Bit-Shift
	// Moving Bits around
	
	//myByte = 0B00001100U;
	myByte = 0x0C;
	
	GPIOA->ODR = myByte;
	GPIOA->ODR = myByte << 1;
	GPIOA->ODR = myByte << 2;
	GPIOA->ODR = myByte << 3;
	GPIOA->ODR = myByte << 4;

	
	
	// Bit mask
	// Targetting a specific 4 bits
	myRegisterValue = 0B1011 1011 101101000111100111011001U;  
	MySuperImportantBitPosition = 24;
	MyDesiredBitConfig = 0b1100; // Or 0xC
	
	// The Wrong way
	// Set the new value
	myRegisterValue  |= (0xC << 24 );
	GPIOA->ODR = myRegisterValue;
	
	// The right way 
	// 1- Erase what ever the Value within the 4 bits position
	myRegisterValue = 0B10111011101101000111100111011001U;  
	myRegisterValue  &= ~ (0xf << 24 );
	
	// Set the new value
	myRegisterValue  |= (0xC << 24 );
	GPIOA->ODR = myRegisterValue;
	
	
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
