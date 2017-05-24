#ifndef _EEPROM_H_
#define _EEPROM_H_

/* ����ϵͳͷ�ļ� */

/* �����Զ���ͷ�ļ� */
#include "stm8s.h"

#define FLASHDATA_ADDR (0x4000)

#define FISTSTART_FLAG 0x00
#define WORKWAKEUP_FLAG 0xAA
#define CHARGEWAKEUP_FLAG 0x55

void FlashErase(void);
void FlashWriteByte(uint32_t addr,uint8_t byte);

#endif

