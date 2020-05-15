/*******************************************************************************
 **  FILENAME     : LCD.c         			                                  **
 **  VERSION      : 1.0                                                        **
 **  DATE         : 23 Mar 2020                                                **                                                                         **
 **  PLATFORM     : STM		                                                  **
 **  AUTHOR       : Nada Mohamed                                               **
 *******************************************************************************/

/************************* Include header Files ********************/
#include "STD_TYPES.h"
#include "GPIO.h"
#include "LCD.h"
#include "LCD_cfg.h"
#include "sched_interface.h"

static APPNotifiactionCbf_t     AppNotifiactionCbf;



/*********************** LCD State ******************************/
#define LCD_STATE                    u8
#define LCD_DISPLAY_CLEAR           (LCD_STATE)0
#define LCD_DISPLAY_FUNCTION_SET    (LCD_STATE)1
#define LCD_ONOFF_Control           (LCD_STATE)2

/********************** LCD Process ****************************/
#define LCD_PROCESS                u8
#define LCD_IDLE_PROCESS           (LCD_PROCESS)0
#define LCD_WRITE_PROCESS          (LCD_PROCESS)1
#define LCD_CLEAR_PROCESS          (LCD_PROCESS)2
#define LCD_MOVE_CURSOR_PROCESS    (LCD_PROCESS)3

/**************************************** Command **********************/
#define CLCD_LINE1_COL1_CMD        0x80
#define CLCD_LINE2_COL1_CMD        0xC0

/************************ Global Variable *************************/
static u8 LCD_gComplete_InitProcess;
static u8 LCD_gData[255];
static u8 LCD_gDataLength;
static u8 LCD_gLineNumber;
static u8 LCD_gColumnNumber;



static LCD_PROCESS LCD_CurrentProcess =LCD_IDLE_PROCESS;
/*********************** Private Functions ***********************/
static void LCD_InitProcess(void);
static void LCD_WriteProcess(void);
static void LCD_ClearProcess(void);
static void LCD_MoveCursorProcess(void);
static void LCD_Task(void);

extern GPIO_t* LCD_u32GetLcdConfiguration();

static u64 LCD_RemapGPIO_Value(u8 value);


/* scheduler object, defined by:
 * runnable function,
 * period (ms) */
SCHED_task_t const task_lcd = {
	.runnable = &LCD_Task,
	.periodicTimeMs = 2,
};


/*******************************************************
 * Description    :- Initialize LCD pins
 * Return Type    :- void
 * Input Argument :- void
 *******************************************************/
void LCD_voidInit(void)
{
	u8 Local_u8Index;

	/****************** Configure LCD pins */
	GPIO_t* GPIO_ConfigurationLCD =LCD_u32GetLcdConfiguration();

	for(Local_u8Index=0;Local_u8Index<LCD_CONFIGPIN;Local_u8Index++)
	{
		GPIO_InitPin(&GPIO_ConfigurationLCD[Local_u8Index]);

	}

}


/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
/* Every 2 ms */
static void LCD_Task(void)
{
	if(LCD_gComplete_InitProcess == 1)
	{
		switch(LCD_CurrentProcess)
		{
		case LCD_IDLE_PROCESS :

			break;
		case LCD_WRITE_PROCESS :
			LCD_WriteProcess();
			break;
		case LCD_CLEAR_PROCESS :
			LCD_ClearProcess();
			break;
		case LCD_MOVE_CURSOR_PROCESS :
			LCD_MoveCursorProcess();
			break;
		}
	}
	else
	{
		LCD_InitProcess();
	}
}

