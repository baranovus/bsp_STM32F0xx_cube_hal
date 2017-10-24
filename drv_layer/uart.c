
#include <stdlib.h>
#include <string.h>
#include "inc\stm32f0xx_hal.h"
#include "drv_layer\uart.h"

// Gloabl handles Added for use with the HAL library.
// Instances are initialized so you can use HAL library macros easily.
// If you use the handles with the HAL library they will retain
// the initialization info, peripheral state, and any errors.
//
// Make sure these structs and function are set up correctly!


typedef struct
{
    void    (*pTxFunc)( void );
    void    (*pRxFunc)( UINT32 Status, UINT32 Data );
}
UART_CB;
UART_CB uart_cb[DEVICE_MAXNUM_UART];

void (*pTxCallback)(void) = NULL;
void (*pRxCallback)(void)( UINT32 Status, UINT32 Data ) = NULL;

UART_HandleTypeDef* GetUartHandleFromInst(UINT32 inst)
{
    static UART_HandleTypeDef UartHandles[6] = {
        { .Instance = USART1 },
        { .Instance = USART2 },
        { .Instance = USART3 },
        { .Instance = USART4 },
        { .Instance = USART5 },
        { .Instance = USART6 }
    };
    return &(UartHandles[inst]);
}




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
	UART_HandleTypeDef* uartHandle = GetUartHandleFromInst(channel);
	if(uartHandle == NULL || uartHandle->Instance == NULL)
        return;
	UART_CB *pUart = &uart_cb[channel];
	switch(channel)
	{
		case STM32_UART1:
			__HAL_RCC_USART1_CLK_ENABLE();
			__HAL_RCC_USART1_FORCE_RESET();
			__HAL_RCC_USART1_RELEASE_RESET();
			break;
		case STM32_UART2:
			__HAL_RCC_USART2_CLK_ENABLE();
			__HAL_RCC_USART2_FORCE_RESET();
			__HAL_RCC_USART2_RELEASE_RESET();
			break;
		case STM32_UART3:
			__HAL_RCC_USART3_CLK_ENABLE();
			__HAL_RCC_USART3_FORCE_RESET();
			__HAL_RCC_USART3_RELEASE_RESET();
			break;
		case STM32_UART4:
			__HAL_RCC_USART4_CLK_ENABLE();
			__HAL_RCC_USART4_FORCE_RESET();
			__HAL_RCC_USART4_RELEASE_RESET();
			break;
		case STM32_UART5:
			__HAL_RCC_USART5_CLK_ENABLE();
			__HAL_RCC_USART5_FORCE_RESET();
			__HAL_RCC_USART5_RELEASE_RESET();
			break;
		case STM32_UART6:
			__HAL_RCC_USART6_CLK_ENABLE();
			__HAL_RCC_USART6_FORCE_RESET();
			__HAL_RCC_USART6_RELEASE_RESET();
			break;			
	}

	switch(Stop_bits)
    {
    default:
    case 1:
        uartHandle->Init.StopBits = UART_STOPBITS_1;
        break;
    case 2:
        uartHandle->Init.StopBits = UART_STOPBITS_2;
        break;
    }
	switch(Parity)
    {
    case PARITY_NONE:
    default:
        uartHandle->Init.Parity = UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        uartHandle->Init.Parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        uartHandle->Init.Parity = UART_PARITY_EVEN;
        break;
    }
    switch(Bits)
    {
    case 7:
        uartHandle->Init.WordLength = UART_WORDLENGTH_8B;

        // If parity isn't used, we have to change the stop bits to fool the
        // hardware into thinking the msb bit is the stop bit
        if(parity == PARITY_NONE)
        {
          if(Stop_bits == 2)
		  {
            uartHandle->Init.StopBits = USART_STOPBITS_1;
		  }
          else{
            uartHandle->Init.StopBits = USART_STOPBITS_0_5;
		  }
        }
        break;
    default:
    case 8:
        // Data bits include parity bit
        if(parity == PARITY_NONE)
          uartHandle->Init.WordLength = UART_WORDLENGTH_8B;
        else
          uartHandle->Init.WordLength = UART_WORDLENGTH_9B;
        break;
    case 9:
        // 9 data bits not supported by software
        uartHandle->Init.WordLength = UART_WORDLENGTH_9B;
         break;
    }	
	HAL_UART_DeInit(uartHandle);
    uartHandle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uartHandle->Init.BaudRate = Baudrate;
    uartHandle->Init.Mode = UART_MODE_TX_RX;
    uartHandle->Init.OverSampling = 0;
	uartHandle->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT; 
    HAL_UART_Init(uartHandle);
    pUart->pTxFunc  = pTxFunc;
    pUart->pRxFunc  = pRxFunc;

    __HAL_UART_DISABLE_IT(uartHandle, UART_IT_TXE);
    __HAL_UART_DISABLE_IT(uartHandle, UART_IT_TC);
    __HAL_UART_DISABLE_IT(uartHandle, UART_IT_RXNE);

    //clear the flags just in the uart was being used previously
    __HAL_UART_CLEAR_FLAG(uartHandle, UART_FLAG_TXE);
    __HAL_UART_CLEAR_FLAG(uartHandle, UART_FLAG_RXNE);
}

/********************************************************************
 *******************************************************************/
void uart_SetBaudrate( UART_CHANNEL channel, UINT32 Baudrate )
{
	UART_HandleTypeDef* uartHandle = GetUartHandleFromInst(channel);
	uartHandle->Init.BaudRate = Baudrate;
	UART_SetConfig(uartHandle);	
}



/********************************************************************
 *******************************************************************/
void uart_SendChar( UART_CHANNEL channel, UINT16 data )
{
 	UART_HandleTypeDef* uartHandle = GetUartHandleFromInst(channel);
	if(uartHandle->Init.WordLength == UART_WORDLENGTH_9B)
	{
		uartHandle->Instance->TDR = data &0x01FF;
	}
	else{
		uartHandle->Instance->TDR = data &0x0FF;
	}
}

/*******************************************************************************
* Function Name  : USART_IRQHandler
* Description    : UART interrupt handler for USART1 and USART2
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void uart_Interrupt(UART_CHANNEL channel)
{
	UART_HandleTypeDef* uartHandle = GetUartHandleFromInst(channel);
	if(uartHandle == NULL || uartHandle->Instance == NULL)    return; 
	UART_CB *pUart = &uart_cb[channel];
	pTxCallback = pUart->pTxFunc;
	pRxCallback = pUart->pRxFunc;
	HAL_UART_IRQHandler(&uartHandle); 
}

/*******************************************************************************
* Function Name  : USART_IRQHandler
* Description    : UART interrupt handler for USART3,4,5,6
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void uart_Interrupt_3_6(void)
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



void uart_InitTranscvInfinetEX( UART_CHANNEL channel, void (*pTxFunc)(void), void (*pRxFunc)( UINT32 Status, UINT32 Data ))
{

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(pTxCallback != NULL)
	{
		(pTxCallback)();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(pRxCallback != NULL)
	{
		UINT32 data  = (UINT32) READ_REG(huart->Instance->RDR);
		UINT32 state = (UINT32) huart->RxState;
		(pTxCallback)(state, data);
	}
}


