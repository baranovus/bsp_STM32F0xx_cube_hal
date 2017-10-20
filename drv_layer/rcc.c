#include <stdlib.h>
#include PROJECT_HEADER
#include "drv_layer\rcc.h"



unsigned long g_RCC_ResetStatus_CSR; //Global that holds the value of the RCC CSR Register, used on powerup




UINT32 rcc_GetHWResetFlags( void )
{
    UINT32 value;

    value = RCC->CSR; //store CSR into temp variable

//Change by DHROMIN on July 2013 - No longer reset the RCC register, only performed in app start, not bootloader.
//MOVED TO NEW FUNC BELOW:    RCC->CSR = ( value & RCC_CSR_LSION ) | RCC_CSR_RMVF;     // reset flags

    //Filter out via mask only the bits that are relevant
    value &= ( RCC_FLAG_SFTRST | RCC_FLAG_IWDGRST | RCC_FLAG_LPWRRST | RCC_FLAG_PINRST | RCC_FLAG_PORRST | RCC_FLAG_WWDGRST);

    return ( value ); //return the masked value, don't clear the CSR register
}

void rcc_ClearHWResetFlags( void )
{
    UINT32 value;

    value = RCC->CSR; //store CSR into local variable

    RCC->CSR = ( value & RCC_CSR_LSION ) | RCC_CSR_RMVF;     // reset flags
}

