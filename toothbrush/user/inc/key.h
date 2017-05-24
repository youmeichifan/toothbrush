#ifndef _KEY_H_
#define _KEY_H_

#include "stm8s.h"

#define KEY_PORT GPIOD
#define KEY_PIN GPIO_PIN_4
#define CHARGE_CHECK_PORT GPIOD
#define CHARGE_CHECK_PIN GPIO_PIN_6

#define KEYUP 1
#define KEYDOWN 0

extern uint8_t KeyDownFlag;
void KeyScan(void);

#endif
