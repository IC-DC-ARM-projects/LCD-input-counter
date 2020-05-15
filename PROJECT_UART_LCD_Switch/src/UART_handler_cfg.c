#include "STD_TYPES.h"
#include "GPIO.h"

typedef struct{
	GPIO_t txPin;
	GPIO_t rxPin;
}uartBusPins_t;

#define NUM_OF_UART_BUS 3
uartBusPins_t uartBusCfg[NUM_OF_UART_BUS] = {
		[0] = {
				.txPin = {
						.pin   = GPIO_PIN9_SELECT,
						.mode  = GPIO_PIN9_MODE_OUTPUT_AF_PUSH_PULL,
						.speed = GPIO_PIN9_SPEED_50MHZ,
						.port  = GPIO_PIN9_PORTA
				},
		},
};
/* UART1 IO pins */
GPIO_t HUART_GPIO_Configuration[2] =
{
	/* Tx pin: A9 */
	{
		.pin   = GPIO_PIN9_SELECT,
		.mode  = GPIO_PIN9_MODE_OUTPUT_AF_PUSH_PULL,
		.speed = GPIO_PIN9_SPEED_50MHZ,
		.port  = GPIO_PIN9_PORTA,
	},

	/* Rx pin: A10 */
	{
		.pin   = GPIO_PIN10_SELECT,
		.mode  = GPIO_PIN10_MODE_INPUT_FLOATING,
		.speed = GPIO_PIN10_SPEED_NONE,
		.port  = GPIO_PIN10_PORTA,
	}
};

