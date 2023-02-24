#include "gpio.h"



Pin initPin( char port, char pin){
	Pin pin_set = {port,pin};
	return pin_set;
}

void PortInit(char GPIO_port){
	RCC->AHB1ENR |= (1<<GPIO_port);
}

GPIO_TypeDef *get_GPIO(char port){
	GPIO_TypeDef * target_port;
	switch(port)
	{
		case PortA : target_port = GPIOA;break;
		case PortB : target_port = GPIOB;break;
		case PortC : target_port = GPIOC;break;
		#ifdef GPIOD
		case PortD : target_port = GPIOD;break;
		#endif
		#ifdef GPIOE
		case PortE : target_port = GPIOE;break;
		#endif
		#ifdef GPIOF
		case PortF : target_port = GPIOF;break;
		#endif
		#ifdef GPIOG
		case PortG : target_port = GPIOG;break;
		#endif
		#ifdef GPIOH
		case PortH : target_port = GPIOH;break;
		#endif
		#ifdef GPIOI
		case PortI : target_port = GPIOI;break;
		#endif
		#ifdef GPIOJ
		case PortJ : target_port = GPIOJ;break;
		#endif
		#ifdef GPIOK
		case PortK : target_port = GPIOK;break;
		#endif
	}
	return target_port;
}



void PinModeSet(char pin,char mode,GPIO_TypeDef * Pinport){
	Pinport->MODER &= ~(3<<(pin*2));
	Pinport->MODER |= (mode<<(pin*2));
}


void Pin_ModeSet(Pin pin,char mode,GPIO_TypeDef * Pinport){
	Pinport->MODER &= ~(3<<(pin.pin*2));
	Pinport->MODER |= (mode<<(pin.pin*2));
}

Pin PinOutputSet(char PortPin){
	char port  = PortPin /16;
	char pin = PortPin%16;
	
	Pin pin_set = {port,pin};
	
	PortInit(port);
	GPIO_TypeDef * Pinport = get_GPIO(port);
	
	PinModeSet(pin,OUT,Pinport);
	Pinport ->OTYPER &= ~(1<<(pin));
	
	Pinport ->OSPEEDR &= ~(3<<(pin*2));
	Pinport ->OSPEEDR |= (HS<<(pin*2));
	
	Pinport->PUPDR &= ~(3<<(pin_set.pin*2));
	Pinport->PUPDR |= (PD<<(pin_set.pin*2));
	
	return pin_set;
}

Pin PinIntputSet(char PortPin){
	
	char port  = PortPin /16;
	char pin = PortPin%16;	

	Pin pin_set = {port,pin};
	
	PortInit(port);
	
	GPIO_TypeDef * Pinport = get_GPIO(port);
	
	Pin_ModeSet(pin_set,IN,Pinport);
	Pinport->OTYPER &= ~(1<<(pin_set.pin));
	Pinport->PUPDR &= ~(3<<(pin_set.pin*2));
	Pinport->PUPDR |= (PD<<(pin_set.pin*2));
	
	
	return pin_set;
}
void PinADCSet(char PortPin){
		char port  = PortPin /16;
		char pin = PortPin%16;
		Pin pin_set = {port,pin};
		PortInit(port);
		GPIO_TypeDef * Pinport = get_GPIO(port);
		Pin_ModeSet(pin_set,AN,Pinport);
		Pinport->OSPEEDR |= (3<<(pin*2));	
}

void PinIntSet(char PortPin,char edge){
	
	char port  = PortPin /16;
	
	char pin = PortPin%16;	
	char exti = pin /4, extiPin = pin % 4;
	//disable global interruipt
	__disable_irq();
	// Set The pin as Input 
	PinIntputSet(PortPin);
	// Enable clock access EXTI
	RCC->APB2ENR |= (1 << 14);
	
	// Select target PIN on the EXTI
	SYSCFG->EXTICR[exti] &= ~(0xf << extiPin*4);
	SYSCFG->EXTICR[exti] |= (port << extiPin*4);
	// Unmask the interrupt reg
	EXTI->IMR |= (1<<pin);
	// Select if rising or Falling edge trigger 
	if(edge)
	{
		EXTI->RTSR |= (1<<pin);
	}
	else
	{
		EXTI->FTSR |= (1<<pin);
	}
	// Enable exti line in NVIC
	if(pin==0)
	{
		NVIC_EnableIRQ(EXTI0_IRQn);
	}
	else if(pin==1)
	{
		NVIC_EnableIRQ(EXTI1_IRQn);
	}
	else if(pin==2)
	{
		NVIC_EnableIRQ(EXTI2_IRQn);
	}
	else if(pin==3)
	{
		NVIC_EnableIRQ(EXTI3_IRQn);
	}
	else if(pin==4)
	{
		NVIC_EnableIRQ(EXTI4_IRQn);
	}
	else if(pin<10)
	{
		NVIC_EnableIRQ(EXTI9_5_IRQn);
	}
	else
	{
		NVIC_EnableIRQ(EXTI15_10_IRQn);
	}
	
	// Enable the global interrupt
	__enable_irq();
}


