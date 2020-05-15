#include "STD_TYPES.h"
#include "UART.h"
#include "UART_cfg.h"
#include "GPIO.h"
#include "NVIC.h"

#define HUART_TX_PIN 0
#define HUART_RX_PIN 1

extern GPIO_t HUART_GPIO_Configuration[2];

static const u8 UART_IRQ_Number[] = {
		USART1_IRQNUMBER,
		USART2_IRQNUMBER,
		USART3_IRQNUMBER,
		UART4_IRQNUMBER,
		UART5_IRQNUMBER
};

void HUART_InitGPIO(void)
{
	GPIO_InitPin(&HUART_GPIO_Configuration[HUART_TX_PIN]);
	GPIO_InitPin(&HUART_GPIO_Configuration[HUART_RX_PIN]);
}

void HUART_EnableIRQ(void)
{
	for(u8 Copy_index =0 ;Copy_index <UART_COUNT;Copy_index++)
	{
		//NVIC_ClearPendingIRQ(UART_IRQ_Number[Copy_index]);
		//NVIC_SetPriorityGrouping(3);
		//NVIC_SetPriority(UART_IRQ_Number[Copy_index], 1);
		NVIC_EnableIRQ(UART_IRQ_Number[Copy_index]);
		NVIC_EnableAllInterrupt();
	}
}
