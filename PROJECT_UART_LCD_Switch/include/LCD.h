/**
 * @file  LCD.h
 * @brief This file is to be used as an implementation of the LCD driver.
 *
 * @author MSN
 * @date Mar 31, 2020
 *
 */

#ifndef LCD_H
#define LCD_H


typedef u8          Std_ReturnType;

#define E_OK        (Std_ReturnType)0
#define E_NOT_OK    (Std_ReturnType)1
#define E_BUSY      (Std_ReturnType)2



#define LCD_8_BIT_1_LINE   			 0x30
#define LCD_8_BIT_2_LINE   			 0x38
#define LCD_4_BIT_1_LINE   			 0x20
#define LCD_4_BIT_2_LINE   			 0x28

#define LCD_CLEAR_SCREEN   		 	 0x01

#define LCD_DISPLAY_OFF_CURSOR_OFF       0x08
#define LCD_DISPLAY_ON_CURSOR_ON         0x0E
#define LCD_DISPLAY_ON_CURSOR_OFF        0x0C
#define LCD_DISPLAY_ON_CURSOR_Blinging   0x0F

#define LCD_FIRST_LINE                   1U
#define LCD_SECOND_LINE                  2U

typedef void (*APPNotifiactionCbf_t) (void);

/**
 * @brief Initialize LCD pins
 * @param void
 * @return void
 */
void LCD_voidInit(void);



/**
 * @brief Write string on LCD
 * @param Copy_ptStringData: Pointer to string
 * @param Copy_u16StringLength: String length
 * @return Std_ReturnType \n
 *         E_OK     : Service request accepted \n
			  E_NOT_OK : Service request not accepted \n
			  E_BUSY   : transmit request could not be processed because no \n
			    	       transmit object was available
 */
Std_ReturnType LCD_WriteString(const u8* Copy_ptStringData ,u16 Copy_u16StringLength);


/**
 * @brief Clear the LCD screen
 * @param void
 * @return Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted . \n
			  E_BUSY   : transmit request could not be processed because no \n
					       transmit object was available
 */
Std_ReturnType LCD_ClearScreen(void);


/**
 * @brief To move the cursor to the location
 * @param Copy_Line: LCD line
 * @param Copy_Column: LCD column
 * @return Std_ReturnType  \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted .\n
			  E_BUSY   : transmit request could not be processed because no \n
					       transmit object was available
 */
Std_ReturnType LCD_GotoLocation(u8 Copy_Line , u8 Copy_Column);


/**
 * @brief Callback function to handle any application function \n
*         it run after \n
*         1- the writing to LCD is finished.  -> LCD_WriteString() finish successfully \n
*         2- move cursor                      -> LCD_GotoLocation() finish successfully \n
*         3- clear screen                     -> LCD_ClearScreen()  finish successfully
*  @param Copy_SetCbf: pointer to function
*  @return Std_ReturnType \n
			  E_OK     : Service request accepted . \n
			  E_NOT_OK : Service request not accepted . \n
			  E_BUSY   : transmit request could not be processed because no \n
					       transmit object was available
 */
Std_ReturnType LCD_SetCbf(APPNotifiactionCbf_t Copy_SetCbf);


#endif
