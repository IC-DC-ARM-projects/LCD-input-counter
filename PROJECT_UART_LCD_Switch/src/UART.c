
#include "STD_TYPES.h"
#include "UART.h"
#include "UART_cfg.h"

/************************** Register **************/
typedef struct
{
	u32 SR  ;
	u32 DR  ;
	u32 BRR ;
	u32 CR1 ;
	u32 CR2 ;
	u32 CR3 ;
	u32 GTPR;
}UART_Reg;


#define  UART5                ((void*)BASE_ADDRESS_UART5)
#define  UART4                ((void*)BASE_ADDRESS_UART4)
#define  USART3               ((void*)BASE_ADDRESS_USART3)
#define  USART2               ((void*)BASE_ADDRESS_USART2)
#define  USART1               ((void*)BASE_ADDRESS_USART1)

#define USART1_IRQNUMBER   37U
#define USART2_IRQNUMBER   38U
#define USART3_IRQNUMBER   39U
#define UART4_IRQNUMBER    52U
#define UART5_IRQNUMBER    53U
volatile UART_Reg* const UART_Peripherals[]={USART1,USART2,USART3,UART4,UART5};

/*************************** Call back function ************/
//static APPRxNotifiactionCbf_t     AppRXNotifiactionCbf ;
//static APPTxNotifiactionCbf_t     AppTXNotifiactionCbf ;
static void(*APPTxNotifiactionCbf_t)(void);
static void(*APPRxNotifiactionCbf_t)(void);
/*************************** Global Variable ***************/
static volatile UART_Reg*            UARTX_g;
static volatile UART_DATABUFFER_t    UART_TXBuffer ;
static volatile UART_DATABUFFER_t    UART_RXBuffer ;

/* private function */
static void IRQ_Handler(UART_Reg* UARTX);


/********************************** Macros *****************/
#define UART_MAX_DATALENGTH        511U

/************************* ******* STATE **************************/
#define UART_STATE_IDLE           (u8)0
#define UART_STATE_BUSY           (u8)1


/********************************** Masks *****************/
#define UART_STOP_BIT_MASK        (u32)0xffffcfff
#define UART_UE_BIT_MASK          (u32)0xffffdfff
#define UART_M_MASK               (u32)0xffffefff
#define UART_PCE_PS_MASK          (u32)0xfffff9ff

#define UART_SR_TXE               (u32)0x80
#define UART_SR_TXE_MASK          (u32)0xffffff7f

#define UART_SR_TC               (u32)0x40
#define UART_SR_TC_MASK          (u32)0xffffffbf

#define UART_SR_RXNE              (u32)0x20
#define UART_SR_RXNE_MASK         (u32)0xffffffdf

#define UART_CR1_RE_TE_MASK       (u32)0xfffffff3

#define UART_BRR_DIVFRACTION      (u32)0x0000000f
#define UART_BRR_DIVMANTISSA      (u32)0x0000fff0


#define UART_CR1_RXNEIE_MASK      (u32)0xffffffdf
#define UART_CR1_RXNEIE           (u32)0x20

#define UART_CR1_TXEIE_MASK      (u32)0xffffff7f
#define UART_CR1_TXEIE           (u32)0x80

#define UART_CR1_TCIE_MASK      (u32)0xffffffbf
#define UART_CR1_TCIE           (u32)0x40

UART_CONFIG_t* UART_Configuration_func ();

/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)

 ********************************************************************************/
