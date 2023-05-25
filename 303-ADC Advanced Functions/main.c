
#include "adc.h"
#include "gpio.h"
#include "clock.h"

int L_Potentiometer = 0,R_Potentiometer = 0, P1_V_mV, S_P1_mm, R_angle;

int main(void)
{
	Clk_STM32F407_168Mhz();
	
	PinOutputSet(PA0);
	PinOutputSet(PA5);
	//PA1 --> Lineare Potentiometer
	//PinAnalogSet(adc1,PA1);
	PinADCSet(PA1);
	PinADCycle(PA1,_480_CYCLES);
	
	// PA4 --> Rotation Potentiometer
	//PinAnalogSet(adc1,PA4);
	PinADCSet(PA4);
	//PinADCycle(PA4,_480_CYCLES);

	while(1){
		
		
		//L_Potentiometer = PinAnalogRead(adc1,PA1);
		PinW(PA0,ON);
		L_Potentiometer = PinADCRx(PA1);
		P1_V_mV = PinADRXDiv(PA1,3300);
		S_P1_mm = PinADRXDiv(PA1,30);
		PinW(PA0,OFF);
		//R_Potentiometer = PinAnalogRead(adc1,PA4);
		PinW(PA5,ON);
		R_Potentiometer = PinADCRx(PA4);
		R_angle = PinADRXDiv(PA4,360);
		PinW(PA5,OFF);
	
	
	
	}
	
	
}

