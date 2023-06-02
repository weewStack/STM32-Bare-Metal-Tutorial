#include "clock.h"
#include "adc.h"
#include "gpio.h"

int ADC_data1 = 0,ADC_data2 = 0;
char adc_check = 0;
int main(void){
	PinOutputSet(PA0);
	PinOutputSet(PA5);
	PinADCSet(PA1);
	ADC_IRQ_ON(adc2);
	ADC_Pin_Set(adc2,PA4);
	
	
	// Assign a Pin / Channel to the ADC and start
	
	// Turn off the IRQ
	
while(1){


// Read Data 
	PinW(PA5,ON);
	if(adc_check)
	{
		ADC_data1 = ADC_Rx(adc2);
		adc_check = 0;
	}
	PinW(PA5,OFF);
	PinW(PA0,ON);
	ADC_data2 = PinADCRx(PA1);
	PinW(PA0,OFF);
	
}
	
	return 1;
}

// USe the ADC IRQ handler 
void ADC_IRQHandler(){
	// Checking the signal
	if(ADC_IRQ_Check(adc2))
	{
		adc_check = 1;
	}
	if(ADC_IRQ_Check(adc1))
	{
		//adc_check = 1;
	}


}


