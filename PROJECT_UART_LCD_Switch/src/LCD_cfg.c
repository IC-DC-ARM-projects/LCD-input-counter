
/********************************************************************************
**  FILENAME     : LCD_Cfg.c        			                               **
**  VERSION      : 1.0                                                         **
**  DATE         : 23 Mar 2020                                                 **                                                                         **
**  PLATFORM     : STM		                                                   **
**  AUTHOR       : Nada Mohamed                                                **
*********************************************************************************/
#include "STD_TYPES.h"
#include "GPIO.h"
#include "LCD.h"
#include "LCD_cfg.h"


static const GPIO_t LCD_Configuration[] =
{
	{        //Data
		.pin = GPIO_PIN0_SELECT |
		       GPIO_PIN1_SELECT |
			    GPIO_PIN2_SELECT |
			    GPIO_PIN3_SELECT |
			    GPIO_PIN4_SELECT |
			    GPIO_PIN5_SELECT |
			    GPIO_PIN6_SELECT |
			    GPIO_PIN7_SELECT,

		.mode  = GPIO_PIN_ALL_MODE_OUTPUT_PUSH_PULL,
		.speed = GPIO_PIN_ALL_SPEED_2MHZ,
		.port  = GPIO_PIN_ALL_PORTA,
	},
	{        // RS
		.pin   = GPIO_PIN12_SELECT,
		.mode  = GPIO_PIN12_MODE_OUTPUT_PUSH_PULL,
		.speed = GPIO_PIN12_SPEED_2MHZ,
		.port  = GPIO_PIN12_PORTB,
	},
	{        // RW
		.pin   = GPIO_PIN13_SELECT,
		.mode  = GPIO_PIN13_MODE_OUTPUT_PUSH_PULL,
		.speed = GPIO_PIN13_SPEED_2MHZ,
		.port  = GPIO_PIN13_PORTB,
	},
	{        // E
		.pin   = GPIO_PIN14_SELECT,
		.mode  = GPIO_PIN14_MODE_OUTPUT_PUSH_PULL,
		.speed = GPIO_PIN14_SPEED_2MHZ,
		.port  = GPIO_PIN14_PORTB,
	}

};

GPIO_t* LCD_u32GetLcdConfiguration()
{
	return (GPIO_t*)LCD_Configuration;
}
