/**
  ******************************************************************************
  * @file    stm8s_it.c
  * @author   MCD Application Team
  * @version  V2.0.0
  * @date     25-February-2011
  * @brief    Main Interrupt Service Routines.
  *           This file provides template for all peripherals interrupt service 
  *           routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s_it.h"
#include "tim1.h"
#include "tim2.h"
#include "halt.h"
#include "main.h"
#include "key.h"
#include "charge.h"
#include "eeprom.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy Interrupt routine
  * @par Parameters:
  * None
  * @retval
  * None
*/
INTERRUPT_HANDLER(NonHandledInterrupt, 25)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*_COSMIC_*/

/**
  * @brief TRAP Interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
/**
  * @brief Top Level Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TLI_IRQHandler, 0)

{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Auto Wake Up Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(AWU_IRQHandler, 1)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Clock Controller Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(CLK_IRQHandler, 2)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTA Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */

}

/**
  * @brief External Interrupt PORTB Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTC Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 
  if((GPIO_ReadInputData(KEY_PORT) & KEY_PIN) == 0x00)//KEY
  {
    FlashWriteByte(FLASHDATA_ADDR,WORKWAKEUP_FLAG);
    WWDG->CR |= 0x80;//开启看门狗
    WWDG->CR &= 0xBF;//复位
  }

  if((GPIO_ReadInputData(CHARGE_CHECK_PORT) & CHARGE_CHECK_PIN) == 0x00)//BAT
  {
    FlashWriteByte(FLASHDATA_ADDR,CHARGEWAKEUP_FLAG);
    WWDG->CR |= 0x80;//开启看门狗
    WWDG->CR &= 0xBF;//复位
  }
}

/**
  * @brief External Interrupt PORTE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#ifdef STM8S903
/**
  * @brief External Interrupt PORTF Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(EXTI_PORTF_IRQHandler, 8)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /*STM8S903*/

#if defined (STM8S208) || defined (STM8AF52Ax)
/**
  * @brief CAN RX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(CAN_RX_IRQHandler, 8)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }

/**
  * @brief CAN TX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(CAN_TX_IRQHandler, 9)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /*STM8S208 || STM8AF52Ax */

/**
  * @brief SPI Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI_IRQHandler, 10)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer1 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  static uint16_t count=0;
    
  if(count  <= Duty)  
  {
    PWM_NP_LOW(); 
    PWM_NN_HI(); 
  }
  else  
  {
    PWM_NP_HI();
    PWM_NN_LOW();
  }
  
  if((count >= (Cycle/2)) && (count <= ((Cycle/2)+Duty)))
  {
    PWM_PP_LOW();
    PWM_PN_HI();
  }
  else 
  {
    PWM_PP_HI();
    PWM_PN_LOW();
  }
  
  if(count++ >= Cycle)
    count = 0;

  
  TIM1_ClearITPendingBit(TIM1_IT_UPDATE);  
}

/**
  * @brief Timer1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#ifdef STM8S903
/**
  * @brief Timer5 Update/Overflow/Break/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM5_UPD_OVF_BRK_TRG_IRQHandler, 13)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
/**
  * @brief Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM5_CAP_COM_IRQHandler, 14)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }

#else /*STM8S208, STM8S207, STM8S105 or STM8S103 or STM8AF62Ax or STM8AF52Ax or STM8AF626x */
/**
  * @brief Timer2 Update/Overflow/Break Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  static uint16_t count=0;
  static uint8_t CheckAdTime;
  static uint16_t Duty_bak=0,Cycle_bak=0;
  static uint8_t promptTime_s120=0,promptTime_s30=0,Prompt_flag=0;
  static uint8_t Prompt_Duty_Time_ms=0;//30s提示  时长
  static uint16_t promptTime_ms=0;//
  static uint16_t chargeCheckCount=0;//检测是否充电    读取到该引脚低电平次数
  static uint8_t chargeOnCount=0;//非充电模式  检测充电电平次数
  static uint8_t ChargeVol=0;
  static uint8_t KeyDownTime=0;
  switch(LedState)
  {
    /*
    case WORK_NOMAL_LOW://正常工作低档位  LED常亮
      LedFlickFre = LED_LOWLEVEL_FLICK_FRE;
      break;
    case WORK_NOMAL_HI:   //正常工作高档位
      LedFlickFre = LED_HIGHLEVEL_FLICK_FRE;
      break;
    */
    case WORK_LOWPOWER://低电压提示   LED闪烁
      LedFlickFre = LED_LOWPOWER_FLICK_FRE;
      LedLightTime = LED_LOWPOWER_LIGHT;
      break;
    case WORK_CHARGE://充电  LED闪烁
      LedFlickFre = LED_CHARGE_FLICK_FRE;
      LedLightTime = LED_CHARTE_LIGHT;
      break;
    default:break;
  }
  if(LedState == WORK_NOMAL_LOW || LedState == WORK_NOMAL_HI)
    LEDON();
  else if(LedState == WORK_STOP || LedState == WORK_FULL)
    LEDOFF();
  else
  {
    if(count <= LedLightTime)
    {
//      count = 0;
      LEDON();
    }
    else
      LEDOFF();
    if(count++ >= LedFlickFre)
    {
      count=0;
      
    }
    
  }
  
  if(WorkStart_Flag==1)//开始工作
  {
    if(promptTime_ms++ == 1000)
    {
      promptTime_ms=0;
      if(promptTime_s30++ == PROMTP_TIME_S)//30一个提示
      {
        promptTime_s30=0;
        Duty_bak = Duty;
        Cycle_bak = Cycle;
        Duty = PROMPT_DUTY;
        Cycle = PROMPT_CYCLE;
        Prompt_flag = 1;
      }
      if(promptTime_s120++ == WORK_TIME_S)//两分钟关机
      {
        promptTime_s120=0;
        WorkOver_Flag = 1;
//        JumpHalt();
      }
    }
  }
  
  if(Prompt_flag)
  {
    if(Prompt_Duty_Time_ms++ == PROMPT_DUTY_TIME_MS)
    {
      Prompt_Duty_Time_ms=0;
      Prompt_flag=0;
      Duty=Duty_bak;
      Cycle=Cycle_bak;
    }
  }
  
  
  if(ChekcAd_flag == 0)//定时检测一次ADC
  {
    if(CheckAdTime++ == 200)
    {
      ChekcAd_flag = 1;
      CheckAdTime = 0;
    }
  }

  //充电检测   
  if((GPIO_ReadInputData(CHARGE_CHECK_PORT) & CHARGE_CHECK_PIN) == 0x00)
  {
    if(chargeCheckCount++ == CHARGE_CHECK_COUNT)//如果一直没高电平，则表示取下了充电器
    {
      ChargeState = CHARGEOFF;
      chargeCheckCount = 0;
    }
    if(ChargeVol)
    {
      ChargeVol = 0;
      if((chargeOnCount++ == 40) && (WorkMode!=WORK_CHARGE))
      {
        chargeOnCount = 0;
        WorkMode  = WORK_CHARGE;
      }
    }
  }
  else
  {//如果有一个高电平  则表示在充电
    chargeCheckCount = 0;
    ChargeState = CHARGEON;
    
    ChargeVol = 1;
  }    
  
  if(KeyDownFlag == 0)
  {
    if((GPIO_ReadInputData(KEY_PORT) & KEY_PIN) == 0x00)
    {
      if(KeyDownTime++ == SUREKEYDOWNTIME)
      {
        KeyDownTime = 0;
        KeyDownFlag = 1;
      }
    }
  }
  if(GPIO_ReadInputData(KEY_PORT) & KEY_PIN)
  {
    KeyDownFlag  = 0;
    KeyDownTime = 0;
  }
  
  if(WaitKeyDownFlag)
  {
    WaitKeyDwonTime++;
  }
  
  TimingDelay_Decrement();
  TIM2_ClearITPendingBit(TIM2_IT_UPDATE);
 }

