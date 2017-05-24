#include "adc.h"
#include "uart1.h"



/*******************************************************************************
 * ����: ADC_Init
 * ����: adc2��ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: ADC2_Init�������ββ���ʹ�û������ʼ����ͨ��ADC 
 ******************************************************************************/
/*
void ADC_Init(void)
{
    ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,(ADC1_CHANNEL_3),\
              ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM, DISABLE,ADC1_ALIGN_RIGHT,\
              (ADC1_SCHMITTTRIG_CHANNEL6|ADC1_SCHMITTTRIG_CHANNEL6),DISABLE);
    ADC1_DataBufferCmd(ENABLE);//���û���Ĵ����洢����
    ADC1_Cmd(ENABLE);
  
}
*/

/**************************************************************************
 * ��������Send_ADC_Value
 * ����  ��ADCת�������ʾ����
 * ����  ��AD_Value--ADCת�����ֵ
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ڲ����� 
 *************************************************************************/
void Send_ADC_Value(uint16_t AD_Value)
{
    UART1_SendByte(AD_Value/1000+0x30);
    UART1_SendByte(AD_Value%1000/100+0x30);
    UART1_SendByte(AD_Value%1000%100/10+0x30);
    UART1_SendByte(AD_Value%1000%100%10+0x30);
}

/*******************************************************************************
 * ����: OneChannelGetADValue
 * ����: ADC2��ͨ��ѡ���ȡADֵ
 * �β�: ADC2_Channel,ADC2_SchmittTriggerChannel
 * ����: ��ͨ����ADֵ
 * ˵��: ��Ҫ��ȡ��ͨ��ADֵ�ɵ��øú���������ֻ�ǳ�ʼ��ADC_Init���� 
 ******************************************************************************/
static uint16_t OneChannelGetADValue(ADC1_Channel_TypeDef ADC1_Channel,\
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

/**************************************************************************
 * ��������MultipleChannelGetADValue
 * ����  ����ӡADC��ͨ����ȡADֵ
 * ����  ����
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ���� 
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
