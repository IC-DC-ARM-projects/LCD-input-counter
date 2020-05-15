/*******************************************************************************
**  FILENAME     : LED.c         			                                  **
**  VERSION      : 1.0                                                        **
**  DATE         : 17 Feb 2020                                                **                                                                         **
**  PLATFORM     : STM		                                                  **
**  AUTHOR       : Nada Mohamed                                               **
*******************************************************************************/

#include "STD_TYPES.h"
#include "LED.h"
#include "GPIO.h"
#include "LED_Cfg.h"

/************************************************************
 * this Function to return the container data (array of struct )
 * Return Type :-
 *            GPIO_t* ( pointer of struct GPIO_t)
 *Input Argument :-
 *             void
 *
 *************************************************************/
LED_cfg_t* LED_u32GetLedConfiguration();

/******************************************************************
 * Function To initialize LED PIN and Clock.
 * return Type :- void
 * Input Argument :- void
 *****************************************************************/
void LED_voidInit(void)
{
	LED_cfg_t* LED_Configuration= LED_u32GetLedConfiguration();

	for(u8 iterator=0;iterator<LED_CFGNUMBER;iterator++)
	{
		GPIO_InitPin(&LED_Configuration[iterator].LED_IO);

	}
}


/******************************************************************
 * Function To put led  on
 * return Type :- void
 * Input Argument :-LED_Number
 *                  LED1
 *                  LED2
 ******************************************************************/
void LED_voidON(u8 LED_Number)
{
	LED_cfg_t* LED_Configuration= LED_u32GetLedConfiguration();

	switch(LED_Configuration->activeState)
	{
	case LED_ACTIVE_HIGH:
	    GPIO_WritePin( &LED_Configuration[LED_Number].LED_IO, GPIO_PIN_ALL_VALUE_HIGH );
	break;

	case LED_ACTIVE_LOW:
	    GPIO_WritePin( &LED_Configuration[LED_Number].LED_IO, GPIO_PIN_ALL_VALUE_LOW );
	break;
	}
}


/******************************************************************
 * Function To put led  off
 * return Type :- void
 * Input Argument :-LED_Number
 *                  LED1
 *                  LED2
 ******************************************************************/
void LED_voidOFF(u8 LED_Number)
{
	LED_cfg_t* LED_Configuration= LED_u32GetLedConfiguration();

	switch(LED_Configuration->activeState)
	{
	case LED_ACTIVE_HIGH:
	    GPIO_WritePin( &LED_Configuration[LED_Number].LED_IO, GPIO_PIN_ALL_VALUE_LOW );
	break;

	case LED_ACTIVE_LOW:
	    GPIO_WritePin( &LED_Configuration[LED_Number].LED_IO, GPIO_PIN_ALL_VALUE_HIGH );
	break;
	}
}
