#include "gpio.h"
#include "time.h"

extern short clock_speed;
extern short APB1_clock_speed_div;

char APB1_timers[7] = {T2,T3,T4,T5,T12,T13,T14};

typedef struct timer_struct
{
	char timer_num;
	char channel;
	TIM_TypeDef * timer;
} Timer;

/*********************************************************

                     Systick Functions

**********************************************************/
void systick_init(void){
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
}




void SysDelaymicro(void){
	SysTick->LOAD = clock_speed-1;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
}

void SysDelayUs(unsigned long t){
	if((SysTick->CTRL & 5) == 0)
	{systick_init();}
	
	for(;t>0;t--)
		{
			SysDelaymicro();
		}
}


void SysDelayMillis(void){
	SysTick->LOAD = (clock_speed*1000-1);
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
}



void SysDelayMs(unsigned long t){
	if((SysTick->CTRL & 5) == 0)
	{systick_init();}
	
	for(;t>0;t--)
		{
			SysDelayMillis();
		}
}
void systicc_IRQ(void){
__disable_irq();
	SysTick->CTRL = 0;
	SysTick->LOAD = (clock_speed*1000-1); /// Set the relad value (Or having 0.1 sec delay as Clock is 72Mhz)
	SysTick->VAL = 0; // Initialize value
	SysTick->CTRL = 7; // Enabling the Systick timer and also the interrupt
	__enable_irq();
	
	//Interrupt handler 
	/*
	void SysTick_Handler(void)
		{
			
		}
	
	*/
	
}

/*********************************************************

                     Timer Functions

**********************************************************/
char timer_clock_div(char timer){
	int i;
	if(APB1_clock_speed_div == 1)
		{return 1;}
	else{
		for(i=0;i<7;i++)
		{
			if(timer == APB1_timers[i])
			{
				return 2;
			}
		}
	}
	
	return 1;
		
}
TIM_TypeDef * get_timer(char timer){
	TIM_TypeDef * tim;
	switch(timer)
	{
		case T1 : tim = TIM1;break;
		case T2 : tim = TIM2;break;
		case T3 : tim = TIM3;break;
		case T4 : tim = TIM4;break;
		#ifdef TIM5
		case T5 : tim = TIM5;break;
		#endif
		#ifdef TIM6
		case T6 : tim = TIM6;break;
		#endif
		#ifdef TIM7
		case T7 : tim = TIM7;break;
		#endif
		#ifdef TIM8
		case T8 : tim = TIM8;break;
		#endif
		#ifdef TIM9
		case T9 : tim = TIM9;break;
		#endif
		#ifdef TIM10
		case T10 : tim = TIM10;break;
		#endif
		#ifdef TIM11
		case T11 : tim = TIM11;break;
		#endif
		#ifdef TIM12
		case T12 : tim = TIM12;break;
		#endif
		#ifdef TIM13
		case T13 : tim = TIM13;break;
		#endif
		#ifdef TIM14
		case T14 : tim = TIM14;break;
		#endif
		#ifdef TIM15
		case T15 : tim = TIM15;break;
		#endif
		#ifdef TIM16
		case T16 : tim = TIM16;break;
		#endif
		#ifdef TIM17
		case T17 : tim = TIM17;break;
		#endif
	}
	return tim;
}

void timer_startRCC(char timer){
	if(timer==1)
		{
			//Setup the Counter at the bus level
			RCC->APB2ENR |= 1;
		}
		else if(timer == 8)
		{
			RCC->APB2ENR |= 2;
		}
		else if ((timer >1) && (timer <8))
		{
			RCC->APB1ENR |= 1 <<(timer-2);
		}
		 else if (timer >11 && timer <15)
		{
			RCC->APB1ENR |= 1 <<(timer-6);
		}
		else if (timer >8 && timer <12)
		{
			RCC->APB1ENR |= 1 <<(16 + timer-9);
		}
}

TIM_TypeDef * timer_start_micros(char timer, int microS){
	int prescaler = (clock_speed/timer_clock_div(timer))-1;
	TIM_TypeDef * tim;

	timer_startRCC(timer);
		
	tim = get_timer(timer);
	
		// Setup the counter to 0
	tim->CNT = 0;
	
	// Setup the prescaler to 72 -> 1 div equal to 1 Micro Sec
	tim->PSC = prescaler;	
	
	// initialize the Auto reload register value
	tim->ARR = (microS-1);	
	
	//Enable the counter
	tim->CR1 |= 0x1;
	
	return tim ;
}

