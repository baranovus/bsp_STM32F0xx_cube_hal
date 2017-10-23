
#include <stdlib.h>
#include PROJECT_HEADER
#include "gpio.h"
#include "inc\stm32f0xx_hal.h"


static const GPIO_TypeDef* _GPIO_[] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOF };

static const UINT32 rcc_port_bit[] =
{
    RCC_AHBENR_GPIOAEN,
    RCC_AHBENR_GPIOBEN,
    RCC_AHBENR_GPIOCEN,
    RCC_AHBENR_GPIODEN,
    RCC_AHBENR_GPIOFEN,
};

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void gpio_ResetPort( GPIO_PORT port )				//turn clock enable OFF
{
    RCC->AHBENR  &= ~rcc_port_bit[port];
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void gpio_EnablePort( GPIO_PORT port )
{

    //Check if Port Clock is not enabled, then enable it. Otherwise do nothing.
    if (( RCC->AHBENR  & rcc_port_bit[port] ) == 0 )
    {
//NOTE: This was made atomic on Aug 22, 2013 to protect against this R-W-M operation.
ATOMIC(
        RCC->RCC->AHBENR |=  rcc_port_bit[port];
    );
    }

}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void gpio_ResetPorts( void )
{
    gpio_ResetPort( STM32_GPIOA );
    gpio_ResetPort( STM32_GPIOB );
    gpio_ResetPort( STM32_GPIOC );
    gpio_ResetPort( STM32_GPIOD );
    gpio_ResetPort( STM32_GPIOF );
}

void gpio_InitPin( GPIO_PORT port, unsigned short pin_list, unsigned long pin_mode, BOOL value )
{
		WARNING: Use "GPIO_Init" function for HAL-based projects
}

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    HAL_GPIO_Init(GPIOx, GPIO_InitStruct);
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void gpio_SetPin( GPIO_PORT port, UINT16 pin_list, BOOL value )
{
    GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)_GPIO_[port];

    if ( value )
        GPIOx->BSRR = pin_list;
    else
        GPIOx->BRR = pin_list;
}


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
BOOL gpio_PinState( GPIO_PORT port, UINT16 pin_mask )
{
    GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)_GPIO_[port];

    return (( GPIOx->IDR & pin_mask ) != 0 );
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
UINT32 gpio_PortState( GPIO_PORT port )
{
    GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)_GPIO_[port];

    return ( GPIOx->IDR );
}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void gpio_InitStartupStatusofPort(GPIO_PORT port, UINT32 MODER, UINT16 data)
{
	GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)_GPIO_[port];
	GPIOx->ODR = data; //set the pin states before configuring the pins
	GPIOx->MODER = MODER; //Load port configuration 
}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

