#include "gpio.h"
#include "time.h"

void ImportantSetupToMakePinReady(void);

/*
Code for STM32F407VEGT6
*/
int main(void)
{
	ImportantSetupToMakePinReady();
	
	PinToggle(PA0);
	while(1)
	{
		PinToggle(PA0);
		PinToggle(PA1);
		DelayMs(500);
		PinToggle(PA0);
		PinToggle(PA1);
		DelayMs(500);
	
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
	//
}
