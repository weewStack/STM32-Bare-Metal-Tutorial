#include "stm32f4xx.h"
#include "gpio.h"
#include "adc.h"


static char ADC1Set = 0;
static char ADC2Set = 0;
static char ADC3Set = 0;

static char ADC_IRQ = 0;

static unsigned short ADC_PIN_CH_MAP_cols = 3;
static unsigned short ADC_PIN_CH_MAP_rows = 48;
static unsigned char ADC_PIN_CH_MAP[48][3] = {
	//{PIN, ADCx, Channel}
		{PF3,adc3,9},
		{PF4,adc3,14},
		{PF5,adc3,15},
		{PF6,adc3,4},
		{PF7,adc3,5},
		{PF8,adc3,6},
		{PF9,adc3,7},
		{PF10,adc3,8},
		{PC0,adc1,10},
		{PC0,adc2,10},
		{PC0,adc3,10},
		{PC1,adc1,11},
		{PC1,adc2,11},
		{PC1,adc3,11},
		{PC2,adc1,12},
		{PC2,adc2,12},
		{PC2,adc3,12},
		{PC3,adc1,13},
		{PC3,adc2,13},
		{PC3,adc3,13},
		{PA0,adc1,0},
		{PA0,adc2,0},
		{PA0,adc3,0},
		{PA1,adc1,1},
		{PA1,adc2,1},
		{PA1,adc3,1},
		{PA2,adc1,2},
		{PA2,adc2,2},
		{PA2,adc3,2},
		{PA3,adc1,3},
		{PA3,adc2,3},
		{PA3,adc3,3},
		{PA4,adc1,4},
		{PA4,adc2,4},
		{PA5,adc1,5},
		{PA5,adc2,5},
		{PA6,adc1,6},
		{PA6,adc2,6},
		{PA7,adc1,7},
		{PA7,adc2,7},
		{PC4,adc1,14},
		{PC4,adc2,14},
		{PC5,adc1,15},
		{PC5,adc2,15},
		{PB0,adc1,8},
		{PB0,adc2,8},
		{PB1,adc1,9},
		{PB1,adc2,9},
};

void ADCRccInit(char adc){
	RCC->APB2ENR |= (1<<(8+adc));
}

ADC_TypeDef * get_ADC(char adc){

	ADC_TypeDef * ADCx;
	
	switch(adc)
	{
		case adc1 : ADCx = ADC1; break;
		#ifdef ADC2
		case adc2 : ADCx = ADC2; break;
		#endif
		#ifdef ADC3
		case adc3 : ADCx = ADC3; break;
		#endif
	}
	
	return ADCx;
}

ADC_TypeDef * AdcInit(char adc){
	ADC_TypeDef * ADCx;
	// ADCRccInit
	ADCRccInit(adc);
	// Identify the ADC
	ADCx = get_ADC(adc);
	// Reset CR2
	ADCx->CR2 =0;
	// Run CR2 (Wait a bit)
	ADCx->CR2 |= 1;
	while((ADCx->CR2 & 1) == 0){}
	
	return ADCx;
}

char AdcPinChannelMapper(char adc, int PortPin){
char channel = 0;
int i;
	for(i=0;i< ADC_PIN_CH_MAP_rows;i++)
	{
		if((PortPin == ADC_PIN_CH_MAP[i][0]) && (adc == ADC_PIN_CH_MAP[i][1]))
		{
			channel = ADC_PIN_CH_MAP[i][2];
			return channel;
		}
	
	}
	return channel;
}

// void PinAnalogSet
void PinAnalogSet(char adc, int PortPin){
	char channel;	
	ADC_TypeDef * ADCx;
	// Init the Pin  --> Clock / GPIO 
		PinOutputSet(PortPin); // GPIO has been activated
		PinModeADC(PortPin); // Pin is set to analog mode

	//------------------ Inside the ADC -----
	if(adc == adc1)
	{
		if(ADC1Set == 0)
		{
			//AdcInit
			ADCx = AdcInit(adc);
			ADC1Set = 1;
			
		}
	}
	else if(adc == adc2)
	{
		if(ADC2Set == 0)
		{
			//AdcInit
			ADCx = AdcInit(adc);
			ADC2Set = 2;
			
		}
	}
	else if(adc == adc3)
	{
		if(ADC3Set == 0)
		{
			//AdcInit
			ADCx = AdcInit(adc);
			ADC3Set = 2;
			
		}
	}
	
		
		// AdcPinChannelMapper
		channel = AdcPinChannelMapper(adc,PortPin);
		// Choose the channel 
		ADCx->SQR3 = channel; // Channel 1 is connected to PA1
		// Run CR2 (Wait a bit)
		ADCx->CR2 |= 1;
		// Reading the data --> Target register / Status register
}





