#include "eeprom.h"


/*
��ַ�� 0x4000 ��ʼ
*/

void FlashErase(void)
{
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
  FLASH_EraseBlock(0, FLASH_MEMTYPE_DATA);/*��FLASHд����ǰ��Ҫ������Ӧ������*/
  FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
}


void FlashWriteByte(uint32_t addr,uint8_t byte)
{
  
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET);/* �ȴ� Data EEPROM area ������־λ��λ*/
  FLASH_ProgramByte(addr,byte);
  FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
  FLASH_Lock(FLASH_MEMTYPE_DATA);/*������Ҫ����*/
}