TIM_TypeDef * timer_start_millis(char timer, int microS){
	int prescaler = (clock_speed/timer_clock_div(timer));
	TIM_TypeDef * tim;

	timer_startRCC(timer);
		
	tim = get_timer(timer);
	
		// Setup the counter to 0
	tim->CNT = 0;
	
	// Setup the prescaler to 72 -> 1 div equal to 1 Micro Sec
	//tim->PSC = (prescaler*250)-1;	
	tim->PSC = ((clock_speed*250)/timer_clock_div(timer))-1;	
	
	// initialize the Auto reload register value
	tim->ARR = (microS*4-1);	
	
	//Enable the counter
	tim->CR1 |= 0x1;
	
	return tim ;
}

void TimerStartUs(char timer){
		TIM_TypeDef * tim = timer_start_micros(timer, 0xffff);
		//Enable the counter
		tim->CR1 |= 0x9;
}
void TimerStartMs(char timer){
		TIM_TypeDef * tim = timer_start_millis(timer, 0xffff);
		//Enable the counter
		tim->CR1 |= 0x9;
}


int TimerGetTimeUs(char timer){
	TIM_TypeDef *tim = get_timer(timer);
	int my_time = tim->CNT;
	return my_time;
}
int TimerGetTimeMs(char timer){
	TIM_TypeDef *tim = get_timer(timer);
	int my_time = tim->CNT;
	return (my_time/4);
}

void TDelayUs(char timer, int microS){
	
	TIM_TypeDef * tim = timer_start_micros(timer, microS);

	//Enable the counter
	tim->CR1 |= 0x9;
	tim->CNT =0;
	while(tim->CR1 & 1)
	{}
	
}

void TDelayMs(char timer, int milliS){
	int i = 0;
	for(i=0;i<milliS;i++)
	{
		TDelayUs(timer,1000);
	}
}

void DelayUs(int microS){
	TDelayUs(T4, microS);
}

void DelayMs(int milliS){
	TDelayMs(T4, milliS);
}

/*********************************************************

                     IRQ functions

**********************************************************/


void TimerEnIRQ(char timer){
	__disable_irq();
	switch(timer)
	{
		case 1 : NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);break;
		case 2 : NVIC_EnableIRQ(TIM2_IRQn);break;
		case 3 : NVIC_EnableIRQ(TIM3_IRQn);break;
		case 4 : NVIC_EnableIRQ(TIM4_IRQn);break;
		
	}
	__enable_irq();
}



void TimerIRQMS(char timer, int millis){
	TIM_TypeDef * tim = timer_start_millis(timer, millis);
	tim->DIER |=1 ;
	tim->CR1 |= 0x9;
	TimerEnIRQ(timer);
}
void TimerAR_IRQUS(char timer, int micros){
	TIM_TypeDef * tim = timer_start_micros(timer, micros);
	tim->DIER |=1 ;
	tim->CR1 &= ~(1<<3);
	tim->CR1 |= 0x1;
	__disable_irq();
	switch(timer)
	{
		case 1 : NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);break;
		case 2 : NVIC_EnableIRQ(TIM2_IRQn);break;
		case 3 : NVIC_EnableIRQ(TIM3_IRQn);break;
		case 4 : NVIC_EnableIRQ(TIM4_IRQn);break;
		#ifdef TIM5
		case 5 : NVIC_EnableIRQ(TIM5_IRQn);break;
		#endif
		#ifdef TIM6
		case 6 : NVIC_EnableIRQ(TIM6_DAC_IRQn);break;
		#endif
		#ifdef TIM7
		case 7 : NVIC_EnableIRQ(TIM7_IRQn);break;
		#endif
		#ifdef TIM8
		case 8 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
		#ifdef TIM8_UP_TIM13_IRQn
		case 9 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
		#ifdef TIM8_UP_TIM13_IRQn
		case 10 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
		#ifdef TIM8_UP_TIM13_IRQn
		case 11 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
		#ifdef TIM12
		case 12 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
		#ifdef TIM13
		case 13 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
	}
	__enable_irq();
}


