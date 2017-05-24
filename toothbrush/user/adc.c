#include "adc.h"
#include "uart1.h"



/*******************************************************************************
 * 名称: ADC_Init
 * 功能: adc2初始化操作
 * 形参: 无
 * 返回: 无
 * 说明: ADC2_Init函数的形参不能使用或运算初始化多通道ADC 
 ******************************************************************************/
/*
void ADC_Init(void)
{
    ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,(ADC1_CHANNEL_3),\
              ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM, DISABLE,ADC1_ALIGN_RIGHT,\
              (ADC1_SCHMITTTRIG_CHANNEL6|ADC1_SCHMITTTRIG_CHANNEL6),DISABLE);
    ADC1_DataBufferCmd(ENABLE);//启用缓存寄存器存储数据
    ADC1_Cmd(ENABLE);
  
}
*/

/**************************************************************************
 * 函数名：Send_ADC_Value
 * 描述  ：ADC转换结果显示函数
 * 输入  ：AD_Value--ADC转换结果值
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：内部调用 
 *************************************************************************/
void Send_ADC_Value(uint16_t AD_Value)
{
    UART1_SendByte(AD_Value/1000+0x30);
    UART1_SendByte(AD_Value%1000/100+0x30);
    UART1_SendByte(AD_Value%1000%100/10+0x30);
    UART1_SendByte(AD_Value%1000%100%10+0x30);
}

/*******************************************************************************
 * 名称: OneChannelGetADValue
 * 功能: ADC2单通道选择读取AD值
 * 形参: ADC2_Channel,ADC2_SchmittTriggerChannel
 * 返回: 该通道的AD值
 * 说明: 当要读取多通道AD值采调用该函数，否则只是初始化ADC_Init即可 
 ******************************************************************************/
static uint16_t OneChannelGetADValue(ADC1_Channel_TypeDef ADC1_Channel,\
                                     ADC1_SchmittTrigg_TypeDef ADC1_SchmittTriggerChannel)
{
    uint16_t ADConversion_Value;
    /**< 连续转换模式 */
    /**< 使能通道 */
    /**< ADC时钟：fADC2 = fcpu/18 */
    /**< 这里设置了从TIM TRGO 启动转换，但实际是没有用到的*/
    /**  不使能 ADC2_ExtTriggerState**/
    /**< 转换数据右对齐 */
    /**< 不使能通道10的斯密特触发器 */
    /**  不使能通道10的斯密特触发器状态 */
    ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS , ADC1_Channel, ADC1_PRESSEL_FCPU_D18,\
		ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SchmittTriggerChannel,DISABLE);
    ADC1_Cmd(ENABLE);
    ADC1_StartConversion();
    ADConversion_Value = ADC1_GetConversionValue();
    return ADConversion_Value;
}

/**************************************************************************
 * 函数名：MultipleChannelGetADValue
 * 描述  ：打印ADC多通道读取AD值
 * 输入  ：无
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 
 *************************************************************************/
#define VCAPVAL 1800   //uint mv
void MultipleChannelGetADValue(void)
{
 // uint32_t adcVot;
//  uint16_t adcVal;
//  uint8_t buf[10];
  
//  adcVal = OneChannelGetADValue(ADC1_CHANNEL_3,ADC1_SCHMITTTRIG_CHANNEL3);
  /*
  itoa(adcVal,(char*)buf,10);
  UART1_printf("\r\nadcVal:");
  UART1_SendData(buf,10);
  
  adcVot = adcVal*3300/1024;
  adcVot = adcVot;
  
  itoa(adcVot,(char*)buf,10);
  UART1_printf("\r\nadcVcap:");
  UART1_SendData(buf,10);
  
  adcVot = VCAPVAL*3300/adcVot;
  
  itoa(adcVot,(char*)buf,10);
  UART1_printf("\r\nadcVdd:");
  UART1_SendData(buf,10);
  */
}
