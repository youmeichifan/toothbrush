#include "eeprom.h"


/*
地址从 0x4000 开始
*/

void FlashErase(void)
{
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
  FLASH_EraseBlock(0, FLASH_MEMTYPE_DATA);/*往FLASH写数据前，要擦除对应的区域*/
  FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
}


void FlashWriteByte(uint32_t addr,uint8_t byte)
{
  
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET);/* 等待 Data EEPROM area 解锁标志位置位*/
  FLASH_ProgramByte(addr,byte);
  FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
  FLASH_Lock(FLASH_MEMTYPE_DATA);/*操作完要加锁*/
}