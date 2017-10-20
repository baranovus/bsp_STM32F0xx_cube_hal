
#include <stdlib.h>
#include <string.h>

#include "drv_layer\uart.h"






/********************************************************************
 * Description  :This routine  intializes the uart for Cresnet      *
 *                                                                  *
 * Parameters   :UART channel, Transmit int func, Receive int func  *
 *                                                                  *
 * Return Value :none                                               *
 *******************************************************************/
void uart_InitForCresnet( UART_CHANNEL channel, void (*pTxFunc)(void), void (*pRxFunc)( UINT32 Status, UINT32 Data ))
{

}

void uart_InitForI2DP( UART_CHANNEL channel, void (*pTxFunc)(void), void (*pRxFunc)( UINT32 Status, UINT32 Data ))
{


}

/********************************************************************
 * Description  :This routine  intializes the uart baud rate, parity*
 *               break etc control bits...                          *
 *                                                                  *
 * Parameters   :UART channel, Baud Rate, Flags, Transmit int func, *
 *               Receive int func                                   *
 *                                                                  *
 * Return Value :none
 *******************************************************************/
void uart_Init232( UART_CHANNEL channel, UINT32 Baudrate, UINT32 Bits, UPARITY Parity, UINT32 Stop_bits,
                   void (*pTxFunc)(void), void (*pRxFunc)( UINT32 Status, UINT32 Data ))
{

}

/********************************************************************
 *******************************************************************/
void uart_SetBaudrate( UART_CHANNEL channel, UINT32 Baudrate )
{
 
}


/********************************************************************
 *******************************************************************/
//Sets the baudrate - use when PCLK1_Frequency = 36Mhz
void uart_SetBaudrate_Alt( UART_CHANNEL channel, UINT32 Baudrate )
{
 

}

/********************************************************************
 *******************************************************************/
void uart_SendChar( UART_CHANNEL channel, UINT16 data )
{
 
}

/********************************************************************
 * Description  :Generic UART interrupt.                            *
 *                                                                  *
 * Parameters   :USART_TypeDef *USARTx                              *
 *                                                                  *
 * Return Value :None                                               *
 *******************************************************************/
void uart_Interrupt( UART_CHANNEL channel )
{
 
}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
static void uart1_Interrupt( void )
{
 
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
static void uart2_Interrupt( void )
{
 
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
static void uart3_Interrupt( void )
{
 
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
static void uart4_Interrupt( void )
{
  
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
static void uart5_Interrupt( void )
{
    
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
int uart_Flush( UART_CHANNEL channel )
{
 

    return 0;
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// transmitter interrupt control for Transmission Complete
void uart_TxIntControl( UART_CHANNEL channel, BOOL enable )
{
 
}

// Read Status of Transmitter interrupt Enable Flag for Transmission Complete
BOOL uart_IsTxIntEnabled( UART_CHANNEL channel )
{
 
}



//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// receiver interrupt control
void uart_RxIntControl( UART_CHANNEL channel, BOOL enable )
{

}

BOOL uart_IsRxIntEnabled( UART_CHANNEL channel )
{
 
}


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// break control
void uart_BreakControl( UART_CHANNEL channel, BOOL enable )
{
  
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// transmit enable control
void uart_TransmitControl( UART_CHANNEL channel, BOOL enable )
{
 
}
/************************************************************************/
UINT16 uart_Control( UART_CHANNEL channel )
{

}

/********************************************************************
 * Description  :This routine  intializes the uart baud rate, parity*
 *               break etc control bits...                          *
 *                                                                  *
 * Parameters   :UART channel, Baud Rate, Flags, Transmit int func, *
 *               Receive int func                                   *
 *                                                                  *
 * Return Value :none
 *******************************************************************/
void uart_InitBasic( UART_CHANNEL channel,void (*pTxFunc)(void), void (*pRxFunc)( UINT32 Status, UINT32 Data ))
{
 
}


/********************************************************************
 * Description  :This routine  intializes the uart baud rate, parity*
 *               break etc control bits...                          *
 *                                                                  *
 * Parameters   :UART channel, Baud Rate, Flags, Transmit int func, *
 *               Receive int func                                   *
 *                                                                  *
 * Return Value :none
 *******************************************************************/
void uart_InitTranscvInfinetEX( UART_CHANNEL channel, void (*pTxFunc)(void), void (*pRxFunc)( UINT32 Status, UINT32 Data ))
{

}





