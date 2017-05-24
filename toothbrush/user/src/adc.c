#include "adc.h"


/*******************************************************************************
 * 名称: ADC_Init
 * 功能: adc2初始化操作
 * 形参: 无
 * 返回: 无
 * 说明: ADC2_Init函数的形参不能使用或运算初始化多通道ADC 
 ******************************************************************************/

void ADC_Init(void)
{
    ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,ADC1_CHANNEL_5,\
              ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM, DISABLE,ADC1_ALIGN_RIGHT,\
              ADC1_SCHMITTTRIG_CHANNEL5,DISABLE);
    ADC1_DataBufferCmd(ENABLE);//启用缓存寄存器存储数据
    ADC1_Cmd(ENABLE);
  
}

/*******************************************************************************
 * 名称: OneChannelGetADValue
 * 功能: ADC2单通道选择读取AD值
 * 形参: ADC2_Channel,ADC2_SchmittTriggerChannel
 * 返回: 该通道的AD值
 * 说明: 当要读取多通道AD值采调用该函数，否则只是初始化ADC_Init即可 
 ******************************************************************************/
uint16_t OneChannelGetADValue(ADC1_Channel_TypeDef ADC1_Channel,\
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
#define VCAPVAL ((uint32_t)1220)   //uint mv  1800
#define BITCOUNT (1024)
uint16_t GetVccVal(void)
{
  uint16_t adVal;
  uint32_t sum=0;
  uint8_t i;
//  volatile uint32_t adVcap;

  for(i=0;i<40;i++)
    sum += OneChannelGetADValue(ADC1_CHANNEL_7,ADC1_SCHMITTTRIG_CHANNEL7);///5
  adVal = sum/40;
  return (uint16_t)(VCAPVAL*BITCOUNT/adVal);
//  return (uint16_t)adVcap;
//  adVcap = adVal*VCCVAL/BITCOUNT;
//  return (uint16_t)(VCAPVAL*VCCVAL/adVcap);

   
}