void PinIntStop(char PortPin,char edge){
	
	//char port  = PortPin /16;
	
	char pin = PortPin%16;	

	if(edge)
	{
		EXTI->RTSR &= ~(1<<pin);
	}
	else
	{
		EXTI->FTSR &= ~(1<<pin);
	}
	
}


void PinIRQFE(char PortPin){
	PinIntSet(PortPin,FALL);
}

void PinIRQRE(char PortPin){
	PinIntSet(PortPin,RISE);
}

void PinIRQFRE(char PortPin){
	PinIRQRE(PortPin);
	PinIRQFE(PortPin);
}

void PinIrqStopFE(char PortPin){
	PinIntStop(PortPin,FALL);
}
void PinIrqStopRE(char PortPin){
	PinIntStop(PortPin,RISE);
}


Pin PinAFSet(char PortPin){
	
	char port  = PortPin /16;
	char pin = PortPin%16;
	Pin pin_set = {port,pin};
	
	PortInit(port);
	
	GPIO_TypeDef * Pinport = get_GPIO(port);
	
	Pin_ModeSet(pin_set,AF,Pinport);

	
	
	return pin_set;
}

void PinW(char PortPin,char state){
	char port  = PortPin /16;
	char pin = PortPin%16;
	
	GPIO_TypeDef * Pinport = get_GPIO(port);
	if(state){
		Pinport->ODR |= (1<<pin);
	}
	else 
	{
		Pinport->ODR &= ~(1<<pin);
	}
}
char PinR(char PortPin){
	char port  = PortPin /16;
	char pin = PortPin%16;
	
	GPIO_TypeDef * Pinport = get_GPIO(port);
	if(Pinport->IDR & (1<<(pin)) )
	{
		return 0xFF;
	}
	else
	{
		return 0;
	}

}

void PinToggle(char PortPin){
	char port  = PortPin /16;
	char pin = PortPin%16;
	GPIO_TypeDef * Pinport = get_GPIO(port);
	PinR(PortPin) ? (Pinport ->ODR &= ~(1<<pin)  ) : (Pinport ->ODR |= (1<<pin));
}


Pin Pin_OutputSet(char port, char pin){
	
	
	Pin pin_set = {port,pin};
	
	PortInit(port);
	GPIO_TypeDef * Pinport = get_GPIO(port);
	
	Pin_ModeSet(pin_set,OUT,Pinport);
	Pinport ->OTYPER &= ~(1<<(pin_set.pin));
	
	Pinport ->OSPEEDR &= (3<<(pin_set.pin*2));
	Pinport ->OSPEEDR |= (HS<<(pin_set.pin*2));
	
	return pin_set;
}




Pin Pin_IntputSet(char port, char pin){
	
	Pin pin_set = {port,pin};
	
	PortInit(port);
	
	GPIO_TypeDef * Pinport = get_GPIO(port);
	
	Pin_ModeSet(pin_set,IN,Pinport);
	Pinport->OTYPER &= ~(1<<(pin_set.pin));
	Pinport->PUPDR &= ~(3<<(pin_set.pin*2));
	Pinport->PUPDR |= (PU<<(pin_set.pin*2));
	
	
	return pin_set;
}



Pin Pin_AFSet(char port, char pin){
	
	Pin pin_set = {port,pin};
	
	PortInit(port);
	
	GPIO_TypeDef * Pinport = get_GPIO(port);
	
	Pin_ModeSet(pin_set,AF,Pinport);

	
	
	return pin_set;
}




void Pin_W(Pin pin, char state){
	GPIO_TypeDef * Pinport = get_GPIO(pin.port);
	if(state){
		Pinport->ODR |= (1<<pin.pin);
	}
	else 
	{
		Pinport->ODR &= ~(1<<pin.pin);
	}
}

char Pin_R(Pin pin){
	GPIO_TypeDef * Pinport = get_GPIO(pin.port);
	if(Pinport->IDR & (1<<(pin.pin)) )
	{
		return 0xFF;
	}
	else
	{
		return 0;
	}

}

void Pin_toggle(Pin pin){
	GPIO_TypeDef * Pinport = get_GPIO(pin.port);
	Pin_R(pin) ? (Pinport ->ODR &= ~(1<<pin.pin)  ) : (Pinport ->ODR |= (1<<pin.pin));
}

