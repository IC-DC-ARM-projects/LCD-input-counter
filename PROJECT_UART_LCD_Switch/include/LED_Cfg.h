/**
 * @file  LED_Cfg.h
 * @brief This file is to be used as an implementation of the LED configuration.
 *
 * @author MSN
 * @date Mar 31, 2020
 *
 */

#ifndef LED_CFG_H
#define LED_CFG_H


typedef struct
{
	GPIO_t LED_IO;
	u8 activeState;
} LED_cfg_t;


#define LED_CFGNUMBER           1


#endif