void TimerAR_IRQMS(char timer, int millis){
	TIM_TypeDef * tim = timer_start_millis(timer, millis);
	tim->DIER |=1 ;
	tim->CR1 &= ~(1<<3);
	tim->CR1 |= 0x1;
	__disable_irq();
	switch(timer)
	{
		case 1 : NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);break;
		case 2 : NVIC_EnableIRQ(TIM2_IRQn);break;
		case 3 : NVIC_EnableIRQ(TIM3_IRQn);break;
		case 4 : NVIC_EnableIRQ(TIM4_IRQn);break;
		#ifdef TIM5
		case 5 : NVIC_EnableIRQ(TIM5_IRQn);break;
		#endif
		#ifdef TIM6
		case 6 : NVIC_EnableIRQ(TIM6_DAC_IRQn);break;
		#endif
		#ifdef TIM7
		case 7 : NVIC_EnableIRQ(TIM7_IRQn);break;
		#endif
		#ifdef TIM8
		case 8 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
		#ifdef TIM8_UP_TIM13_IRQn
		case 9 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
		#ifdef TIM8_UP_TIM13_IRQn
		case 10 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
		#ifdef TIM8_UP_TIM13_IRQn
		case 11 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
		#ifdef TIM12
		case 12 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
		#ifdef TIM13
		case 13 : NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);break;
		#endif
	}
	__enable_irq();
}





/*********************************************************

                   Compare functions

**********************************************************/

Timer PIN_TIMER_MAP_FUNC(char port, char pin){
	int i =0;
	Timer tim ={0,0};
	for (i=0;i<PIN_TIMER_MAP_cols;i++)
	{
		if((port == PIN_TIMER_MAP[0][i]) && (pin == PIN_TIMER_MAP[1][i]))
		{
			tim.timer_num = PIN_TIMER_MAP[2][i];
			tim.channel = PIN_TIMER_MAP[3][i];
			tim.timer = get_timer(PIN_TIMER_MAP[2][i]);
			return tim;
		}
	}
	return tim;
}



void timer_compare_micro(char port, char pin, int arr, int compare){
	Timer target_tim = PIN_TIMER_MAP_FUNC(port,pin);
	TIM_TypeDef * tim = target_tim.timer;
	char timer = target_tim.timer_num;
	char channel = target_tim.channel;
	short new_clock_speed = (clock_speed/timer_clock_div(timer));
	if ((tim->CCER & (1 << ((channel-1)*4)) ) == 0)
	{
		timer_startRCC(timer);
		//init_GP(port,pin,OUT50,O_AF_PP);
		
		Timer_Pin_set(port,pin, timer);
		
		
		tim->PSC = (new_clock_speed-1);

		switch(channel)
		{
			case 1: tim->CCMR1 |= 0x30;break;
			case 2: tim->CCMR1 |= 0x3000;break;
			case 3: tim->CCMR2 |= 0x30;break;
			case 4: tim->CCMR2 |= 0x3000;break;
		}
		tim->CCER |= (1 << ((channel-1)*4));
		tim->BDTR |= 0x8000;
		
		tim->CR1 |=1;
	}
	tim->CNT =0 ;
	tim->ARR = (arr-1);
	switch(channel)
	{
		case 1: tim->CCR1 = compare; break;
		case 2: tim->CCR2 = compare; break;
		case 3: tim->CCR3 = compare; break;
		case 4: tim->CCR4 = compare; break;
	}
	
}


void timer_compare_milli(char port, char pin, int arr, int compare){
	Timer target_tim = PIN_TIMER_MAP_FUNC(port,pin);
	TIM_TypeDef * tim = target_tim.timer;
	char timer = target_tim.timer_num;
	char channel = target_tim.channel;
	short new_clock_speed = (clock_speed/timer_clock_div(timer));
	
	if ((tim->CCER & (1 << ((channel-1)*4)) ) == 0)
	{
		timer_startRCC(timer);
		//init_GP(port,pin,OUT50,O_AF_PP);
		
		Timer_Pin_set(port,pin, timer);
		
		
		tim->PSC = (new_clock_speed*250-1);
		
		
		switch(channel)
		{
			case 1: tim->CCMR1 |= 0x30;break;
			case 2: tim->CCMR1 |= 0x3000;break;
			case 3: tim->CCMR2 |= 0x30;break;
			case 4: tim->CCMR2 |= 0x3000;break;
		}
		tim->CCER |= (1 << ((channel-1)*4));
		tim->BDTR |= 0x8000;
		tim->CR1 |=1;
	}
	tim->ARR = (arr*4-1);
	
	compare *= 4;
	
	switch(channel)
	{
		case 1: tim->CCR1 = compare; break;
		case 2: tim->CCR2 = compare; break;
		case 3: tim->CCR3 = compare; break;
		case 4: tim->CCR4 = compare; break;
	}
}
void timer_compare_stop(char PortPin){
	char port  = PortPin /16;
	char pin = PortPin%16;
	Timer target_tim = PIN_TIMER_MAP_FUNC(port,pin);
	TIM_TypeDef * tim = target_tim.timer;
	char channel = target_tim.channel;
	
	tim->CCER &= ~(1 << ((channel-1)*4));
	tim->CR1=0;
}