void Timer_Pin_set(char port, char pin,char timer){
		Pin Timer_pin = Pin_AFSet(port,pin);
		GPIO_TypeDef * Pinport = get_GPIO(port);
		char AF_Selector, AF_Timer_val;
		if (pin < 8){ AF_Selector = 0; }
		else { AF_Selector = 1; pin = pin -8 ;}
		
		if( timer < 3 ){AF_Timer_val=1;}
		else if( timer < 6 ){AF_Timer_val=2;}
		else if( timer < 11 ){AF_Timer_val=3;}
		else {AF_Timer_val=9;}

		Pinport->OSPEEDR |= (3<<(pin*2));
		Pinport->AFR[AF_Selector] &= ~(0xf<< pin*4);
		Pinport->AFR[AF_Selector] |= (AF_Timer_val<< pin*4);
		
}
void Serial_Pin_set(char port, char pin,char uart){
		Pin Timer_pin = Pin_AFSet(port,pin);
		GPIO_TypeDef * Pinport = get_GPIO(port);
		char AF_Selector, AF_uart_val;
		if (pin < 8){ AF_Selector = 0; }
		else { AF_Selector = 1; pin = pin -8 ;}
		
		if( uart < 4 ){AF_uart_val=7;}
		else {AF_uart_val=8;}
		

		Pinport->OSPEEDR |= (3<<(pin*2));
		Pinport->AFR[AF_Selector] &= ~(0xf<< pin*4);
		Pinport->AFR[AF_Selector] |= (AF_uart_val<< pin*4);
		
}

void ADC_Pin_set(char port, char pin){
		
		Pin pin_set = {port,pin};
		PortInit(port);
		GPIO_TypeDef * Pinport = get_GPIO(port);
		Pin_ModeSet(pin_set,AN,Pinport);
		Pinport->OSPEEDR |= (3<<(pin*2));		
}
void ADCPinset(char PortPin){
		char port  = PortPin /16;
		char pin = PortPin%16;
		Pin pin_set = {port,pin};
		PortInit(port);
		GPIO_TypeDef * Pinport = get_GPIO(port);
		Pin_ModeSet(pin_set,AN,Pinport);
		Pinport->OSPEEDR |= (3<<(pin*2));		
}
void SPIPinset(char PortPin,char spi){
		char port  = PortPin /16;
		char pin = PortPin%16;
		char AF_Selector, AF_spi_val;
		PortInit(port);
	
		GPIO_TypeDef * Pinport = get_GPIO(port);
		PinAFSet(PortPin);
		Pinport->OTYPER &= ~(1<<(pin));
		/*Pinport->PUPDR &= ~(3<<(pin*2));
		Pinport->PUPDR |= (PU<<(pin*2));*/
		
		Pinport->OSPEEDR |= (3<<(pin*2));		
		
		if (pin < 8){ AF_Selector = 0; }
		else { AF_Selector = 1; pin = pin -8 ;}
		
		if( spi < 2 ){AF_spi_val=5;}
		else {AF_spi_val=6;}
		Pinport->AFR[AF_Selector] &= ~(0xf<< pin*4);
		Pinport->AFR[AF_Selector] |= (AF_spi_val<< pin*4);		
}

void I2CPinset(char PortPin,char AFunction){
		char port  = PortPin /16;
		char pin = PortPin%16;
		char AF_Selector;
		PortInit(port);
	
		GPIO_TypeDef * Pinport = get_GPIO(port);
		PinAFSet(PortPin);
	// St the Pin as Open Drain
		Pinport->OTYPER |= (1<<(pin));
	// Set The Pin as Pull up
	Pinport->PUPDR &= ~(3<<(pin*2));
	Pinport->PUPDR |= (PU<<(pin*2));
		
		Pinport->OSPEEDR |= (3<<(pin*2));		
		
		if (pin < 8){ AF_Selector = 0; }
		else { AF_Selector = 1; pin = pin -8 ;}
		
		Pinport->AFR[AF_Selector] &= ~(0xf<< pin*4);
		Pinport->AFR[AF_Selector] |= (AFunction<< pin*4);		
}
void SDIOPinset(char PortPin){
		char port  = PortPin /16;
		char pin = PortPin%16;
		char AF_Selector;
		PortInit(port);
	
		char AFunction = 12;
	
		GPIO_TypeDef * Pinport = get_GPIO(port);
		PinAFSet(PortPin);
	// St the Pin as Open Drain
		//Pinport->OTYPER &= ~(1<<(pin));
	// Set The Pin as Pull up
	
		
		Pinport->OSPEEDR |= (3<<(pin*2));		
		
		if (pin < 8){ AF_Selector = 0; }
		else { AF_Selector = 1; pin = pin -8 ;}
		
		Pinport->AFR[AF_Selector] &= ~(0xf<< pin*4);
		Pinport->AFR[AF_Selector] |= (AFunction<< pin*4);		
}
