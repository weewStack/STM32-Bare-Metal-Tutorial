#include "stm32f4xx.h"


#define PortA          0           
#define PortB          1           
#define PortC          2  
#define PortD          3 
#define PortE          4 
#define PortF          5 
#define PortG          6 
#define PortH          7 
#define PortI          8 
#define PortJ          9 
#define PortK          10 


#define  IN   0
#define  OUT  1
#define  AF   2
#define  AN	  3

#define HIGH       1
#define LOW        0

#define FALL 0
#define RISE 1

/*Defining Pin Speed*/

#define LS  0
#define MS  1
#define FS  2
#define HS 	3


#define NPP 0
#define PU  1
#define PD 	2
#define PP 	3

enum portA{PA0=0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15}; 
enum portB{PB0=16,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15}; 
enum portC{PC0=32,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15}; 
enum portD{PD0=48,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15}; 
enum portE{PE0=64,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15}; 
enum portF{PF0=80,PF1,PF2,PF3,PF4,PF5,PF6,PF7,PF8,PF9,PF10,PF11,PF12,PF13,PF14,PF15}; 
enum portG{PG0=96,PG1,PG2,PG3,PG4,PG5,PG6,PG7,PG8,PG9,PG10,PG11,PG12,PG13,PG14,PG15}; 
enum portH{PH0=112,PH1,PH2,PH3,PH4,PH5,PH6,PH7,PH8,PH9,PH10,PH11,PH12,PH13,PH14,PH15}; 
enum portI{PI0=128,PI1,PI2,PI3,PI4,PI5,PI6,PI7,PI8,PI9,PI10,PI11,PI12,PI13,PI14,PI15}; 
enum portJ{PJ0=144,PJ1,PJ2,PJ3,PJ4,PJ5,PJ6,PJ7,PJ8,PJ9,PJ10,PJ11,PJ12,PJ13,PJ14,PJ15}; 
 
enum AFunction {AF0,AF1,AF2,AF3,AF4,AF5,AF6,AF7,AF8,AF9,AF10,AF11,AF12,AF13,AF14,AF15};

typedef struct pinMaster{
	char port;
	char pin;
	//	GPIO_TypeDef * gpio;
	//void (*init)(char port, char pin);
} Pin ;

Pin initPin( char port, char pin);
Pin Pin_OutputSet(char port, char pin);
Pin Pin_IntputSet(char port, char pin);
Pin Pin_AFSet(char port, char pin);
void Timer_Pin_set(char port, char pin,char timer);
void Serial_Pin_set(char port, char pin,char uart);
void ADC_Pin_set(char port, char pin);
void Pin_W(Pin pin, char state);
char Pin_R(Pin pin);
void Pin_toggle(Pin pin);
/************************* 1-Elt Pin Control*************************

*********************************************************************/

Pin PinOutputSet(char PortPin);
Pin PinIntputSet(char PortPin);
Pin PinAFSet(char PortPin);
void PinW(char PortPin,char state);
char PinR(char PortPin);
void PinToggle(char PortPin);
void PinADCSet(char PortPin);
/**************************GPIO-IRQ*********************************



*********************************************************************/
void PinIRQFE(char PortPin);
void PinIRQRE(char PortPin);//
void PinIRQFRE(char PortPin);
void PinIrqStopFE(char PortPin);
void PinIrqStopRE(char PortPin);

/**************************GPIO-AF*********************************



*********************************************************************/
void ADCPinset(char PortPin);
void SPIPinset(char PortPin,char spi);
void I2CPinset(char PortPin,char AFunction);
void SDIOPinset(char PortPin);

/***********************Interrup*********************
void EXTI4_IRQHandler(void)
{
	if(EXTI->PR & (1<<4))
	{
		EXTI->PR |= (1<<4);
	}
	PinToggle(PC5);
	
}

*/