void PinADCSet(int PortPin){PinAnalogSet(adc1,PortPin);}
void PinADC2Set(int PortPin){PinAnalogSet(adc2,PortPin);}
void PinADC3Set(int PortPin){PinAnalogSet(adc3,PortPin);}
//PinAnalogRead
int PinAnalogRead(char adc, int PortPin){
int ADC_Val = 0, EOC =0;
ADC_TypeDef * ADCx;
ADCx = get_ADC(adc);	
char channel = AdcPinChannelMapper(adc,PortPin);
	
if(channel != ADCx->SQR3)
{
	ADCx->SQR3 = channel;
	ADCx->CR2 |= (1<<30);
}
else{ADCx->CR2 |= (1<<30);}
	
// Reading operation
		ADCx->CR2 |= (1<<30);
		while(EOC==0){EOC = ADCx->SR & 2;}
	
		ADC_Val = ADC1->DR;
	
	return ADC_Val;
}

int PinADCRx(int PortPin){return PinAnalogRead(adc1, PortPin);}
int PinADC2Rx(int PortPin){return PinAnalogRead(adc2, PortPin);}
int PinADC3Rx(int PortPin){return PinAnalogRead(adc3, PortPin);}
void PinAnalogCycleSet(char adc, int PortPin, char cycles){
	char channel = AdcPinChannelMapper(adc,PortPin);
	ADC_TypeDef * ADCx = get_ADC(adc);
	
	ADCx->CR2 = 0;
	if(channel > 10)
	{
		ADCx->SMPR2 &= ~(0x7 << ((channel-10)*3));
		ADCx->SMPR2 |= (cycles << ((channel-10)*3));
	
	}
	else
	{
		ADCx->SMPR2 &= ~(0x7 << ((channel)*3));
		ADCx->SMPR2 |= (cycles << ((channel)*3));
	}
	ADCx->CR2 |= 1;
	while((ADCx->CR2 & 1) == 0){}
	ADCx->CR2 |= 1;
	
}

void PinADCycle(int PortPin, char cycles){PinAnalogCycleSet(adc1,PortPin,cycles);}
void PinAD2Cycle(int PortPin, char cycles){PinAnalogCycleSet(adc2,PortPin,cycles);}
void PinAD3Cycle(int PortPin, char cycles){PinAnalogCycleSet(adc3,PortPin,cycles);}

int PinAnalagRxDix(char adc, int PortPin,int div){
int ADC_val = PinAnalogRead(adc,PortPin);
//0 --> 4095
if(div == 0){div = 1;}
if(((ADC_val*div)/4095) > div) {return div;}

return ((ADC_val*div)/4095);
}

int PinADRXDiv(int PortPin,int div){return PinAnalagRxDix(adc1, PortPin,div);}
int PinAD2RXDiv(int PortPin,int div){return PinAnalagRxDix(adc2, PortPin,div);}
int PinAD3RXDiv(int PortPin,int div){return PinAnalagRxDix(adc3, PortPin,div);}

/********************IRQ Functions section******************************

ADC_IRQHandler()

************************************************************************/

// Initiate the ADC IRQ function ADC_IRQ_ON
void ADC_IRQ_ON(char adc){
	ADC_TypeDef * ADCx = get_ADC(adc);
	if(adc == adc1)
	{
		if(ADC1Set == 0)
		{
			//AdcInit
			ADCx = AdcInit(adc);
			ADC1Set = 1;
			
		}
	}
	else if(adc == adc2)
	{
		if(ADC2Set == 0)
		{
			//AdcInit
			ADCx = AdcInit(adc);
			ADC2Set = 2;
			
		}
	}
	else if(adc == adc3)
	{
		if(ADC3Set == 0)
		{
			//AdcInit
			ADCx = AdcInit(adc);
			ADC3Set = 2;
			
		}
	}
	
	ADCx->CR2 |= 2; // Continious conversion
	
	if(ADC_IRQ ==0)
	{
	__disable_irq();
	NVIC_EnableIRQ(ADC_IRQn);	
	__enable_irq();
	ADC_IRQ = 1;
	}


}

// Assign a Pin / Channel to the ADC and start
void ADC_Pin_Set(char adc,int PortPin){
	PinOutputSet(PortPin); // GPIO has been activated
	PinModeADC(PortPin); // Pin is set to analog mode
	ADC_TypeDef * ADCx = get_ADC(adc);
	char channel = AdcPinChannelMapper(adc,PortPin);
	
	ADCx->CR1 =0;
	if(channel != ADCx->SQR3)
	{
		ADCx->SQR3 = channel;
	}
	
	ADCx->CR2 |= (1<<10); // Enabling EOCs
	ADCx->CR1 |= (1<<5); // Enabling the Interrup
	ADCx->CR2 |= (1<<30); //Starting conversion
	
	
}
char ADC_IRQ_Check(char adc){
	ADC_TypeDef * ADCx = get_ADC(adc);
	if(ADCx->SR &= 0x2)
	{
		ADCx->SR = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}
// Read Data 
int ADC_Rx(char adc){
	ADC_TypeDef * ADCx = get_ADC(adc);
	int data = ADCx->DR;
	ADCx->CR2 |= (1<<30);
	return data;
}
void ADC_IRQ_OFF(char adc){
	ADC_TypeDef * ADCx = get_ADC(adc);
	ADCx->CR2 &= ~(1<<30);
	ADCx->CR2 &= ~(0x2);
	__disable_irq();
	NVIC_DisableIRQ(ADC_IRQn);	
	__enable_irq();
	ADC_IRQ = 0;
	
}

