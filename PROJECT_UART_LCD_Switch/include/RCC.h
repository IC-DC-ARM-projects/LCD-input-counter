/**
 * @file  RCC.h
 * @brief This file is to be used as an implementation of the RCC driver.
 *
 * @author MSN
 * @date Mar 31, 2020
 *
 */

#ifndef RCC_H_
#define RCC_H_

#include "STD_TYPES.h"

typedef u32       ClockSource_ReturnType;

#define ClockSourceType  (u32)

#define RCC_CR_HSI        (u32)0x00000001
#define RCC_CR_HSIRDY     (u32)0x00000002

#define RCC_CR_HSE        (u32)0x00010000
#define RCC_CR_HSERDY     (u32)0x00020000

#define RCC_CR_HSEBYP     (u32)0x00030000
#define RCC_CR_CSSON      (u32)0x00040000

#define RCC_CR_PLL        (u32)0x01000000
#define RCC_CR_PLLRDY     (u32)0x02010000



#define RCC_CFGR_SW_HSI         (u32)0x00000000
#define RCC_CFGR_SW_HSE         (u32)0x00000001
#define RCC_CFGR_SW_PLL         (u32)0x00000002

#define RCC_CFGR_SWS_HSI            (u32)0x0
#define RCC_CFGR_SWS_HSE     		   (u32)0x4
#define RCC_CFGR_SWS_PLL      		(u32)0x8



#define RCC_CFGR_PLLMUL_2           (u32)0x00000000
#define RCC_CFGR_PLLMUL_3        	(u32)0x00040000
#define RCC_CFGR_PLLMUL_4        	(u32)0x00080000
#define RCC_CFGR_PLLMUL_5           (u32)0x000C0000
#define RCC_CFGR_PLLMUL_6           (u32)0x00100000
#define RCC_CFGR_PLLMUL_7           (u32)0x00140000
#define RCC_CFGR_PLLMUL_8        	(u32)0x00180000
#define RCC_CFGR_PLLMUL_9        	(u32)0x001C0000
#define RCC_CFGR_PLLMUL_10       	(u32)0x00200000
#define RCC_CFGR_PLLMUL_11       	(u32)0x00240000
#define RCC_CFGR_PLLMUL_12        	(u32)0x00280000
#define RCC_CFGR_PLLMUL_13        	(u32)0x002C0000
#define RCC_CFGR_PLLMUL_14        	(u32)0x00300000
#define RCC_CFGR_PLLMUL_15        	(u32)0x00340000
#define RCC_CFGR_PLLMUL_16      	   (u32)0x00380000



#define RCC_CFGR_PLLXTPRESRC_HSE_divided_1        (u32)0x00010000
#define RCC_CFGR_PLLXTPRESRC_HSE_divided_2        (u32)0x00030000
#define RCC_CFGR_PLLXTPRESRC_HSI_divided_2        (u32)0x00000000



#define RCC_CFGR_PPRE1_div_1            (u32)0x00000000
#define RCC_CFGR_PPRE1_div_2            (u32)0x00000400
#define RCC_CFGR_PPRE1_div_4            (u32)0x00000500
#define RCC_CFGR_PPRE1_div_8            (u32)0x00000600
#define RCC_CFGR_PPRE1_div_16           (u32)0x00000700



#define RCC_CFGR_PPRE2_div_1 			(u32)0x00000000
#define RCC_CFGR_PPRE2_div_2 			(u32)0x00002000
#define RCC_CFGR_PPRE2_div_4 			(u32)0x00002800
#define RCC_CFGR_PPRE2_div_8			(u32)0x00003000
#define RCC_CFGR_PPRE2_div_16			(u32)0x00003800



#define RCC_CFGR_HPRE_div_1            (u32)0x00000000
#define RCC_CFGR_HPRE_div_2            (u32)0x00000080
#define RCC_CFGR_HPRE_div_4            (u32)0x00000090
#define RCC_CFGR_HPRE_div_8            (u32)0x000000A0
#define RCC_CFGR_HPRE_div_16           (u32)0x000000B0
#define RCC_CFGR_HPRE_div_64           (u32)0x000000C0
#define RCC_CFGR_HPRE_div_128          (u32)0x000000D0
#define RCC_CFGR_HPRE_div_256          (u32)0x000000E0
#define RCC_CFGR_HPRE_div_512          (u32)0x000000F0



#define RCC_CFGR_ADCPRE_div_2      (u32)0x0
#define RCC_CFGR_ADCPRE_div_4      (u32)0x4000
#define RCC_CFGR_ADCPRE_div_6      (u32)0x8000
#define RCC_CFGR_ADCPRE_div_8      (u32)0xc000



#define RCC_CFGR_MCO_NOCLK    (u32)0x00000000
#define RCC_CFGR_MCO_SYSCLK   (u32)0x4000000
#define RCC_CFGR_MCO_HSI      (u32)0x5000000
#define RCC_CFGR_MCO_HSE      (u32)0x6000000
#define RCC_CFGR_MCO_PLL      (u32)0x7000000



#define RCC_APB2ENR_AFIOEN_Enable      (u32)0x1
#define RCC_APB2ENR_AFIOEN_Disable     (u32)0x0

