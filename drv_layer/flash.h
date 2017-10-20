
#ifndef _STM32DRIVER_FLASH_H_
#define _STM32DRIVER_FLASH_H_

#define MCU_FLASH_START   0x08000000



typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;

/* Extern Global Access Flash API Functions */
extern FLASH_Status flash_ProgramBlock( UINT32 dst, UINT32* src, UINT16 size );
extern FLASH_Status flash_ReadBlock(UINT32 address,UINT8* destRamBuffer, UINT16 DataBufferSize);
extern FLASH_Status flash_ErasePage( UINT32 Page_Address );

extern UINT32 flash_GetSectorSize( void );
extern UINT32 flash_GetDeviceSize( void );



/*
void flash_InitDriver( unsigned long user_flash_start );
void flash_CloseDriver( void );
BOOL flash_WriteByte( unsigned long addr, int byte );
*/


#endif

