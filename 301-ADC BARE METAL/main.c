#include "stm32f4xx.h"
#include "gpio.h"


int adcData, d_mm, V_mV;

int main(void)
{
	
// Init the ADC --> Clock 
RCC->APB2ENR |= (1<<8);
	
// Init the Pin PA1 --> Clock / GPIO 
PinOutputSet(PA1); // GPIOA has been activated
PinModeADC(PA1); // PA1 is set to analog mode
//------------------ Inside the ADC -----
	
// Reset CR2
ADC1->CR2 =0;
// Run CR2 (Wait a bit)
ADC1->CR2 |= 1;
while((ADC1->CR2 & 1) == 0){}
// Choose the channel 
ADC1->SQR3 = 1; // Channel 1 is connected to PA1
// Run CR2 (Wait a bit)
ADC1->CR2 |= 1;
// Reading the data --> Target register / Status register

	while(1){
	/// Reading operation
		ADC1->CR2 |= (1<<30);
		while((ADC1->SR & 2)==0){}
		adcData = ADC1->DR;
		V_mV = (3300*adcData)/4095;
		d_mm = (30*adcData)/4095;
	
	}
	
	
}

