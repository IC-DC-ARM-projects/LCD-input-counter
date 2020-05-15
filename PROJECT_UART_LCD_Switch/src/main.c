/* libs */
#include "STD_TYPES.h"
/* MCAL */
#include "RCC.h"
#include "UART.h"
/* HAL */
#include "UART_handler.h"
#include "LED.h"
#include "LCD.h"
#include "switch_interface.h"
/* Services */
#include "sched_interface.h"
#include <diag/Trace.h>

/* switch */
#define SWITCH_A11 0
/* internal LED */
#define LED_C13   0

#define LED_INTERNAL_OFF 0
#define LED_INTERNAL_ON  1

/* app callback */
void app_task(void);

/* scheduler object, defined by:
 * runnable function,
 * period (ms) */
SCHED_task_t const task_app = {
	.runnable = &app_task,
	.periodicTimeMs = 300,
};

static u8 RXbuffer[2];
static u8 RXbuffer_previous;
static u8 number = '0';

void ReceiveData(void)
{
	if (RXbuffer[0] != RXbuffer_previous) /* if new data */
	{
		RXbuffer_previous = RXbuffer[0];
		trace_printf("UART Rx CB = %c\n", RXbuffer[0]);

		LCD_WriteString(RXbuffer, 1);
	}
	else /* if same data */
	{

	}
}

void transmitData(void)
{
	trace_printf("UART Tx CB = %c\n", number);
}

void LCD_CB(void)
{
	trace_printf("LCD CB\n");
}

void main(void)
{
	/* turn on HSE */
	RCC_SetClock(RCC_CR_HSE, ON);

	/* switch system clock to HSE */
	Select_SystemClock(RCC_CFGR_SW_HSE);

	/* HCLK = PPRECLK1,2 = div1 */
	RCC_HPRE_SetPrescaler(RCC_CFGR_HPRE_div_1);
	RCC_PPRE1_SetPrescaler(RCC_CFGR_PPRE1_div_1);
	RCC_PPRE2_SetPrescaler(RCC_CFGR_PPRE2_div_1);

	/* enable clocks for ports A, B, C, and USART1 */
	RCC_EnablePeripheral_APB2(RCC_APB2ENR_IOPAEN_PORTA);
	RCC_EnablePeripheral_APB2(RCC_APB2ENR_IOPBEN_PORTB);
	RCC_EnablePeripheral_APB2(RCC_APB2ENR_IOPCEN_PORTC);
	RCC_EnablePeripheral_APB2(RCC_APB2ENR_USART1EN);

	/* init Switch module */
	Switch_Init();

	/* init LCD module */
	LCD_SetCbf(LCD_CB);
	LCD_voidInit();

	/* init LCD module */
	LED_voidInit();

	/* init UART module */
	UART_SetTransmissionCbf(transmitData);
	UART_SetRecieverCbf(ReceiveData);
	HUART_InitGPIO();
	HUART_EnableIRQ();
	UART_Init();

	/* init Scheduler */
	SCHED_Init();

	SCHED_Start();
}

void app_task(void)
{
	static u8 led_state = LED_INTERNAL_ON;

	UART_RecieveData(RXbuffer, 1);

	/* send number on UART */
	UART_SendData(&number, 1, USART1_Peripherial);

	if (Switch_GetReading(SWITCH_A11) == SWITCH_PRESSED) /* if switch is pressed */
	{
		if (led_state == LED_INTERNAL_OFF) /* if LED is already off, then turn it on */
		{
			led_state = LED_INTERNAL_ON;
			LED_voidON(LED_C13);
		}
		else /* if LED is already on, then turn it off */
		{
			led_state = LED_INTERNAL_OFF;
			LED_voidOFF(LED_C13);
		}

		/* limit value at 9 (only increment if value < 9) */
		if (number == '9') /* if value reached its limit, then reset */
		{
			number = '0';
		}
		else /* if value didn't reach its limit, then increment */
		{
			number++;
		}
	}

	else /* if switch is not pressed */
	{

	}
}
