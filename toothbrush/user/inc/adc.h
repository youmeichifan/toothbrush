#ifndef __ADC_H_
#define __ADC_H_

/* �����Զ���ͷ�ļ� */
#include "stm8s.h"

#define VCCVAL_MIN 3200 //3500          //ǿ�����ߵ�ѹ
#define VCCVAL_LOW 3500 //3600           //�͵�ѹ���� ��ѹ       
#define VCCVAL_MAX 4170         //����4.1V�رճ��
#define VCCVAL_START_CHARGE 4120   //С��4V��ʼ���

#define CHARGE_PORT GPIOA
#define CHARGE_PIN GPIO_PIN_2

#define CHARGE_START() GPIO_WriteHigh(CHARGE_PORT,CHARGE_PIN)
#define CHARGE_STOP() GPIO_WriteLow(CHARGE_PORT,CHARGE_PIN)


void ADC_Init(void);
uint16_t GetVccVal(void);
uint16_t OneChannelGetADValue(ADC1_Channel_TypeDef ADC1_Channel,ADC1_SchmittTrigg_TypeDef ADC1_SchmittTriggerChannel);

#endif
