
#include <stdlib.h>
#include PROJECT_HEADER
#include "drv_layer\watchdog.h"
#include "inc\stm32f0xx.h"


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void wdg_InitWatchdog( UINT32 timeout_ms )
{
    UINT32 min_timeout_us = 100;         // 0.1 ms for the fastest prescale rate
    UINT32 max_timeout_us = 409600;      // for the reload value of 0x0fff at this prescale
    UINT32 timeout = timeout_ms * 1000;  // in microseconds
    UINT32 i;

    /* Added on: 2/23/2012 */
    /* Enable this bit to allow debugging a release build later on (via attaching to JTAG and using matching src code map) */
    DBGMCU->CR |= ((UINT32)0x00000100);

    for ( i = 0; i < 7; i++ )                   // that's as far as this hardware allows
    {
        if ( max_timeout_us > timeout )
        {
            break;
        }
        min_timeout_us <<= 1;
        max_timeout_us <<= 1;
    }

    IWDG->KR = 0x5555;          // Enable write access to IWDG_PR and IWDG_RLR registers
    IWDG->PR = i;               // Preload value 0..7

    if ( max_timeout_us > timeout )
    {
        timeout /= min_timeout_us;
        if ( timeout > 0x0fff )
            timeout = 0x0fff;
    }
    else
    {
        timeout = 0x0fff;
    }

    IWDG->RLR = timeout;        // set the reload value
    IWDG->KR = 0xaaaa;          // reload the counter
    IWDG->KR = 0xcccc;          // enable the counter
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void wdg_ResetWatchdog( void )
{
    IWDG->KR = 0xaaaa;          // reload the counter
}