void timerCompIrQEn(char PortPin){
	char port  = PortPin /16;
	char pin = PortPin%16;
	Timer target_tim = PIN_TIMER_MAP_FUNC(port,pin);
	target_tim.timer->DIER |= (1 << target_tim.channel);
	TimerEnIRQ(target_tim.timer_num);
	
}

void TimerCompIRQ(char PortPin, int arr, int compare){
	char port  = PortPin /16;
	char pin = PortPin%16;
	timer_compare_micro(port, pin, arr, compare);
	timerCompIrQEn(PortPin);
}


void timer_pwm_micro(char PortPin, int arr, int compare){
	
	char port  = PortPin /16;
	char pin = PortPin%16;
	Timer target_tim = PIN_TIMER_MAP_FUNC(port,pin);
	TIM_TypeDef * tim = target_tim.timer;
	char timer = target_tim.timer_num;
	char channel = target_tim.channel;
	short new_clock_speed = (clock_speed/timer_clock_div(timer));
	if ((tim->CCER & (1 << ((channel-1)*4)) ) == 0)
	{
		timer_startRCC(timer);
		//init_GP(port,pin,OUT50,O_AF_PP);
		
		Timer_Pin_set(port,pin, timer);
		
		
		tim->PSC = (new_clock_speed-1);

		switch(channel)
		{
			case 1: tim->CCMR1 |= 0x60;break;
			case 2: tim->CCMR1 |= 0x6000;break;
			case 3: tim->CCMR2 |= 0x60;break;
			case 4: tim->CCMR2 |= 0x6000;break;
		}
		tim->CCER |= (1 << ((channel-1)*4));
		tim->BDTR |= 0x8000;
		tim->CR1 |=1;
	}
	tim->ARR = (arr-1);
	switch(channel)
	{
		case 1: tim->CCR1 = compare; break;
		case 2: tim->CCR2 = compare; break;
		case 3: tim->CCR3 = compare; break;
		case 4: tim->CCR4 = compare; break;
	}
}
void timer_pwm_milli(char PortPin, int arr, int compare){
	
	char port  = PortPin /16;
	char pin = PortPin%16;
	
	Timer target_tim = PIN_TIMER_MAP_FUNC(port,pin);
	TIM_TypeDef * tim = target_tim.timer;
	char timer = target_tim.timer_num;
	char channel = target_tim.channel;
	short new_clock_speed = (clock_speed/timer_clock_div(timer));
	if ((tim->CCER & (1 << ((channel-1)*4)) ) == 0)
	{
		timer_startRCC(timer);
		//init_GP(port,pin,OUT50,O_AF_PP);
		
		Timer_Pin_set(port,pin, timer);
		
		
		tim->PSC = (new_clock_speed*250-1);
		switch(channel)
		{
			case 1: tim->CCMR1 |= 0x60;break;
			case 2: tim->CCMR1 |= 0x6000;break;
			case 3: tim->CCMR2 |= 0x60;break;
			case 4: tim->CCMR2 |= 0x6000;break;
		}
		tim->CCER |= (1 << ((channel-1)*4));
		tim->BDTR |= 0x8000;
		tim->CR1 |=1;
	}
	tim->ARR = (arr*4-1);
	
	compare *= 4;
	
	switch(channel)
	{
		case 1: tim->CCR1 = compare; break;
		case 2: tim->CCR2 = compare; break;
		case 3: tim->CCR3 = compare; break;
		case 4: tim->CCR4 = compare; break;
	}
}
/*********************************************************

                   Motor Driver

**********************************************************/
void ESCDivX(char PortPin,unsigned int Div,unsigned int speed)
{
	unsigned int MaxDiv = 1000, nominalSpeed = 1000, Cycle = 20000;
	if(Div == 0)
	{
		Div = MaxDiv;
	}
	if(speed>Div)
	{
		speed = Div;
	}
	else{
		speed = (speed*MaxDiv)/Div;
	}
	unsigned int NewSpeed = nominalSpeed + speed;
	timer_pwm_micro(PortPin,Cycle, NewSpeed);
}
void ESCDiv100(char PortPin,unsigned int speed){
	ESCDivX(PortPin,100,speed);
}

