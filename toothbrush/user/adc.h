#ifndef __ADC_H_
#define __ADC_H_

/* �����Զ���ͷ�ļ� */
#include "stm8s.h"


/**************************************************************************
 * ��������Send_ADC_Value
 * ����  ��ADCת�������ʾ����
 * ����  ��AD_Value--ADCת�����ֵ
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ڲ����� 
 *************************************************************************/
//void ADC_Init(void);
void Send_ADC_Value(uint16_t AD_Value);
void MultipleChannelGetADValue(void);

#endif