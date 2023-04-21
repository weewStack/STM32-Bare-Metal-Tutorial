


#define HSI 0	// MCO1 Only
#define LSE 1 // MCO1 Only

#define SYSCLK 0  // MCO2 Only
#define PLLI2S 1	// MCO2 Only

#define HSE	2	// Both MCO2 & MCO1 
#define PLL 3 // Both MCO2 & MCO1 


#define SWS_HSI 0
#define SWS_HSE 1
#define SWS_PLL 2



#define MCO_DIV_1  0b000
#define MCO_DIV_2  0b100
#define MCO_DIV_3  0b101
#define MCO_DIV_4  0b110
#define MCO_DIV_5  0b111


//#define PLLP_POS 	16
#define PLL_P_POS 16
#define PLL_N_POS 6
#define PLL_Q_POS 24

#define AHBPrescalerPos 	4
#define APB1PrescalerPos 	10
#define APB2PrescalerPos 	13


#define Pll_SRC_HSI_HSI 0
#define Pll_SRC_HSI_HSE 1

#define HSIClkSpeed   16

#if defined(STM32F405xx)
  #define HSEClkSpeed   8
#elif defined(STM32F415xx)
  #define HSEClkSpeed   8
#elif defined(STM32F407xx)
  #define HSEClkSpeed   8
#elif defined(STM32F417xx)
  #define HSEClkSpeed   8
#elif defined(STM32F427xx)
  #define HSEClkSpeed   8
#elif defined(STM32F437xx)
  #define HSEClkSpeed   8
#elif defined(STM32F429xx)
  #define HSEClkSpeed   8
#elif defined(STM32F439xx)
  #define HSEClkSpeed   8
#elif defined(STM32F401xC)
  #define HSEClkSpeed   8
#elif defined(STM32F401xE)
  #define HSEClkSpeed   8
#elif defined(STM32F410Tx)
  #define HSEClkSpeed   8
#elif defined(STM32F410Cx)
  #define HSEClkSpeed   8
#elif defined(STM32F410Rx)
  #define HSEClkSpeed   8
#elif defined(STM32F411xE)
  #define HSEClkSpeed   25
#elif defined(STM32F446xx)
  #define HSEClkSpeed   8
#elif defined(STM32F469xx)
  #define HSEClkSpeed   8
#elif defined(STM32F479xx)
  #define HSEClkSpeed   8
#elif defined(STM32F412Cx)
  #define HSEClkSpeed   8
#elif defined(STM32F412Zx)
  #define HSEClkSpeed   8
#elif defined(STM32F412Rx)
  #define HSEClkSpeed   8
#elif defined(STM32F412Vx)
  #define HSEClkSpeed   8
#elif defined(STM32F413xx)
  #define HSEClkSpeed   8
#elif defined(STM32F423xx)
  #define HSEClkSpeed   8
#else
 #error "Please select first the target STM32F4xx device used in your application (in stm32f4xx.h file)"
#endif


void ClockPllOn(void);
void ClockHseOn(void);
void Clock_MCO1(char clock, char div);
void Clock_MCO2(char clock, char div);
int ClockPll(void);
int ClockSysSpeed(void);
void ClockSpeedSetHSE(int M,int N, int P,  int Q, int AHBPrescaler, int APB1Prescaler, int APB2Prescaler);

void Clk_STM32F407_168Mhz(void);
void Clk_STM32F411_100Mhz(void);



