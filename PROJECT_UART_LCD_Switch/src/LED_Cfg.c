
/********************************************************************************
**  FILENAME     : LED_Cfg.c        			                               **
**  VERSION      : 1.0                                                         **
**  DATE         : 17 Feb 2020                                                 **                                                                         **
**  PLATFORM     : STM		                                                   **
**  AUTHOR       : Nada Mohamed                                                **
*********************************************************************************/

#include "STD_TYPES.h"
#include "GPIO.h"
#include "LED.h"
#include "LED_Cfg.h"

static const LED_cfg_t LED_Configuration[] =
{
	{
		.LED_IO = {
			.pin   = GPIO_PIN13_SELECT,
			.mode  = GPIO_PIN13_MODE_OUTPUT_PUSH_PULL,
			.speed = GPIO_PIN13_SPEED_2MHZ,
			.port  = GPIO_PIN13_PORTC,
		},

		.activeState = LED_ACTIVE_LOW,
	}
};


/************************************************************
 * this Function to return the container data (array of struct )
 * Return Type :-
 *            GPIO_t* ( pointer of struct GPIO_t)
 *Input Argument :-
 *             void
 *
 *************************************************************/
LED_cfg_t* LED_u32GetLedConfiguration()
{
	return (LED_cfg_t*)LED_Configuration;
}