/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
static void LCD_InitProcess(void)
{
	static LCD_STATE Local_CurrentState = LCD_DISPLAY_CLEAR;
	GPIO_t* GPIO_ConfigurationLCD =LCD_u32GetLcdConfiguration();

	switch(Local_CurrentState)
	{
	case LCD_DISPLAY_CLEAR :
		if(GPIO_ReadPin(&GPIO_ConfigurationLCD[LCD_E_PIN]))
		{
			Local_CurrentState = LCD_DISPLAY_FUNCTION_SET;

			/* E=0 Disable to Enable pin*/
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_LOW );
		}
		else
		{
			/* RS =0  command */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RS_PIN], GPIO_PIN_ALL_VALUE_LOW );

			/* RW =0  write to lcd */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RW_PIN], GPIO_PIN_ALL_VALUE_LOW );

			/* Write command in lcd */
			GPIO_WritePin(&GPIO_ConfigurationLCD[LCD_D_PIN], LCD_RemapGPIO_Value(LCD_CLEAR_SCREEN));

			/* E=1 to Enable pin*/
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_HIGH );
		}
	break;

	case LCD_DISPLAY_FUNCTION_SET :
		if(GPIO_ReadPin(&GPIO_ConfigurationLCD[LCD_E_PIN]))
		{
			Local_CurrentState = LCD_ONOFF_Control;

			/* E=0 Disable to Enable pin*/
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_LOW );
		}
		else
		{
			/* RS =0  command */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RS_PIN], GPIO_PIN_ALL_VALUE_LOW );

			/* RW =0  write to lcd */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RW_PIN], GPIO_PIN_ALL_VALUE_LOW );

			/* Write command in lcd */
			GPIO_WritePin(&GPIO_ConfigurationLCD[LCD_D_PIN], LCD_RemapGPIO_Value(LCD_FUNCTION_SET));

			/* E=1 to Enable pin*/
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_HIGH );
		}
	break;

	case LCD_ONOFF_Control :
		if(GPIO_ReadPin(&GPIO_ConfigurationLCD[LCD_E_PIN]))
		{
			LCD_gComplete_InitProcess = 1;
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_LOW );
		}
		else
		{
			/* RS =0  command */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RS_PIN], GPIO_PIN_ALL_VALUE_LOW );

			/* RW =0  write to lcd */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RW_PIN], GPIO_PIN_ALL_VALUE_LOW );

			/* Write command in lcd */
			GPIO_WritePin(&GPIO_ConfigurationLCD[LCD_D_PIN], LCD_RemapGPIO_Value(LCD_DISPLAY_CURSOR));

			/* E=1 to Enable pin*/
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_HIGH );
		}
	break;
	}
}

/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
static void LCD_WriteProcess(void)
{
	static u8 Local_CurrentChar=0;
	GPIO_t* GPIO_ConfigurationLCD =LCD_u32GetLcdConfiguration();

	if(GPIO_ReadPin(&GPIO_ConfigurationLCD[LCD_E_PIN]))
	{
		/* E=0 Disable to Enable pin*/
		GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_LOW );
	}
	else
	{
		if(LCD_gDataLength == Local_CurrentChar)
		{
			Local_CurrentChar =0;
			LCD_CurrentProcess =LCD_IDLE_PROCESS;
			AppNotifiactionCbf();   //Set App Call back function
		}
		else
		{
			/* RS =1  data */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RS_PIN], GPIO_PIN_ALL_VALUE_HIGH );

			/* RW =0  write to lcd */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RW_PIN], GPIO_PIN_ALL_VALUE_LOW );

			/* Write data in lcd */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_D_PIN], LCD_RemapGPIO_Value(LCD_gData[Local_CurrentChar]) );

			/* E=1 to Enable pin*/
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_HIGH );

			Local_CurrentChar++;
		}
	}
}

/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
Std_ReturnType LCD_WriteString(const u8* Copy_ptStringData ,u16 Copy_u16StringLength)
{
	u8 Local_u8Index;
	Std_ReturnType Std_LcdState = E_OK;

	if( Copy_ptStringData == NULL)
	{
		Std_LcdState = E_NOT_OK;
	}
	else
	{
		if(LCD_CurrentProcess ==LCD_IDLE_PROCESS)
		{
			LCD_CurrentProcess =LCD_WRITE_PROCESS;
			for(Local_u8Index=0 ; Local_u8Index < Copy_u16StringLength ; Local_u8Index++)
			{
				LCD_gData[Local_u8Index] =  Copy_ptStringData[Local_u8Index];
			}
			LCD_gDataLength=Copy_u16StringLength;

		}
		else
		{
			Std_LcdState = E_BUSY;
		}
	}
	return Std_LcdState;
}

