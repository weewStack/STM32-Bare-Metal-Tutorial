#include "gpio.h"
#include "time.h"
#include <stdio.h>

#define StartPIN 		PA0
#define CharPIN  		PA1
#define ShortPIN  	PA2
#define IntPin 			PA3
#define FloatPin		PA4
#define LongPin			PA5
#define LongLongPin PA6
#define DoublePin 	PA7


int i;


void ImportantSetupToMakePinReady(void);
char CharComputation(char number);


/*
Code for STM32F407VGT6
Used board STM32F4-Discovery 
*/

unsigned char MyCharVariable = 2;

unsigned short MyShortVariable = 2;

unsigned int MyIntVariable = 2;

float myFloatVariable = 2;

unsigned long myLongVariable  = 2;

unsigned long long MyLongLongVariable = 2;

double MyDoubleVariable = 2;

unsigned char VaribleByteSize = 0;

int main(void)
{
	ImportantSetupToMakePinReady();
	
	VaribleByteSize = sizeof(MyCharVariable)*8;
	PinW(CharPIN,LOW);
	VaribleByteSize = sizeof(MyShortVariable)*8;
	PinW(CharPIN,LOW);
	VaribleByteSize = sizeof(MyIntVariable)*8;
	PinW(CharPIN,LOW);
	VaribleByteSize= sizeof(myFloatVariable)*8;
	PinW(CharPIN,LOW);
	VaribleByteSize = sizeof(myLongVariable)*8;
	PinW(CharPIN,LOW);
	VaribleByteSize= sizeof(MyLongLongVariable)*8;
	PinW(CharPIN,LOW);
	VaribleByteSize= sizeof(MyDoubleVariable)*8;
	PinW(CharPIN,LOW);
	while(1)
	{
		PinW(StartPIN,HIGH);
	/*---
		
			PinW(CharPIN,HIGH);
			for(i=0;i<100;i++)
			{
				MyCharVariable = MyCharVariable * 100;
				MyCharVariable = MyCharVariable / 100;
			}
			PinW(CharPIN,LOW);
		
			PinW(ShortPIN,HIGH);
			for(i=0;i<100;i++)
			{
				MyShortVariable = MyShortVariable * 100;
				MyShortVariable =  MyShortVariable / 100;
			}
			PinW(ShortPIN,LOW);
			
			PinW(IntPin,HIGH);
			for(i=0;i<100;i++)
			{
				MyIntVariable = MyIntVariable * 100;
				MyIntVariable = MyIntVariable / 100;
				
			}
			PinW(IntPin,LOW);
			
			PinW(FloatPin,HIGH);
			for(i=0;i<100;i++)
			{
				myFloatVariable = myFloatVariable * 100;
				myFloatVariable = myFloatVariable / 100;
			}
			PinW(FloatPin,LOW);
			
			
			PinW(LongPin,HIGH);
			for(i=0;i<100;i++)
			{
				myLongVariable = myLongVariable * 100;
				myLongVariable = myLongVariable / 100;
			}
			PinW(LongPin,LOW);
			
			PinW(LongLongPin,HIGH);
			
			for(i=0;i<100;i++)
			{
				MyLongLongVariable = MyLongLongVariable * 100;
				MyLongLongVariable = MyLongLongVariable / 100;
			}
			PinW(LongLongPin,LOW);
			
			PinW(DoublePin,HIGH);
			for(i=0;i<100;i++)
			{
				MyDoubleVariable = MyDoubleVariable * 100;
				MyDoubleVariable = MyDoubleVariable / 100;
			}
			PinW(DoublePin,LOW);
	
			--------------------------------------------------------------------*/
			
			
		
		
			MyIntVariable = 1253;

			myFloatVariable = 1.253;
			
			PinW(IntPin,HIGH);
			for(i=0;i<1000;i++)
			{
				MyIntVariable = MyIntVariable * 1000;
				MyIntVariable = MyIntVariable / 1000;
				
			}
			PinW(IntPin,LOW);
			
			PinW(FloatPin,HIGH);
			for(i=0;i<1000;i++)
			{
				myFloatVariable = myFloatVariable * 1000;
				myFloatVariable = myFloatVariable / 1000;
			}
			PinW(FloatPin,LOW);
			
						/*-

			--------------------------------------------------------------------*/
			
		//DelayMs(10);	
		PinW(StartPIN,LOW);
		
		
		
	
	}
	

}


void ImportantSetupToMakePinReady(void){
	PinOutputSet(PA0);
	PinOutputSet(PA1);
	PinOutputSet(PA2);
	PinOutputSet(PA3);
	PinOutputSet(PA4);
	PinOutputSet(PA5);
	PinOutputSet(PA6);
	PinOutputSet(PA7);

}