extern void UART_Init(void)
{
	u32 Local_u32Temp =0 ;
	f64 Local_f64BaudrateCounter ;
	u8  Local_u8BaudrateMantissa ;
	f32 Local_f32BaudrateFraction ;

	UART_CONFIG_t* UART_Configuration = UART_Configuration_func ();


	for(u8 Copy_index =0 ;Copy_index <UART_COUNT;Copy_index++)
	{

		UARTX_g = UART_Peripherals[UART_Configuration[Copy_index].UART_Peripheral] ;

		/* Default Data Configuration */
		UART_TXBuffer.UART_DATABuffer = NULL;
		UART_TXBuffer.UART_DataIndex  = 0   ;
		UART_TXBuffer.UART_DataLength = 0   ;
		UART_TXBuffer.UART_State      =  UART_STATE_IDLE ;

		UART_RXBuffer.UART_DATABuffer = NULL;
		UART_RXBuffer.UART_DataIndex  = 0   ;
		UART_RXBuffer.UART_DataLength = 0   ;
		UART_RXBuffer.UART_State      =  UART_STATE_IDLE ;

		/* Enable UART */
		UARTX_g->CR1 &= UART_UE_BIT_MASK ;
		UARTX_g->CR1 |= UART_ENABLE_BIT  ;

		/* enable TX & RX */
		UARTX_g->CR1 &= UART_CR1_RE_TE_MASK ;
		UARTX_g->CR1 |= UART_Configuration[Copy_index].UART_TX_RX_Mode ;

		/* word Length */
		UARTX_g->CR1 &= UART_M_MASK ;
		UARTX_g->CR1 |= UART_Configuration[Copy_index].UART_DataLength;

		/* Parity Selection */
		UARTX_g->CR1 &= UART_PCE_PS_MASK;
		UARTX_g->CR1 |= UART_Configuration[Copy_index].UART_Parity ;

		/* Stop Bit */
		UARTX_g->CR2 &= UART_STOP_BIT_MASK ;
		UARTX_g->CR2 |= UART_Configuration[Copy_index].UART_StopBits ;

		/* Baud Rate counter
	          Tx/ Rx baud =fCK /(16*USARTDIV)
	         USARTDIV = fck / (16 *baud) */

		Local_f64BaudrateCounter   = (UART_FREQUENCY /( UART_Configuration[Copy_index].UART_Buadrate * 16 )) ;
		Local_u8BaudrateMantissa   = Local_f64BaudrateCounter ;
		Local_f32BaudrateFraction  = Local_f64BaudrateCounter - (u32)Local_u8BaudrateMantissa ;
		Local_f32BaudrateFraction  = Local_f32BaudrateFraction *16 ;

		Local_u32Temp = UARTX_g->BRR ;
		Local_u32Temp |= ((Local_u8BaudrateMantissa<<4) & UART_BRR_DIVMANTISSA) | ((u32)Local_f32BaudrateFraction & UART_BRR_DIVFRACTION) ;
		UARTX_g->BRR   = Local_u32Temp;

		/* Enable interrupt */
		UARTX_g->CR1 &= UART_CR1_RXNEIE_MASK;
		UARTX_g->CR1 |= UART_CR1_RXNEIE;    // UART Receive Interrupt Enable.

		UARTX_g->CR1 &= UART_CR1_TCIE_MASK;
		UARTX_g->CR1 |= UART_CR1_TCIE;      // UART transmit Interrupt Enable.
	}



}


