#include "adc.h"


/*******************************************************************************
 * ����: ADC_Init
 * ����: adc2��ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: ADC2_Init�������ββ���ʹ�û������ʼ����ͨ��ADC 
 ******************************************************************************/

void ADC_Init(void)
{
    ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,ADC1_CHANNEL_5,\
              ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM, DISABLE,ADC1_ALIGN_RIGHT,\
              ADC1_SCHMITTTRIG_CHANNEL5,DISABLE);
    ADC1_DataBufferCmd(ENABLE);//���û���Ĵ����洢����
    ADC1_Cmd(ENABLE);
  
}

/*******************************************************************************
 * ����: OneChannelGetADValue
 * ����: ADC2��ͨ��ѡ���ȡADֵ
 * �β�: ADC2_Channel,ADC2_SchmittTriggerChannel
 * ����: ��ͨ����ADֵ
 * ˵��: ��Ҫ��ȡ��ͨ��ADֵ�ɵ��øú���������ֻ�ǳ�ʼ��ADC_Init���� 
 ******************************************************************************/
uint16_t OneChannelGetADValue(ADC1_Channel_TypeDef ADC1_Channel,\
                                     ADC1_SchmittTrigg_TypeDef ADC1_SchmittTriggerChannel)
{
    uint16_t ADConversion_Value;
    /**< ����ת��ģʽ */
    /**< ʹ��ͨ�� */
    /**< ADCʱ�ӣ�fADC2 = fcpu/18 */
    /**< ���������˴�TIM TRGO ����ת������ʵ����û���õ���*/
    /**  ��ʹ�� ADC2_ExtTriggerState**/
    /**< ת�������Ҷ��� */
    /**< ��ʹ��ͨ��10��˹���ش����� */
    /**  ��ʹ��ͨ��10��˹���ش�����״̬ */
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

