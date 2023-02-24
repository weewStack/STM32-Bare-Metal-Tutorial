#include "stm32f4xx.h"


enum timers{
	T,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17
};

static unsigned short PIN_TIMER_MAP_rows = 3;
static unsigned short PIN_TIMER_MAP_cols = 62;
static unsigned char PIN_TIMER_MAP[4][62] =
{
	{4,4,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,1,1,4,4,4,1,1,7,7,7,7,7,3,3,3,3,2,2,2,2,2,2,2,2,0,0,0,0,8,0,1,1,1,1,1,1,1,1,1,8,8,8},//Port
	{5,6,6,7,8,9,0,1,1,2,2,2,3,3,3,6,7,7,0,1,11,13,14,10,11,6,9,10,11,12,12,13,14,15,6,7,8,9,6,7,8,9,8,9,10,11,2,15,3,4,5,6,7,8,8,9,9,5,6,7},// Pin
	{9,9,10,11,13,14,5,2,5,2,5,9,2,5,9,3,3,14,3,3,1,1,1,2,2,12,12,5,5,5,4,4,4,4,8,8,8,8,3,3,3,3,1,1,1,1,8,2,2,3,3,4,4,4,10,4,11,8,8,8}, // Timer 
	{1,2,1,1,1,1,1,2,1,3,3,1,4,4,2,1,2,1,3,4,2,3,4,3,4,1,2,1,2,3,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,4,1,2,1,2,1,2,3,1,4,1,1,2,3}// Channel
};	
/*********************************************************

                     Systick Functions

**********************************************************/
void systick_init(void);
void SysDelayMillis(void);
void SysDelayMs(unsigned long t);
void SysDelaymicro(void);
void SysDelayUs(unsigned long t);

/*
typedef struct Systick_Preiph{
	void (*init)(void);
	void (*delayMs)(unsigned long t);
	void (*delayUs)(unsigned long t);
} Systick_Timer;
Systick_Timer SysTimer = {systick_init,SysDelayMs,SysDelayUs};
*/
/*********************************************************

                     Timer Functions

**********************************************************/
void TimerStartUs(char timer);
int TimerGetTimeUs(char timer);
void TimerStartMs(char timer);
int TimerGetTimeMs(char timer);
void TDelayUs(char timer, int milliS);
void TDelayMs(char timer, int microS);
void DelayUs(int microS);
void DelayMs(int milliS);
/*********************************************************

                     IRQ functions

**********************************************************/

void TimerIRQMS(char timer, int millis);
void TimerAR_IRQUS(char timer, int micros);
void TimerAR_IRQMS(char timer, int millis);

/*********************************************************

                   Compare functions

**********************************************************/
void timer_compare_micro(char port, char pin, int arr, int compare);
void timer_compare_milli(char port, char pin, int arr, int compare);
void timer_compare_stop(char PortPin);
void TimerCompIRQ(char PortPin, int arr, int compare);
void timer_pwm_micro(char PortPin, int arr, int compare);
void timer_pwm_milli(char PortPin, int arr, int compare);
/*********************************************************

                   Motor Driver

**********************************************************/
void ESCDiv100(char PortPin,unsigned int speed);

