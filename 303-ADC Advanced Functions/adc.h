



enum ADCs {adc1=0,adc2,adc3};

#define _3_CYCLES 	0
#define _15_CYCLES 	1
#define _28_CYCLES 	2
#define _56_CYCLES 	3
#define _84_CYCLES 	4
#define _112_CYCLES 5
#define _144_CYCLES 6
#define _480_CYCLES 7

void PinAnalogSet(char adc, int PortPin);
int PinAnalogRead(char adc, int PortPin);

void PinADCSet(int PortPin);
void PinADC2Set(int PortPin);
void PinADC3Set(int PortPin);
int PinADCRx(int PortPin);
int PinADC2Rx(int PortPin);
int PinADC3Rx(int PortPin);
void PinADCycle(int PortPin, char cycles);
void PinAD2Cycle(int PortPin, char cycles);
void PinAD3Cycle(int PortPin, char cycles);
int PinADRXDiv(int PortPin,int div);
int PinAD2RXDiv(int PortPin,int div);
int PinAD3RXDiv(int PortPin,int div);



	


