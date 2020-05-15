/**
 * @file  LCD.h
 * @brief This file is to be used as an implementation of the UART handler
 *
 * @author MSN
 * @date Mar 31, 2020
 *
 */

#ifndef UART_HANDLER_H_
#define UART_HANDLER_H_


/**
 * @brief Initialize UART pins
 * @param void
 * @return void
 */
void HUART_InitGPIO(void);


/**
 * @brief Enable UART IRQ
 * @param void
 * @return void
 */
void HUART_EnableIRQ(void);


#endif
