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

int myLEDList[] ={PA0,PC4,PD15,PC2,PF8,PA5, PE6,PG5,PB6,PF0};
int LedNumber=10;
/*

Input
1- PA4
2- PE2
3- PD1
4- PB10
5- PD0

*/

int MyPushButtonList[] = {PA4,PE2,PD1,PB10, PD0};

#define B_LED PA0
#define G_LED PC4

#define RedPushButton PinW(B_LED,PinR(PA4));
#define RedTiltPushButton PinW(G_LED,~PinR(PA4));
int i;
int main(void)
{
	PinInputSet(PA4);
	/*
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
	*/
	PinsOutputSet(myLEDList,LedNumber);
	PinsInputSet(MyPushButtonList,5);
	
	while(1)
	{
		/*
		PinW(PA0,~PinR(PA4));
		PinW(PA5,PinR(PE2));
		PinW(PC2,PinR(PD1));
		PinW(PD15,PinR(PB10));
		PinW(PE6,PinR(PD0));
		
		RedPushButton;
		RedTiltPushButton;
		*/
		
		for(i=0;i<LedNumber;i++)
		{
			PinW(myLEDList[i],PinR(MyPushButtonList[i/2]));
		}
	}
	

	


}
