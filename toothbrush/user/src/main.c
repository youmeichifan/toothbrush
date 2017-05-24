/*******************************************************************************
一，程序控制要求：
l 充电指示：放在充电器上充电时，指示灯闪烁；充满电时，指示灯常亮。
从充电器上拔下时，指示灯灭。
l 充电保护：充满电时，充电功能要自动切断，防止过充。
l 放电保护：还剩10%电量时，指示灯开始闪烁提示；电量耗尽时，停止工作，防止过放电。
l 总共有两个工作档位：低档位工作参数：电压3.7V（电池电压），频率256HZ，占空比DC：
正占空比14%,总共28%；高档位工作参数：电压3.7V（电池电压），频率256HZ，占空比DC：
正占空比20%，总共40%。方波波形参考：

l 开关控制：
1.每次开机，定时工作2分钟，每隔30秒，有一个停顿提示。
2.档位的切换：开机默认的低档位工作，低档位工作期间如果再按一下开关，切换到高档位，
高档位工作时，再按开关，会关机。工作计时，不受档位切换的影响，仍然是每次开机定时
工作2分钟，每隔30秒，有一个停顿提示。
3.计时未满2分钟的情况下关机，如果关机不超过3秒钟，仍然延续关机前的计时。
4.工作状态时，指示灯亮，不工作时，指示灯灭。
*******************************************************************************

程序流程
1.按键：
      休眠下，按键唤醒，且启动低速/读取当前RTC和存储RTC，比较是否超过3S，
        如未超过，则读取上次存储的工作累计时间，如超过了，则清除累计时间
      低速下，按键切换档位，启动高速
      高速下，按键休眠，且保存当前及时/存储当前RTC，判断是否超过2分钟，
        如未超过，则记录当前RTC与工作累计时间
          
2.每隔30s一个停顿提示，LED闪烁(状态->停顿提示)/这个30s是启动后计时的还是累计的？

3.LED：
      工作时，常亮(状态->工作中)
      30s一个停顿提示(状态->停顿提示)
      休眠时，熄灭(状态->休眠)
      充电时，这个时候是被唤醒的，

电池充满先按照4.1设置，那个T100高电平充电，低电平关充电
保护电压3.5V
低于3.5V不工作进入低功耗

LED状态，工作>充电
*******************************************************************************/

#include "main.h"
#include "tim1.h"
#include "tim2.h"
#include "halt.h"
#include "adc.h"
#include "key.h"
#include "eeprom.h"


uint8_t ChekcAd_flag = 0;//AD定时检测标记
uint8_t WorkMode;
uint8_t LedState;
uint16_t LedFlickFre,LedLightTime;
uint8_t RunModeFlag;//存储的唤醒标记
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
  FlashWriteByte(FLASHDATA_ADDR,FISTSTART_FLAG);//清零flash
  
  
  switch(RunModeFlag)
  {
    case FISTSTART_FLAG:
      JumpHalt();
      break;
    case CHARGEWAKEUP_FLAG://充电唤醒，充电模式
      WorkMode = WORK_CHARGE;
      LedState = WORK_CHARGE;
      ChargeState = CHARGEON;//充电状态，正在充电
      break;
    case WORKWAKEUP_FLAG://按键唤醒，正常工作模式    
      //需等待一个确认按键
      WaitKeyDownFlag = 1;
      while(KeyDownFlag == 0)
      {
        if(WaitKeyDwonTime >= SUREKEYDOWNTIME)
          JumpHalt();
      }
      KeyDownFlag = 2;
      WorkMode = WORK_NOMAL_LOW;
      LedState = WORK_NOMAL_LOW;//LED状态为 刷牙状态
      
      VccVal = GetVccVal();//采集一次AD电压
      if(VccVal <= VCCVAL_MIN)//需要休眠  启动之前检查电压是否满足需求，不满足就休眠
         JumpHalt();
      //1.启动PWM
      Duty = DUTY_LOW;
      Cycle = CYCLE;
      Tim1_Init();
      //2.开始计时30s
      //如果30s计时时间到，则停顿提示
      WorkStart_Flag = 1;
      break;
    default:break;
  }


  VccVal = GetVccVal();//采集一次AD电压
  while (1)
  {
    ////////////////检测AD电压，通过电压的操作//////////////////////////////////
    if(ChekcAd_flag == 1)//每隔一定时间检测AD
    {
      ChekcAd_flag=0;
      VccVal = GetVccVal();//采集AD电压
    }
    
    ////////////////正常工作模式////////////////////////////////////
    if(WorkMode == WORK_NOMAL_LOW || WorkMode == WORK_NOMAL_HI)
    {
      KeyScan();
            
      if(VccVal <= VCCVAL_LOW)//低电压提示
         LedState = WORK_LOWPOWER;
      if(VccVal <= VCCVAL_MIN || WorkOver_Flag)//需要休眠  //
        JumpHalt();      
    }
    ////////////////充电模式////////////////////////////////////
    if(WorkMode == WORK_CHARGE)
    {
      
      //第一次进来  关电机
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
        ChargeState = CHARGEON;//充电状态，正在充电
      }
      
      if(ChargeState == 0)//没充电，则休眠
      {//取下充电器
        //这里需要做个延时，一定时间后，检测确实拔下了，再休眠
       LedState = WORK_STOP;
       
       Delay_ms(200);
       JumpHalt();
      }
      else//正在充电
      {
        if(VccVal >= VCCVAL_MAX)//大于4.1V关闭充电
        {
          CHARGE_STOP(); 
          LedState = WORK_FULL;
          ChargeFullState = 1;//充满电标记

//          Delay_ms(200);
//          JumpHalt();
        }
        else if(VccVal < VCCVAL_START_CHARGE)
        {
          if(ChargeFullState != 1)
            LedState = WORK_CHARGE;//充满电之后 再自动降下来的 自动充电不闪烁LED
          CHARGE_START();
        }
      }
    }
  }
  
}

void HartwareInit(void)
{
  CLK_DeInit();//复位时钟寄存器
  CLK_HSICmd(ENABLE);//使能内部高速时钟
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//配置内部高速时钟(时钟分频器:4分频),系统时钟4MHz
  CLK_ClockSecuritySystemEnable();//开启时钟安全系统
  
//  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1,ENABLE);
//  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2,ENABLE);
//  CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC,ENABLE);

  Gpio_Init();
  Tim2_Init();
  CHARGE_START();
  LedState = WORK_STOP;//关闭LED
  enableInterrupts();
}

void Gpio_Init(void)
{
  GPIO_DeInit(PWMPORT);
  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NP_PIN|PWM_PP_PIN), GPIO_MODE_OUT_PP_HIGH_FAST);      //PC6低速推完输出 低电平
  GPIO_Init(PWMPORT, (GPIO_Pin_TypeDef)(PWM_NN_PIN|PWM_PN_PIN), GPIO_MODE_OUT_PP_LOW_FAST);      //PC6低速推完输出 低电平
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
