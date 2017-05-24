/*******************************************************************************
һ���������Ҫ��
l ���ָʾ�����ڳ�����ϳ��ʱ��ָʾ����˸��������ʱ��ָʾ�Ƴ�����
�ӳ�����ϰ���ʱ��ָʾ����
l ��籣����������ʱ����繦��Ҫ�Զ��жϣ���ֹ���䡣
l �ŵ籣������ʣ10%����ʱ��ָʾ�ƿ�ʼ��˸��ʾ�������ľ�ʱ��ֹͣ��������ֹ���ŵ硣
l �ܹ�������������λ���͵�λ������������ѹ3.7V����ص�ѹ����Ƶ��256HZ��ռ�ձ�DC��
��ռ�ձ�14%,�ܹ�28%���ߵ�λ������������ѹ3.7V����ص�ѹ����Ƶ��256HZ��ռ�ձ�DC��
��ռ�ձ�20%���ܹ�40%���������βο���

l ���ؿ��ƣ�
1.ÿ�ο�������ʱ����2���ӣ�ÿ��30�룬��һ��ͣ����ʾ��
2.��λ���л�������Ĭ�ϵĵ͵�λ�������͵�λ�����ڼ�����ٰ�һ�¿��أ��л����ߵ�λ��
�ߵ�λ����ʱ���ٰ����أ���ػ���������ʱ�����ܵ�λ�л���Ӱ�죬��Ȼ��ÿ�ο�����ʱ
����2���ӣ�ÿ��30�룬��һ��ͣ����ʾ��
3.��ʱδ��2���ӵ�����¹ػ�������ػ�������3���ӣ���Ȼ�����ػ�ǰ�ļ�ʱ��
4.����״̬ʱ��ָʾ������������ʱ��ָʾ����
*******************************************************************************

��������
1.������
      �����£��������ѣ�����������/��ȡ��ǰRTC�ʹ洢RTC���Ƚ��Ƿ񳬹�3S��
        ��δ���������ȡ�ϴδ洢�Ĺ����ۼ�ʱ�䣬�糬���ˣ�������ۼ�ʱ��
      �����£������л���λ����������
      �����£��������ߣ��ұ��浱ǰ��ʱ/�洢��ǰRTC���ж��Ƿ񳬹�2���ӣ�
        ��δ���������¼��ǰRTC�빤���ۼ�ʱ��
          
2.ÿ��30sһ��ͣ����ʾ��LED��˸(״̬->ͣ����ʾ)/���30s���������ʱ�Ļ����ۼƵģ�

3.LED��
      ����ʱ������(״̬->������)
      30sһ��ͣ����ʾ(״̬->ͣ����ʾ)
      ����ʱ��Ϩ��(״̬->����)
      ���ʱ�����ʱ���Ǳ����ѵģ�

��س����Ȱ���4.1���ã��Ǹ�T100�ߵ�ƽ��磬�͵�ƽ�س��
������ѹ3.5V
����3.5V����������͹���

LED״̬������>���
*******************************************************************************/

#include "main.h"
#include "tim1.h"
#include "tim2.h"
#include "halt.h"
#include "adc.h"
#include "key.h"
#include "eeprom.h"


uint8_t ChekcAd_flag = 0;//AD��ʱ�����
uint8_t WorkMode;
uint8_t LedState;
uint16_t LedFlickFre,LedLightTime;
uint8_t RunModeFlag;//�洢�Ļ��ѱ��
uint8_t WorkStart_Flag=0;
uint8_t WorkOver_Flag=0;
uint8_t ChargeState=CHARGEOFF;

