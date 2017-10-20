

#include <stdlib.h>
#include <string.h>
#include PROJECT_HEADER
#include "drv_layer\flash.h"
//#include "drv_layer\timer.h"


#define ERASE_TIMEOUT   ((45000ul * FLASH_TIMER_FREQUENCY)/1000000ul) //Compute msec Timeout: (Timer Freq in Hz * number of 1 usecs / 1usec tick units)
#define PROGRAM_TIMEOUT ((1000  * FLASH_TIMER_FREQUENCY)/1000000) //Compute msec Timeout: (Timer Freq in Hz * number of 1 usecs / 1usec tick units)

//static UINT8 flash_ProgramWord( UINT32 Address, UINT32 Data );
//static BOOL flash_WaitStatusComplete( UINT32 timeout );


UINT32 flash_GetDeviceSize( void )
{
    return ( *(UINT16*)0x1FFFF7CC << 10 );
}
/*
#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F031x6) || defined(STM32F038xx) \
 || defined(STM32F051x8) || defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F058xx) || defined(STM32F070x6)
#define FLASH_PAGE_SIZE          0x400U
#endif /* STM32F030x6 || STM32F030x8 || STM32F031x6 || STM32F051x8 || STM32F042x6 || STM32F048xx || STM32F058xx || STM32F070x6 

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) \
 || defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
#define FLASH_PAGE_SIZE          0x800U
*/
UINT32 flash_GetSectorSize( void )
{
     return ( 4096 );
}



//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Program a sector. The device allows fractions of a sector to be written.
// dst  - the flash address to start writing at.
// src  - the address of the data buffer to be written.
// size - the number of bytes in the data buffer to write.
//


FLASH_Status flash_ProgramBlock( UINT32 dst, UINT32* src, UINT16 size )
{
    UINT16 i;
    FLASH_Status status = HAL_ERROR; //default to success unless error occurs, will set new status below

    if ( HAL_FLASH_Unlock() == HAL_ERROR)    // unlock flash if locked
	{
		return(FLASH_ERROR_PG)
	}

    size = ( size + 3 ) >> 2;           // convert to number of words

    for ( i = 0; i < size; i++ )
    {
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, dst, *src++ );
        if ( status != HAL_OK )
		{
            break;
		}	
        dst += 4;
    }
    HAL_FLASH_Loc();
	if(status == HAL_OK)
	{
		return(FLASH_COMPLETE)
	}
    else{
		return ( FLASH_ERROR_PG );
	}
	
}


FLASH_Status flash_ErasePage( UINT32 Page_Address ) /*this is a global access function*/
{	
 
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = Page_Address;
	EraseInitStruct.NbPages = 1;
	
	UINT32 PageError = 0;

	FLASH_Status status = FLASH_COMPLETE;

	/* Wait for last operation to be completed */
    if (FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT) == HAL_TIMEOUT)
	{
		status = FLASH_TIMEOUT ;
	}
	else if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK) 
	{
		status = FLASH_ERROR_PG;
	}
	return status;
}



FLASH_Status flash_ReadBlock(UINT32 address, UINT8* destRamBuffer, UINT16 DataBufferSize)
{
      // read a page
	 memcpy( destRamBuffer, (const void*)address, DataBufferSize);
	 return FLASH_COMPLETE;
}

#if 0

/* --------------   LOCAL FUNCTIONS ONLY ------------------*/
static UINT8 flash_ProgramWord( UINT32 Address, UINT32 Data )
{
    BOOL status;

    status = flash_WaitStatusComplete( 0 );

    if ( status == TRUE )
    {
        FLASH->CR |= FLASH_CR_PG;

        *(volatile UINT16*)Address = (UINT16)Data;      // write the first halfword

        status = flash_WaitStatusComplete( PROGRAM_TIMEOUT );

        if ( status == TRUE )
        {
            *(volatile UINT16*)( Address + 2 ) = Data >> 16;    // write the second halfword

            status = flash_WaitStatusComplete( PROGRAM_TIMEOUT );
        }

        FLASH->CR &= ~FLASH_CR_PG;
    }

	if(status == TRUE)
		return ( FLASH_SUCCESS );
	else
		return ( FLASH_ERROR );
}

static BOOL flash_WaitStatusComplete( UINT32 timeout )
{
    if ( timeout != 0 )
    {
        timer_OC_EventSetup( FLASH_TIMER_MODULE, FLASH_TIMER_CHANNEL, timeout, 0, NULL );

        while ( FLASH->SR & FLASH_SR_BSY )
        {
            if ( !timer_OC_EventIsRunning( FLASH_TIMER_MODULE, FLASH_TIMER_CHANNEL ))
                return FALSE;
        }
    }
	return (( FLASH->SR & ( FLASH_SR_PGERR | FLASH_SR_WRPRTERR )) == 0 );
}



#endif
