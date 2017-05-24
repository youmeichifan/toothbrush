#include "tim2.h"

/* ȫ�ֱ������� */
static  __IO uint16_t TimingDelay; /* ����ֵ */

/*******************************************************************************
 * ����: Tim2_Timer_Init
 * ����: TIM2��ʱ����ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: TIM2��ʱ����ʱʱ�����
         ʹ���ⲿ24MHz:
         BaseTime_Max=1/(24000000/32768)*(65535+1)=89.478s
         BaseTime_Min=1/24000000*(1+1)=0.083us
         ʹ���ڲ���16MHz
         BaseTime_Max=1/(16000000/32768)*(65535+1)=134.217s
         BaseTime_Min=1/16000000*(1+1)=0.125us
         ���ʹ���ⲿ24MHz���������#define HSE_CLK����#define HSI_CLKע������
         ���ʹ���ⲿ24MHz���������#define HSI_CLK����#define HSE_CLKע������
 ******************************************************************************/
void Tim2_Init(void)
{
    /*BaseTime=1/(16000000/16)*(999+1)=1ms*/
    TIM2_TimeBaseInit(TIM2_PRESCALER_16 ,999);
    TIM2_PrescalerConfig(TIM2_PRESCALER_16,TIM2_PSCRELOADMODE_IMMEDIATE);
    TIM2_ARRPreloadConfig(ENABLE);
    TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE);
    TIM2_Cmd(ENABLE);
}

/*******************************************************************************
 * ����: TimingDelay_Decrement
 * ����: ��ʱ���������Լ�����
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void TimingDelay_Decrement(void)
{
  if(TimingDelay)
    TimingDelay--;
}

/*******************************************************************************
 * ����: Delay_ms
 * ����: ��ʱ����
 * �β�: n10ms -> ��msΪ���������ʱ
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Delay_ms(__IO uint16_t nms)
{	
  TimingDelay = nms;
  while(TimingDelay != 0);
}

/******************** tim2.c **************************************************/