/**
 * @file  LED.h
 * @brief This file is to be used as an implementation of the LED driver.
 *
 * @author MSN
 * @date Mar 31, 2020
 *
 */

#ifndef LED_H
#define LED_H

#define LED_ACTIVE_LOW  0
#define LED_ACTIVE_HIGH 1


/**
 * @brief Function To initialize LED pin and clock.
 * @param void
 * @return void
 */
void LED_voidInit(void);


/**
 * @brief Function put LED on.
 * @param LED_Number: led number ( LED1 )
 * @return void
 */
void LED_voidON(u8 LED_Number);


/**
 * @brief Function put LED off
 * @param LED_Number: LED number ( LED1 )
 * @return void
 */
void LED_voidOFF(u8 LED_Number);

#endif
