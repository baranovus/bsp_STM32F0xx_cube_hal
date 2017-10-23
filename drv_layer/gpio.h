
#ifndef _STM32DRIVER_GPIO_H
#define _STM32DRIVER_GPIO_H

typedef enum
{
    STM32_GPIOA = 0,
    STM32_GPIOB,
    STM32_GPIOC,
    STM32_GPIOD,
    STM32_GPIOF,
}
GPIO_PORT;

void gpio_ResetPorts( void );
void gpio_ResetPort( GPIO_PORT port );
void gpio_EnablePort( GPIO_PORT port );
void gpio_InitPin( GPIO_PORT port, unsigned short pin_list, unsigned long pin_mode, BOOL value );
void gpio_SetPin( GPIO_PORT port, unsigned short pin_list, BOOL value );
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
BOOL gpio_PinState( GPIO_PORT port, unsigned short pin_mask );
unsigned long gpio_PortState( GPIO_PORT port );
void void gpio_InitStartupStatusofPort(GPIO_PORT port, UINT32 MODER, UINT16 data)

extern void externalLine0_interrupt(void);
extern void externalLine1_interrupt(void);


// Input pin modes
//
#define INPUT_PIN_ANALOG    ((unsigned long)0x00)
#define INPUT_PIN_FLOATING  ((unsigned long)0x04)
#define INPUT_PIN_PULLED    ((unsigned long)0x08)

// General purpose output pin modes
//
#define OUT_PIN_PUSH_PULL   ((unsigned long)0x01)
#define SLOW_PIN_PUSH_PULL  ((unsigned long)0x02)
#define FAST_PIN_PUSH_PULL  ((unsigned long)0x03)

#define OUT_PIN_OPEN_DRAIN  ((unsigned long)0x05)
#define SLOW_PIN_OPEN_DRAIN ((unsigned long)0x06)
#define FAST_PIN_OPEN_DRAIN ((unsigned long)0x07)

// Alternate function output pin modes
//
#define OUT_AFP_PUSH_PULL   ((unsigned long)0x09)
#define SLOW_AFP_PUSH_PULL  ((unsigned long)0x0a)
#define FAST_AFP_PUSH_PULL  ((unsigned long)0x0b)

#define OUT_AFP_OPEN_DRAIN  ((unsigned long)0x0d)
#define SLOW_AFP_OPEN_DRAIN ((unsigned long)0x0e)
#define FAST_AFP_OPEN_DRAIN ((unsigned long)0x0f)


#define BIT0    0x00000001
#define BIT1    0x00000002
#define BIT2    0x00000004
#define BIT3    0x00000008
#define BIT4    0x00000010
#define BIT5    0x00000020
#define BIT6    0x00000040
#define BIT7    0x00000080
#define BIT8    0x00000100
#define BIT9    0x00000200
#define BIT10   0x00000400
#define BIT11   0x00000800
#define BIT12   0x00001000
#define BIT13   0x00002000
#define BIT14   0x00004000
#define BIT15   0x00008000
#define BIT16   0x00010000
#define BIT17   0x00020000
#define BIT18   0x00040000
#define BIT19   0x00080000
#define BIT20   0x00100000
#define BIT21   0x00200000
#define BIT22   0x00400000
#define BIT23   0x00800000
#define BIT24   0x01000000
#define BIT25   0x02000000
#define BIT26   0x04000000
#define BIT27   0x08000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000

#endif
