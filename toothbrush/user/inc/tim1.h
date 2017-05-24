#ifndef __TIM1_H_
#define __TIM1_H_

#include "stm8s.h"

#ifdef DUTYCYLE1821
#define CYCLE (167)//6   //1/256
#define DUTY_LOW  (30)//6 //3906*0.18
#define DUTY_HIGH (35)//1 //3906*0.21
#endif

#ifdef DUTYCYLE1420
#define CYCLE (168)//6   //1/256
#define DUTY_LOW  (22)//6 //3906*0.14
#define DUTY_HIGH (32)//1 //3906*0.2
#endif

#define PROMPT_CYCLE 150 //30s��ʾ����
#define PROMPT_DUTY 37   //30s��ʾռ�ձ� 30%

#define PROMPT_DUTY_TIME_MS 250//30s��ʾ ʱ�� 200ms
#define PROMTP_TIME_S 30  //Ĭ����ʾ  ʱ��  Ϊ30s
#define WORK_TIME_S 120   //Ĭ�Ϲ���ʱ�� 120s

#define PWM_START 1
#define PWM_STOP 0

#define PWMPORT GPIOC
#define PWM_NP_PIN GPIO_PIN_7//N+
#define PWM_NN_PIN GPIO_PIN_4//N-
#define PWM_PP_PIN GPIO_PIN_6//P+
#define PWM_PN_PIN GPIO_PIN_3//P-

//#define PWN_N_TOGLE() GPIO_WriteReverse(PWMPORT,(GPIO_Pin_TypeDef)(PWM_NP_PIN|PWM_NN_PIN))
#define PWM_NP_HI() GPIO_WriteHigh(PWMPORT,PWM_NP_PIN)
#define PWM_NN_HI() GPIO_WriteHigh(PWMPORT,PWM_NN_PIN)
#define PWM_NP_LOW() GPIO_WriteLow(PWMPORT,PWM_NP_PIN)
#define PWM_NN_LOW() GPIO_WriteLow(PWMPORT,PWM_NN_PIN)

//#define PWN_P_TOGLE() GPIO_WriteReverse(PWMPORT,(GPIO_Pin_TypeDef)(PWM_NN_PIN|PWM_PP_PIN))
#define PWM_PP_HI() GPIO_WriteHigh(PWMPORT,PWM_PP_PIN)
#define PWM_PN_HI() GPIO_WriteHigh(PWMPORT,PWM_PN_PIN)
#define PWM_PP_LOW() GPIO_WriteLow(PWMPORT,PWM_PP_PIN)
#define PWM_PN_LOW() GPIO_WriteLow(PWMPORT,PWM_PN_PIN)

extern uint16_t Duty,Cycle;

/*******************************************************************************
 * ����: Tim1_Init
 * ����: TIM1��ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Tim1_Init(void);
void Tim1_Ch2(FunctionalState state);
#endif