static void IRQ_Handler(UART_Reg* UARTX)
{
	u32 Local_u32Temp=0;

		/*  Transmit data is sent. */
		if( UARTX->SR  & UART_SR_TC )
		{
			/* CLEAR TC */
			Local_u32Temp =  UARTX->SR          ;
			Local_u32Temp &= UART_SR_TC_MASK ;
			UARTX->SR   =  Local_u32Temp     ;

			/* Transmission is not complete */
			if(UART_TXBuffer.UART_DataLength != UART_TXBuffer.UART_DataIndex)
			{
				UARTX->DR = UART_TXBuffer.UART_DATABuffer[UART_TXBuffer.UART_DataIndex];
				UART_TXBuffer.UART_DataIndex++ ;
			}
			else // Transmission is complete (buffer is finished)
			{
				UART_TXBuffer.UART_DATABuffer = NULL;
				UART_TXBuffer.UART_DataIndex  = 0   ;
				UART_TXBuffer.UART_DataLength = 0   ;
				UART_TXBuffer.UART_State      =  UART_STATE_IDLE ;
				//AppTXNotifiactionCbf();
				APPTxNotifiactionCbf_t();
			}
		}

		/*  Received data is ready to be read. */
		if( UARTX->SR  & UART_SR_RXNE )
		{
			/* CLEAR RXNE */
			Local_u32Temp =  UARTX->SR       ;
			Local_u32Temp &= UART_SR_RXNE_MASK ;
			UARTX->SR   =  Local_u32Temp     ;

			if( UART_RXBuffer.UART_State == UART_STATE_BUSY )
			{
				UART_RXBuffer.UART_DATABuffer[ UART_RXBuffer.UART_DataIndex] = UARTX->DR ;
				UART_RXBuffer.UART_DataIndex++;
				if( UART_RXBuffer.UART_DataIndex ==  UART_RXBuffer.UART_DataLength)
				{
					UART_RXBuffer.UART_DATABuffer = NULL;
					UART_RXBuffer.UART_DataIndex  = 0   ;
					UART_RXBuffer.UART_DataLength = 0   ;
					UART_RXBuffer.UART_State      =  UART_STATE_IDLE ;
					APPRxNotifiactionCbf_t();
				}
			}
		}
		else
		{
			/* nothing */
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
void USART1_IRQHandler(void)
{
	IRQ_Handler(UART_Peripherals[0]);
}


void USART2_IRQHandler(void)
{
	IRQ_Handler(UART_Peripherals[1]);
}

void USART3_IRQHandler(void)
{
	IRQ_Handler(UART_Peripherals[2]);
}


void UART4_IRQHandler(void)
{
	IRQ_Handler(UART_Peripherals[3]);
}

void UART5_IRQHandler(void)
{
	IRQ_Handler(UART_Peripherals[4]);
}





/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)
              Copy_u8DataBuffer  : pointer to data buffer
              Copy_u16DataLength : Data buffer Length (Range From 0 to 511 )
              Copy_u8UARTPeripherail  ->
									UART5_Peripherial
									UART4_Peripherial
									USART3_Peripherial
									USART2_Peripherial
									USART1_Peripherial
 ********************************************************************************/
Std_ReturnType UART_SendData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength, u8 Copy_u8UARTPeripherail)
{
	Std_ReturnType Std_UartState = E_OK;
	UART_Reg* UARTX = UART_Peripherals[Copy_u8UARTPeripherail];

	if( Copy_u8DataBuffer == NULL)
	{
		Std_UartState = E_NOT_OK;
	}
	else
	{
		if( UART_TXBuffer.UART_State     ==  UART_STATE_IDLE )
		{
			UART_TXBuffer.UART_State = UART_STATE_BUSY;

			UART_TXBuffer.UART_DATABuffer = Copy_u8DataBuffer;
			UART_TXBuffer.UART_DataIndex  = 0;
			UART_TXBuffer.UART_DataLength = Copy_u16DataLength ;
			UARTX->DR                   = UART_TXBuffer.UART_DATABuffer[UART_TXBuffer.UART_DataIndex];
			UART_TXBuffer.UART_DataIndex ++;
		}
		else
		{
			Std_UartState = E_BUSY;
		}

	}
	return Std_UartState;
}

/******************************************************************************
 * Description  :
 *
 * ReturnType
 *   Std_ReturnType  (unsigned char)
			   E_OK     : Service request accepted .
			   E_NOT_OK : Service request not accepted .

    Parameter (In)
              Copy_u8DataBuffer  : pointer to data buffer
              Copy_u16DataLength : Data buffer Length (Range From 0 to 511 )
 ********************************************************************************/
Std_ReturnType UART_RecieveData(u8* Copy_u8DataBuffer,u16 Copy_u16DataLength)
{
	Std_ReturnType Std_UartState = E_OK;

	if( Copy_u8DataBuffer == NULL)
	{
		Std_UartState = E_NOT_OK;
	}
	else
	{
		if (UART_RXBuffer.UART_State ==  UART_STATE_IDLE )
		{
			UART_RXBuffer.UART_DATABuffer = Copy_u8DataBuffer;
			UART_RXBuffer.UART_DataIndex  = 0;
			UART_RXBuffer.UART_DataLength = Copy_u16DataLength ;
			UART_RXBuffer.UART_State =  UART_STATE_BUSY;
		}
		else
		{
			Std_UartState = E_BUSY;
		}
	}
	return Std_UartState;
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
Std_ReturnType UART_SetTransmissionCbf(void(*Copy_APPTxNotifiactionCbf)(void))//APPTxNotifiactionCbf_t TransmissionCbf)
{
	Std_ReturnType Local_u8Status=E_OK ;
	if(Copy_APPTxNotifiactionCbf ==NULL)
	{
		Local_u8Status=E_NOT_OK;
	}
	else
	{
		APPTxNotifiactionCbf_t = Copy_APPTxNotifiactionCbf;
	}
	return Local_u8Status;
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
Std_ReturnType UART_SetRecieverCbf(void(*Copy_APPRxNotifiactionCbf)(void))//APPRxNotifiactionCbf_t RecieverCbf)
{
	Std_ReturnType Local_u8Status=E_OK ;
	if(Copy_APPRxNotifiactionCbf ==NULL)
	{
		Local_u8Status=E_NOT_OK;
	}
	else
	{
		APPRxNotifiactionCbf_t = Copy_APPRxNotifiactionCbf;
	}
	return Local_u8Status;
}