/**
  * @brief Timer2 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /*STM8S903*/

#if defined (STM8S208) || defined(STM8S207) || defined(STM8S105) || defined (STM8AF62Ax) ||\
    defined (STM8AF52Ax) || defined (STM8AF626x)
/**
  * @brief Timer3 Update/Overflow/Break Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM3_UPD_OVF_BRK_IRQHandler, 15)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }

/**
  * @brief Timer3 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM3_CAP_COM_IRQHandler, 16)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /*STM8S208, STM8S207 or STM8S105 or STM8AF62Ax or STM8AF52Ax or STM8AF626x */

#if defined (STM8S208) || defined(STM8S207) || defined(STM8S103) || defined (STM8AF62Ax) ||\
    defined (STM8AF52Ax) || defined (STM8S903)
/**
  * @brief UART1 TX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART1 RX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /*STM8S208 or STM8S207 or STM8S103 or STM8S903 or STM8AF62Ax or STM8AF52Ax */

/**
  * @brief I2C Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C_IRQHandler, 19)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#if defined (STM8S105) || defined (STM8AF626x)
/**
  * @brief UART2 TX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART2 RX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /* STM8S105 or STM8AF626x */

#if defined(STM8S207) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
/**
  * @brief UART3 TX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART3_TX_IRQHandler, 20)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART3 RX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART3_RX_IRQHandler, 21)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /*STM8S208 or STM8S207 or STM8AF52Ax or STM8AF62Ax */

#if defined(STM8S207) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
/**
  * @brief ADC2 interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(ADC2_IRQHandler, 22)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#else /*STM8S105, STM8S103 or STM8S903 or STM8AF626x */
/**
  * @brief ADC1 interrupt routine.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
 INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /*STM8S208 or STM8S207 or STM8AF52Ax or STM8AF62Ax */

#ifdef STM8S903
/**
  * @brief Timer6 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM6_UPD_OVF_TRG_IRQHandler, 23)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#else /*STM8S208, STM8S207, STM8S105 or STM8S103 or STM8AF52Ax or STM8AF62Ax or STM8AF626x */
/**
  * @brief Timer4 Update/Overflow Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /*STM8S903*/

/**
  * @brief Eeprom EEC Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/