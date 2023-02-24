
	


#define HSI 0
#define LSE 1
#define HSE	2
#define PLL 3


#define SYSCLK 0
#define PLLI2S 1




#define PLL_411_M  25
#define PLL_411_P  0
#define PLL_411_N  192
#define PLL_411_Q  4


#define PLL_407_M  4
#define PLL_407_P  0
#define PLL_407_N  (168>>1)
#define PLL_407_Q  4







void Clock_MCO1(char clock, char div);
void Clock_MCO2(char clock, char div);

void Clock_F411_96MHZ(void);
void Clock_F407_168MHZ(void);