/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
static void LCD_ClearProcess(void)
{
	GPIO_t* GPIO_ConfigurationLCD =LCD_u32GetLcdConfiguration();

	/* Write command in lcd */
	//GPIO_voidWritePort(LCD_CLEAR_SCREEN,&GPIO_ConfigurationLCD[LCD_D_PIN]);
	//LCD_CurrentProcess =LCD_IDLE_PROCESS;
	//AppNotifiactionCbf();   //Set App Call back function
	if(GPIO_ReadPin(&GPIO_ConfigurationLCD[LCD_E_PIN]))
	{
		LCD_CurrentProcess =LCD_IDLE_PROCESS;
		/* E=0 Disable to Enable pin*/
		GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_LOW );
		AppNotifiactionCbf();
	}
	else
	{
		/* RS =0  command */
		GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RS_PIN], GPIO_PIN_ALL_VALUE_LOW );

		/* RW =0  write to lcd */
		GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RW_PIN], GPIO_PIN_ALL_VALUE_LOW );

		/* Write command in lcd */
		GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_D_PIN], LCD_RemapGPIO_Value(LCD_CLEAR_SCREEN) );

		/* E=1 to Enable pin*/
		GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_HIGH );
	}

}

/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
Std_ReturnType LCD_ClearScreen(void)
{
	Std_ReturnType Std_LcdState = E_OK;

	if(LCD_CurrentProcess ==LCD_IDLE_PROCESS)
	{
		LCD_CurrentProcess =LCD_CLEAR_PROCESS;
	}
	else
	{
		Std_LcdState = E_BUSY;
	}

	return Std_LcdState;
}



/*****************************************/
static void LCD_MoveCursorProcess(void)
{
	GPIO_t* GPIO_ConfigurationLCD =LCD_u32GetLcdConfiguration();


	if(GPIO_ReadPin(&GPIO_ConfigurationLCD[LCD_E_PIN]))
	{
		LCD_CurrentProcess = LCD_IDLE_PROCESS;
		/* E=0 Disable to Enable pin*/
		GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_LOW );
		AppNotifiactionCbf();   //Set App Call back function
	}
	else
	{
		/* RS =0  command */
		GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RS_PIN], GPIO_PIN_ALL_VALUE_LOW );

		/* RW =0  write to lcd */
		GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_RW_PIN], GPIO_PIN_ALL_VALUE_LOW );

		if (LCD_gLineNumber == LCD_FIRST_LINE)
		{
			/* Write command in lcd */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_D_PIN], LCD_RemapGPIO_Value(CLCD_LINE1_COL1_CMD + LCD_gColumnNumber) );
		}
		else if (LCD_gLineNumber == LCD_SECOND_LINE)
		{
			/* Write command in lcd */
			GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_D_PIN], LCD_RemapGPIO_Value(CLCD_LINE2_COL1_CMD + LCD_gColumnNumber) );
		}
		else
		{

		}

		/* E=1 to Enable pin*/
		GPIO_WritePin( &GPIO_ConfigurationLCD[LCD_E_PIN], GPIO_PIN_ALL_VALUE_HIGH );

	}
}

/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
Std_ReturnType LCD_GotoLocation(u8 Copy_LineNumber , u8 Copy_ColumnNumber)
{
	Std_ReturnType Std_LcdState = E_OK;

	if(LCD_CurrentProcess ==LCD_IDLE_PROCESS)
	{
		LCD_gLineNumber    = Copy_LineNumber;
		LCD_gColumnNumber  = Copy_ColumnNumber;
		LCD_CurrentProcess = LCD_MOVE_CURSOR_PROCESS;
	}
	else
	{
		Std_LcdState = E_BUSY;
	}

	return Std_LcdState;
}


/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
Std_ReturnType LCD_SetCbf(APPNotifiactionCbf_t Copy_SetCbf)
{
	Std_ReturnType Local_u8Status=E_OK ;

	if(Copy_SetCbf==NULL)
	{
		Local_u8Status=E_NOT_OK;
	}
	else
	{
		AppNotifiactionCbf  = Copy_SetCbf;
	}

	return Local_u8Status;
}

/* remap values so that for example 0b101 -> 0xF0F */
static u64 LCD_RemapGPIO_Value(u8 value)
{
	u64 val = 0;
	u8 i;

	for (i = 0; i < 8; i++)
	{
		if (value & 1) /* if current bit is 1 */
		{
			/* set corresponding bit position to 0xF,
			 * corresponding bit position is i*4 (scaled by 4) */
			val |= (u64)0xF << (i << 2); /* i * 4 */
		}

		value >>= 1; /* discard LSB */
	}

	return val;
}
