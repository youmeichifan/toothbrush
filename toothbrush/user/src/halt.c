#include "halt.h"
#include "main.h"
#include "key.h"
#include "tim2.h"
#include "adc.h"
#include "tim1.h"
/*
���� ��������
���Ĳο�
http://bbs.eeworld.com.cn/thread-253053-1-1.html
http://www.stmcu.org/module/forum/thread-593627-1-1.html
*/

void Halt_OffDevice(void)
{
  /*
  //�ر��豸ǰ������ϵͳ��ʱ�ӣ����ж�   
  CLK_DeInit();//��λʱ�ӼĴ���
  CLK_HSICmd(ENABLE);//ʹ���ڲ�����ʱ��
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV4);//�����ڲ�����ʱ��(ʱ�ӷ�Ƶ��:4��Ƶ),ϵͳʱ��4MHz
  CLK_ClockSecuritySystemEnable();//����ʱ�Ӱ�ȫϵͳ
  
  
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
  
  
 
  
  //ͣ��ǰ�رղ���Ҫ�Ĺ���ģ���ʱ��  
  
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1,DISABLE);
  
  CLK->PCKENR1 = 0x00;
  CLK->PCKENR2 &= ~0x8C;//�ر���������
  
  CFG->GCR |= 0x01;//����SWIM
  CLK_SlowActiveHaltWakeUpCmd(ENABLE);//�رյ�ѹ������  MVR
  FLASH->CR1 |= 0x04;//�ر�flash
  
  */
 //�ر��豸ǰ������ϵͳ��ʱ�ӣ����ж�   
  
  //�ȹرյ��
  
  TIM1_CtrlPWMOutputs(DISABLE);
  TIM1_Cmd(DISABLE);
  TIM1_DeInit();
  
  PWM_NP_HI();
  PWM_PP_HI();
  PWM_NN_LOW();
  PWM_PN_LOW();
  
  TIM2_Cmd(DISABLE);
  TIM2_DeInit();
  
  
  CLK_DeInit();//��λʱ�ӼĴ���
  CLK_HSICmd(ENABLE);//ʹ���ڲ�����ʱ��
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV4);//�����ڲ�����ʱ��(ʱ�ӷ�Ƶ��:4��Ƶ),ϵͳʱ��4MHz
  CLK_ClockSecuritySystemEnable();//����ʱ�Ӱ�ȫϵͳ
  
  
  
  
  
  ADC1_Cmd(DISABLE);
  ADC1_DeInit();
  
  LEDOFF();
  GPIO_Init(LED_PORT,LED_PIN,GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(CHARGE_PORT,CHARGE_PIN,GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(KEY_PORT,KEY_PIN,GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(CHARGE_CHECK_PORT,CHARGE_CHECK_PIN,GPIO_MODE_IN_FL_NO_IT);
  
  
  //ͣ��ǰ�رղ���Ҫ�Ĺ���ģ���ʱ��  
  
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
  
  
//  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NP_PIN|PWM_PP_PIN), GPIO_MODE_OUT_PP_HIGH_FAST);      //PC6����������� �͵�ƽ
//  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NN_PIN|PWM_PN_PIN), GPIO_MODE_OUT_PP_LOW_FAST);      //PC6����������� �͵�ƽ
//  CFG->GCR |= 0x01;//����SWIM
//  CLK_SlowActiveHaltWakeUpCmd(ENABLE);//�رյ�ѹ������  MVR
//  FLASH->CR1 |= 0x04;//�ر�flash
}

void JumpHalt(void)
{
  
  Halt_OffDevice();
  disableInterrupts();
    //������������Ϊ�ж�
  GPIO_Init(KEY_PORT,KEY_PIN,GPIO_MODE_IN_PU_IT);
  GPIO_Init(CHARGE_CHECK_PORT,CHARGE_CHECK_PIN,GPIO_MODE_IN_PU_IT);
//  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);

  //��PD7���ŵ�TLI�ж�����Ϊ�½����ж�,TLI��������ȼ��ж�
 

  enableInterrupts();

  halt();//����ͣ��ģʽ
}