#include "tim1.h"

uint16_t Duty=0,Cycle=0;
/*******************************************************************************
 * ����: Tim1_Init
 * ����: TIM1��ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/

void Tim1_Init(void)
{
/*
  GPIO_DeInit(PWMPORT);
  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NP_PIN|PWM_PP_PIN), GPIO_MODE_OUT_PP_HIGH_FAST);      //PC6����������� �͵�ƽ
  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NN_PIN|PWM_PN_PIN), GPIO_MODE_OUT_PP_LOW_FAST);      //PC6����������� �͵�ƽ
*/
  TIM1_DeInit();  
  TIM1_TimeBaseInit(15, TIM1_COUNTERMODE_UP, 9, 0);//999
  TIM1_SetCounter(0);/* ����������ֵ��Ϊ0 */
  TIM1_ARRPreloadConfig(DISABLE);	/* Ԥװ�ز�ʹ�� */
  TIM1_ITConfig(TIM1_IT_UPDATE , ENABLE);	/* ���������ϼ���/���¼�����������ж� */
 /* 
  TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,
               DUTY_LOW, TIM1_OCPOLARITY_LOW, TIM1_OCPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_RESET); 
  
  
  TIM1_CCxCmd(TIM1_CHANNEL_1, ENABLE); 
  TIM1_OC1PreloadConfig(ENABLE);
  
  TIM1_CtrlPWMOutputs(ENABLE);
  Tim1Ch1_fhag = PWM_START;
  */
  TIM1_Cmd(ENABLE);			/* ʹ��TIM1 */
  
}