#define RCC_APB2ENR_IOPAEN_PORTA      (u32)0x4
#define RCC_APB2ENR_IOPBEN_PORTB      (u32)0x8
#define RCC_APB2ENR_IOPCEN_PORTC      (u32)0x10
#define RCC_APB2ENR_IOPDEN_PORTD      (u32)0x20
#define RCC_APB2ENR_IOPEEN_PORTE      (u32)0x40
#define RCC_APB2ENR_IOPFEN_PORTF      (u32)0x80
#define RCC_APB2ENR_IOPGEN_PORTG      (u32)0x100
#define RCC_APB2ENR_ADC1EN      	     (u32)0x200
#define RCC_APB2ENR_ADC2EN      	     (u32)0x400
#define RCC_APB2ENR_TIM1EN      	     (u32)0x800
#define RCC_APB2ENR_SPI1EN      	     (u32)0x1000
#define RCC_APB2ENR_TIM8EN      	     (u32)0x2000
#define RCC_APB2ENR_TIM9EN      	     (u32)0x80000
#define RCC_APB2ENR_TIM10EN     	     (u32)0x100000
#define RCC_APB2ENR_TIM11EN    		  (u32)0x200000
#define RCC_APB2ENR_USART1EN     	  (u32)0x4000
#define RCC_APB2ENR_ADC3EN      	     (u32)0x8000
#define RCC_APB2ENR_ADC3EN     		  (u32)0x8000



#define RCC_APB1ENR_USART2EN          (u32)0x20000
#define RCC_APB1ENR_USART3EN          (u32)0x40000
#define RCC_APB1ENR_UART4EN           (u32)0x80000
#define RCC_APB1ENR_UART5EN           (u32)0x100000



#define ON  1
#define OFF 0


/**
 * @brief Select system clock
 * @param SystemClock: system clock \n
 *                     RCC_CFGR_SW_HSI \n
 *                     RCC_CFGR_SW_HSE \n
 *                     RCC_CFGR_SW_PLL
 *@return void
 */
extern void Select_SystemClock(u32 SystemClock);


/**
 * @brief Set the clock
 * @param clock: system clock \n
 *               RCC_CR_HSI \n
 *    			  RCC_CR_HSE \n
 *               RCC_CR_PLL
 * @param State: clock state \n
 *               ON \n
 *               OFF
 *@return void
 */
extern void RCC_SetClock(u32 Clock ,u8 State);

/**
 * @brief check system clock
 * @return ClockSource_ReturnType \n
 *         HSI = RCC_CFGR_SWS_HSI \n
 *		 	  PLL = RCC_CFGR_SWS_PLL \n
 *		 	  HSE = RCC_CFGR_SWS_HSE
 */
ClockSource_ReturnType RCC_CheckSystemClock(void);


/**
 * @brief Configure PLL
 * @param RCC_PLLSource: \n
 *        RCC_CFGR_PLLXTPRESRC_HSE_divided_1 \n
 *   		 RCC_CFGR_PLLXTPRESRC_HSE_divided_2 \n
 *        RCC_CFGR_PLLXTPRESRC_HSI_divided_2 \n
 *        RCC_CR_PLLON
 * @param RCC_PLLMUL: \n
		    RCC_CFGR_PLLMUL_2 \n
			 RCC_CFGR_PLLMUL_3 \n
			 RCC_CFGR_PLLMUL_4 \n
			 RCC_CFGR_PLLMUL_5 \n
			 RCC_CFGR_PLLMUL_6 \n
			 RCC_CFGR_PLLMUL_7 \n
			 RCC_CFGR_PLLMUL_8 \n
			 RCC_CFGR_PLLMUL_9 \n
			 RCC_CFGR_PLLMUL_10 \n
			 RCC_CFGR_PLLMUL_11 \n
			 RCC_CFGR_PLLMUL_12 \n
			 RCC_CFGR_PLLMUL_13 \n
			 RCC_CFGR_PLLMUL_14 \n
			 RCC_CFGR_PLLMUL_15 \n
			 RCC_CFGR_PLLMUL_16
 */
extern void RCC_PLLConfiguration(u32 RCC_PLLSource , u32 RCC_PLLMUL);




/**
 * @brief Set prescaler for PPRE2
 * @param Prescaler: \n
		    RCC_CFGR_PPRE2_div_1  -> HCLK not divided \n
		    RCC_CFGR_PPRE2_div_2  -> HCLK divided by 2 \n
		    RCC_CFGR_PPRE2_div_4  -> HCLK divided by 4 \n
		    RCC_CFGR_PPRE2_div_8  -> HCLK divided by 8 \n
		    RCC_CFGR_PPRE2_div_16 -> HCLK divided by 16
   @return void
 */
extern void RCC_PPRE2_SetPrescaler(u32 Prescaler);


/**
 * @brief Set prescaler for PPRE1
 * @param Prescaler: \n
 *        RCC_CFGR_PPRE1_div_1  -> HCLK not divided \n
		    RCC_CFGR_PPRE1_div_2  -> HCLK divided by 2 \n
		    RCC_CFGR_PPRE1_div_4  -> HCLK divided by 4 \n
		    RCC_CFGR_PPRE1_div_8  -> HCLK divided by 8 \n
		    RCC_CFGR_PPRE1_div_16 -> HCLK divided by 16
 * @return void
 */
