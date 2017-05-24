#ifndef _HALT_H_
#define _HALT_H_

#include "stm8s.h"

#define WAKEUP_PORT GPIOD
#define WAKEUP_PIN_KEY GPIO_PIN_4
#define WAKEUP_PIN_POWER GPIO_PIN_6

//void Clk_Init(void);
//void Halt_OffDevice(void);
void JumpHalt(void);
#endif
