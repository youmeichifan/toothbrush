#ifndef _TIM2_H_
#define _TIM2_H_

#include "stm8s.h"

void Tim2_Init(void);
void TimingDelay_Decrement(void);
void Delay_ms(__IO uint16_t nms);
#endif
