
#ifndef _STM32DRIVER_UART_H_
#define _STM32DRIVER_UART_H_



typedef enum
{
    PARITY_NONE,
    PARITY_0,
    PARITY_1,
    PARITY_ODD,
    PARITY_EVEN
}
UPARITY;

typedef enum
{
    STM32_UART1 = 0,
    STM32_UART2,
    STM32_UART3,
    STM32_UART4,
    STM32_UART5,
    DEVICE_MAXNUM_UART
}
UART_CHANNEL;

extern void uart_InitBasic( UART_CHANNEL channel, void (*pTxFunc)(void), void (*pRxFunc)( UINT32 Status, UINT32 Data ));
extern void uart_InitForCresnet( UART_CHANNEL channel, void (*pTxFunc)(void), void (*pRxFunc)( UINT32 Status, UINT32 Data ));
extern void uart_InitForI2DP( UART_CHANNEL channel, void (*pTxFunc)(void), void (*pRxFunc)( UINT32 Status, UINT32 Data ));
void uart_Init232( UART_CHANNEL channel, UINT32 Baudrate, UINT32 Bits, UPARITY Parity, UINT32 Stop_bits,
                   void (*pTxFunc)(void), void (*pRxFunc)( UINT32 Status, UINT32 Data ));
void uart_SetBaudrate( UART_CHANNEL channel, UINT32 Baudrate );
void uart_SetBaudrate_Alt( UART_CHANNEL channel, UINT32 Baudrate );
void uart_SendChar( UART_CHANNEL channel, UINT16 data );
int  uart_Flush( UART_CHANNEL channel );

BOOL uart_IsTxIntEnabled( UART_CHANNEL channel );
BOOL uart_IsRxIntEnabled( UART_CHANNEL channel );
void uart_TxIntControl( UART_CHANNEL channel, BOOL enable );/*Transmission complete interrupt enable*/
void uart_RxIntControl( UART_CHANNEL channel, BOOL enable );
void uart_LsIntControl( UART_CHANNEL channel, BOOL enable );
void uart_MsIntControl( UART_CHANNEL channel, BOOL enable );
void uart_BreakControl( UART_CHANNEL channel, BOOL enable );
void uart_TransmitControl( UART_CHANNEL channel, BOOL enable );

UINT16 uart_Control( UART_CHANNEL channel );


extern void uart_Interrupt( UART_CHANNEL channel );
extern void uart_BSP_InitializeHardware(UART_CHANNEL channel);
extern void uart1_BSP_Interrupt(void);


#endif

