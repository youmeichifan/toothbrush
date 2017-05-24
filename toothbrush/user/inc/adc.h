#ifndef __ADC_H_
#define __ADC_H_

/* 包含自定义头文件 */
#include "stm8s.h"

#define VCCVAL_MIN 3200 //3500          //强制休眠电压
#define VCCVAL_LOW 3500 //3600           //低电压报警 电压       
#define VCCVAL_MAX 4170         //大于4.1V关闭充电
#define VCCVAL_START_CHARGE 4120   //小于4V开始充电

#define CHARGE_PORT GPIOA
#define CHARGE_PIN GPIO_PIN_2

#define CHARGE_START() GPIO_WriteHigh(CHARGE_PORT,CHARGE_PIN)
#define CHARGE_STOP() GPIO_WriteLow(CHARGE_PORT,CHARGE_PIN)


void ADC_Init(void);
uint16_t GetVccVal(void);
uint16_t OneChannelGetADValue(ADC1_Channel_TypeDef ADC1_Channel,ADC1_SchmittTrigg_TypeDef ADC1_SchmittTriggerChannel);

#endif