uint8_t WaitKeyDwonTime=0;
uint8_t WaitKeyDownFlag = 0;
void main(void)
{
  __IO uint16_t VccVal=0;
  uint8_t firstCharge=0;
  uint8_t ChargeFullState = 0; 
  
  HartwareInit();
  
  RunModeFlag = FLASH_ReadByte(FLASHDATA_ADDR);
  FlashWriteByte(FLASHDATA_ADDR,FISTSTART_FLAG);//����flash
  
  
  switch(RunModeFlag)
  {
    case FISTSTART_FLAG:
      JumpHalt();
      break;
    case CHARGEWAKEUP_FLAG://��绽�ѣ����ģʽ
      WorkMode = WORK_CHARGE;
      LedState = WORK_CHARGE;
      ChargeState = CHARGEON;//���״̬�����ڳ��
      break;
    case WORKWAKEUP_FLAG://�������ѣ���������ģʽ    
      //��ȴ�һ��ȷ�ϰ���
      WaitKeyDownFlag = 1;
      while(KeyDownFlag == 0)
      {
        if(WaitKeyDwonTime >= SUREKEYDOWNTIME)
          JumpHalt();
      }
      KeyDownFlag = 2;
      WorkMode = WORK_NOMAL_LOW;
      LedState = WORK_NOMAL_LOW;//LED״̬Ϊ ˢ��״̬
      
      VccVal = GetVccVal();//�ɼ�һ��AD��ѹ
      if(VccVal <= VCCVAL_MIN)//��Ҫ����  ����֮ǰ����ѹ�Ƿ��������󣬲����������
         JumpHalt();
      //1.����PWM
      Duty = DUTY_LOW;
      Cycle = CYCLE;
      Tim1_Init();
      //2.��ʼ��ʱ30s
      //���30s��ʱʱ�䵽����ͣ����ʾ
      WorkStart_Flag = 1;
      break;
    default:break;
  }


  VccVal = GetVccVal();//�ɼ�һ��AD��ѹ
  while (1)
  {
    ////////////////���AD��ѹ��ͨ����ѹ�Ĳ���//////////////////////////////////
    if(ChekcAd_flag == 1)//ÿ��һ��ʱ����AD
    {
      ChekcAd_flag=0;
      VccVal = GetVccVal();//�ɼ�AD��ѹ
    }
    
    ////////////////��������ģʽ////////////////////////////////////
    if(WorkMode == WORK_NOMAL_LOW || WorkMode == WORK_NOMAL_HI)
    {
      KeyScan();
            
      if(VccVal <= VCCVAL_LOW)//�͵�ѹ��ʾ
         LedState = WORK_LOWPOWER;
      if(VccVal <= VCCVAL_MIN || WorkOver_Flag)//��Ҫ����  //
        JumpHalt();      
    }
    ////////////////���ģʽ////////////////////////////////////
    if(WorkMode == WORK_CHARGE)
    {
      
      //��һ�ν���  �ص��
      if(firstCharge == 0)
      {
        firstCharge = 1;
        TIM1_CtrlPWMOutputs(DISABLE);
        TIM1_Cmd(DISABLE);
        TIM1_DeInit();
        
        PWM_NP_HI();
        PWM_PP_HI();
        PWM_NN_LOW();
        PWM_PN_LOW();
        
        LedState = WORK_CHARGE;
        ChargeState = CHARGEON;//���״̬�����ڳ��
      }
      
      if(ChargeState == 0)//û��磬������
      {//ȡ�³����
        //������Ҫ������ʱ��һ��ʱ��󣬼��ȷʵ�����ˣ�������
       LedState = WORK_STOP;
       
       Delay_ms(200);
       JumpHalt();
      }
      else//���ڳ��
      {
        if(VccVal >= VCCVAL_MAX)//����4.1V�رճ��
        {
          CHARGE_STOP(); 
          LedState = WORK_FULL;
          ChargeFullState = 1;//��������

//          Delay_ms(200);
//          JumpHalt();
        }
        else if(VccVal < VCCVAL_START_CHARGE)
        {
          if(ChargeFullState != 1)
            LedState = WORK_CHARGE;//������֮�� ���Զ��������� �Զ���粻��˸LED
          CHARGE_START();
        }
      }
    }
  }
  
}

void HartwareInit(void)
{
  CLK_DeInit();//��λʱ�ӼĴ���
  CLK_HSICmd(ENABLE);//ʹ���ڲ�����ʱ��
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//�����ڲ�����ʱ��(ʱ�ӷ�Ƶ��:4��Ƶ),ϵͳʱ��4MHz
  CLK_ClockSecuritySystemEnable();//����ʱ�Ӱ�ȫϵͳ
  
//  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1,ENABLE);
//  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2,ENABLE);
//  CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC,ENABLE);

  Gpio_Init();
  Tim2_Init();
  CHARGE_START();
  LedState = WORK_STOP;//�ر�LED
  enableInterrupts();
}

void Gpio_Init(void)
{
  GPIO_DeInit(PWMPORT);
  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NP_PIN|PWM_PP_PIN), GPIO_MODE_OUT_PP_HIGH_FAST);      //PC6����������� �͵�ƽ
  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NN_PIN|PWM_PN_PIN), GPIO_MODE_OUT_PP_LOW_FAST);      //PC6����������� �͵�ƽ
  GPIO_Init(LED_PORT,LED_PIN,GPIO_MODE_OUT_PP_HIGH_SLOW);
  LEDOFF();
  GPIO_Init(CHARGE_PORT,CHARGE_PIN,GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(KEY_PORT,KEY_PIN,GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(CHARGE_CHECK_PORT,CHARGE_CHECK_PIN,GPIO_MODE_IN_FL_NO_IT);
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
