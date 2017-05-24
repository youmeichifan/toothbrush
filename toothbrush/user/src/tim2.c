#include "tim2.h"

/* 全局变量定义 */
static  __IO uint16_t TimingDelay; /* 计数值 */

/*******************************************************************************
 * 名称: Tim2_Timer_Init
 * 功能: TIM2定时器初始化操作
 * 形参: 无
 * 返回: 无
 * 说明: TIM2的时基定时时间计算
         使用外部24MHz:
         BaseTime_Max=1/(24000000/32768)*(65535+1)=89.478s
         BaseTime_Min=1/24000000*(1+1)=0.083us
         使用内部部16MHz
         BaseTime_Max=1/(16000000/32768)*(65535+1)=134.217s
         BaseTime_Min=1/16000000*(1+1)=0.125us
         如果使用外部24MHz晶振则添加#define HSE_CLK，把#define HSI_CLK注释起来
         如果使用外部24MHz晶振则添加#define HSI_CLK，把#define HSE_CLK注释起来
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
 * 名称: TimingDelay_Decrement
 * 功能: 延时计数变量自减操作
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void TimingDelay_Decrement(void)
{
  if(TimingDelay)
    TimingDelay--;
}

/*******************************************************************************
 * 名称: Delay_ms
 * 功能: 延时函数
 * 形参: n10ms -> 以ms为间隔进行延时
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void Delay_ms(__IO uint16_t nms)
{	
  TimingDelay = nms;
  while(TimingDelay != 0);
}

/******************** tim2.c **************************************************/