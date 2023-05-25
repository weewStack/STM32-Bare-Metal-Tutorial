
#include "adc.h"
#include "gpio.h"


int L_Potentiometer = 0,R_Potentiometer = 0;

int main(void)
{
	
	
	//PA1 --> Lineare Potentiometer
	//PinAnalogSet(adc1,PA1);
	PinADCSet(PA1);
	
	// PA4 --> Rotation Potentiometer
	//PinAnalogSet(adc1,PA4);
	PinADCSet(PA4);


	while(1){
		
		
		//L_Potentiometer = PinAnalogRead(adc1,PA1);
		L_Potentiometer = PinADCRx(PA1);
		
		//R_Potentiometer = PinAnalogRead(adc1,PA4);
		R_Potentiometer = PinADCRx(PA4);
		
	
	
	
	}
	
	
}

