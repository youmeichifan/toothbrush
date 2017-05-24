#ifndef __ADC_H_
#define __ADC_H_

/* 包含自定义头文件 */
#include "stm8s.h"


/**************************************************************************
 * 函数名：Send_ADC_Value
 * 描述  ：ADC转换结果显示函数
 * 输入  ：AD_Value--ADC转换结果值
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：内部调用 
 *************************************************************************/
//void ADC_Init(void);
void Send_ADC_Value(uint16_t AD_Value);
void MultipleChannelGetADValue(void);

#endif