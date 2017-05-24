#include "tim1.h"

uint16_t Duty=0,Cycle=0;
/*******************************************************************************
 * 名称: Tim1_Init
 * 功能: TIM1初始化操作
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/

void Tim1_Init(void)
{
/*
  GPIO_DeInit(PWMPORT);
  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NP_PIN|PWM_PP_PIN), GPIO_MODE_OUT_PP_HIGH_FAST);      //PC6低速推完输出 低电平
  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NN_PIN|PWM_PN_PIN), GPIO_MODE_OUT_PP_LOW_FAST);      //PC6低速推完输出 低电平
*/
  TIM1_DeInit();  
  TIM1_TimeBaseInit(15, TIM1_COUNTERMODE_UP, 9, 0);//999
  TIM1_SetCounter(0);/* 将计数器初值设为0 */
  TIM1_ARRPreloadConfig(DISABLE);	/* 预装载不使能 */
  TIM1_ITConfig(TIM1_IT_UPDATE , ENABLE);	/* 计数器向上计数/向下计数溢出更新中断 */
 /* 
  TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,
               DUTY_LOW, TIM1_OCPOLARITY_LOW, TIM1_OCPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_RESET); 
  
  
  TIM1_CCxCmd(TIM1_CHANNEL_1, ENABLE); 
  TIM1_OC1PreloadConfig(ENABLE);
  
  TIM1_CtrlPWMOutputs(ENABLE);
  Tim1Ch1_fhag = PWM_START;
  */
  TIM1_Cmd(ENABLE);			/* 使能TIM1 */
  
}

