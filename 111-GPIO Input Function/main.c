#include "stm32f4xx.h"
#include "gpio.h"


// STM32F446ZET
/*
Pin Map
Output:
1- PA0
2- PC4
3- PD15
4- PC2
5- PF8
6- PA5
7- PE6
8- PG5
9- PB6
10-PF0
*/


/*

Input
1- PA4
2- PE2
3- PD1
4- PB10
5- PD0

*/



//Step 1
// Setup the input Function

// Step 2
// Setup the Read Function

// Step 3
// Setup the toggle function


int main(void)
{
	PinOutputSet(PA0);
	PinOutputSet(PA5);
	PinOutputSet(PC2);
	PinOutputSet(PD15);
	PinOutputSet(PE6);
	
	PinInputSet(PA4);
	PinInputSet(PE2);
	PinInputSet(PD1);
	PinInputSet(PB10);
	PinInputSet(PD0);
	
	while(1)
	{
		PinW(PA0,~PinR(PA4));
		PinW(PA5,PinR(PE2));
		PinW(PC2,PinR(PD1));
		PinW(PD15,PinR(PB10));
		PinW(PE6,PinR(PD0));
	
	}
	

	


}