extern void RCC_PPRE1_SetPrescaler(u32 Prescaler);


/**
 * @brief Set prescaler for HPRE
 * @param Prescaler: \n
		    RCC_CFGR_HPRE_div_1   -> HCLK not divided \n
		    RCC_CFGR_HPRE_div_2   -> HCLK divided by 2 \n
		    RCC_CFGR_HPRE_div_4   -> HCLK divided by 4 \n
		    RCC_CFGR_HPRE_div_8	  -> HCLK divided by 8 \n
		    RCC_CFGR_HPRE_div_16  -> HCLK divided by 16 \n
		    RCC_CFGR_HPRE_div_64  -> HCLK divided by 64 \n
		    RCC_CFGR_HPRE_div_128 -> HCLK divided by 128 \n
		    RCC_CFGR_HPRE_div_256 -> HCLK divided by 256 \n
		    RCC_CFGR_HPRE_div_512 -> HCLK divided by 512
 * @return void
 */
extern void RCC_HPRE_SetPrescaler(u32 Prescaler);



/**
 * @brief ADC prescaler function take one argument
 * @param Prescaler: \n
			 RCC_CFGR_ADCPRE_div_2 : PCLK2 divided by 2 \n
			 RCC_CFGR_ADCPRE_div_4 : PCLK2 divided by 4 \n
			 RCC_CFGR_ADCPRE_div_6 : PCLK2 divided by 6 \n
			 RCC_CFGR_ADCPRE_div_8 : PCLK2 divided by 8
 * @return void
 */
extern void RCC_ADCPRE_SetPrescaler(u32 Prescaler);



/**
 * @brief Select MCO: Microcontroller Clock Output take one argument from
 * @param Clock: \n
			 RCC_CFGR_MCO_NOCLK  -> No clock \n
			 RCC_CFGR_MCO_SYSCLK -> System clock (SYSCLK) selected \n
			 RCC_CFGR_MCO_HSI    -> HSI clock selected \n
			 RCC_CFGR_MCO_HSE    -> HSE clock selected \n
			 RCC_CFGR_MCO_PLL    -> PLL clock selected
 * @return void
 */
extern void RCC_SelectMCO(u32 Clock);



/**
 * @brief APB2 enable peripheral
 * @param Peripheral: \n
			 RCC_APB2ENR_AFIOEN_Enable    AFIOEN:   Alternate function IO clock enable \n
			 RCC_APB2ENR_IOPAEN_PORTA     IOPAEN:   IO port A clock enable \n
			 RCC_APB2ENR_IOPBEN_PORTB     IOPBEN:   IO port B clock enable \n
			 RCC_APB2ENR_IOPCEN_PORTC     IOPCEN:   IO port C clock enable \n
			 RCC_APB2ENR_IOPDEN_PORTD     IOPDEN:   IO port D clock enable \n
			 RCC_APB2ENR_IOPEEN_PORTE     IOPEEN:   IO port E clock enable \n
			 RCC_APB2ENR_IOPFEN_PORTF     IOPFEN:   IO port F clock enable \n
			 RCC_APB2ENR_IOPGEN_PORTG     IOPGEN:   IO port G clock enable \n
			 RCC_APB2ENR_ADC1EN      	   ADC1EN:   ADC 1 interface clock enable \n
			 RCC_APB2ENR_ADC2EN      	   ADC2EN:   ADC 2 interface clock enable \n
			 RCC_APB2ENR_TIM1EN      	   TIM1EN:   TIM1 timer clock enable \n
			 RCC_APB2ENR_SPI1EN      	   TIM8EN:   TIM8 Timer clock enable \n
			 RCC_APB2ENR_TIM8EN      	   TIM8EN:   TIM8 Timer clock enable \n
			 RCC_APB2ENR_TIM9EN      	   TIM9EN:   TIM9 Timer clock enable \n
			 RCC_APB2ENR_TIM10EN     	   TIM10EN:  TIM10 timer clock enable \n
			 RCC_APB2ENR_TIM11EN    	   TIM11EN:  TIM11 Timer clock enable \n
			 RCC_APB2ENR_USART1EN     	   USART1EN: USART1 clock enable \n
			 RCC_APB2ENR_ADC3EN      	   ADC3EN:   ADC3 interface clock enable
 * @return void
 */
extern void RCC_EnablePeripheral_APB2(u32 Peripheral);


/**
 * @brief Enable peripheral APB1
 * @param Peripheral: \n
			 RCC_APB1ENR_USART2EN -> USART2 clock enabled \n
			 RCC_APB1ENR_USART3EN -> USART3 clock enabled \n
			 RCC_APB1ENR_UART4EN  -> UART4 clock enabled \n
			 RCC_APB1ENR_UART5EN  -> UART5 clock enabled
 * @return void
 */
extern void RCC_EnablePeripheral_APB1(u32 Peripheral);

#endif /* RCC_H_ */

