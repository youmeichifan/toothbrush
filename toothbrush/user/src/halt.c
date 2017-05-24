#include "halt.h"
#include "main.h"
#include "key.h"
#include "tim2.h"
#include "adc.h"
#include "tim1.h"
/*
功耗 慢慢调试
功耗参考
http://bbs.eeworld.com.cn/thread-253053-1-1.html
http://www.stmcu.org/module/forum/thread-593627-1-1.html
*/

void Halt_OffDevice(void)
{
  /*
  //关闭设备前，设置系统主时钟，和中断   
  CLK_DeInit();//复位时钟寄存器
  CLK_HSICmd(ENABLE);//使能内部高速时钟
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV4);//配置内部高速时钟(时钟分频器:4分频),系统时钟4MHz
  CLK_ClockSecuritySystemEnable();//开启时钟安全系统
  
  
  TIM1_CtrlPWMOutputs(DISABLE);
  TIM1_Cmd(DISABLE);
  TIM1_DeInit();
  TIM1_Cmd(DISABLE);
  TIM2_Cmd(DISABLE);
  TIM2_DeInit();
  TIM2_Cmd(DISABLE);
  ADC1_Cmd(DISABLE);
  ADC1_DeInit();
  ADC1_Cmd(DISABLE);
  
  LEDOFF();
  
  
  
  
  GPIO_DeInit(GPIOA);
  GPIO_DeInit(GPIOB);
//  GPIO_DeInit(GPIOC);
  GPIO_DeInit(GPIOD);   
  
  

  GPIO_Init(CHARGE_PORT,CHARGE_PIN,GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_IN_FL_NO_IT);
  
  GPIO_Init(LED_PORT,LED_PIN,GPIO_MODE_IN_PU_NO_IT);
  
  GPIO_Init(KEY_PORT,KEY_PIN,GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(CHARGE_CHECK_PORT,CHARGE_CHECK_PIN,GPIO_MODE_IN_FL_NO_IT);
  
  
 
  
  //停机前关闭不需要的功能模块的时钟  
  
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1,DISABLE);
  
  CLK->PCKENR1 = 0x00;
  CLK->PCKENR2 &= ~0x8C;//关闭所有外设
  
  CFG->GCR |= 0x01;//禁用SWIM
  CLK_SlowActiveHaltWakeUpCmd(ENABLE);//关闭电压调节器  MVR
  FLASH->CR1 |= 0x04;//关闭flash
  
  */
 //关闭设备前，设置系统主时钟，和中断   
  
  //先关闭电机
  
  TIM1_CtrlPWMOutputs(DISABLE);
  TIM1_Cmd(DISABLE);
  TIM1_DeInit();
  
  PWM_NP_HI();
  PWM_PP_HI();
  PWM_NN_LOW();
  PWM_PN_LOW();
  
  TIM2_Cmd(DISABLE);
  TIM2_DeInit();
  
  
  CLK_DeInit();//复位时钟寄存器
  CLK_HSICmd(ENABLE);//使能内部高速时钟
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV4);//配置内部高速时钟(时钟分频器:4分频),系统时钟4MHz
  CLK_ClockSecuritySystemEnable();//开启时钟安全系统
  
  
  
  
  
  ADC1_Cmd(DISABLE);
  ADC1_DeInit();
  
  LEDOFF();
  GPIO_Init(LED_PORT,LED_PIN,GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(CHARGE_PORT,CHARGE_PIN,GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(KEY_PORT,KEY_PIN,GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(CHARGE_CHECK_PORT,CHARGE_CHECK_PIN,GPIO_MODE_IN_FL_NO_IT);
  
  
  //停机前关闭不需要的功能模块的时钟  
  
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1,DISABLE);
  
//  GPIO_WriteHigh(LED_PORT,LED_PIN);
  
  GPIO_DeInit(GPIOA);
  GPIO_DeInit(GPIOB);
//  GPIO_DeInit(GPIOC);
  GPIO_DeInit(GPIOD);
  
  
//  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NP_PIN|PWM_PP_PIN), GPIO_MODE_OUT_PP_HIGH_FAST);      //PC6低速推完输出 低电平
//  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NN_PIN|PWM_PN_PIN), GPIO_MODE_OUT_PP_LOW_FAST);      //PC6低速推完输出 低电平
//  CFG->GCR |= 0x01;//禁用SWIM
//  CLK_SlowActiveHaltWakeUpCmd(ENABLE);//关闭电压调节器  MVR
//  FLASH->CR1 |= 0x04;//关闭flash
}

void JumpHalt(void)
{
  
  Halt_OffDevice();
  disableInterrupts();
    //唤醒引脚设置为中断
  GPIO_Init(KEY_PORT,KEY_PIN,GPIO_MODE_IN_PU_IT);
  GPIO_Init(CHARGE_CHECK_PORT,CHARGE_CHECK_PIN,GPIO_MODE_IN_PU_IT);
//  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);

  //将PD7引脚的TLI中断设置为下降沿中断,TLI是最高优先级中断
 

  enableInterrupts();

  halt();//进入停机模式
}