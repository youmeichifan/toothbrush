#include "key.h"
#include "main.h"
#include "tim2.h"
#include "tim1.h"
#include "halt.h"

uint8_t KeyDownFlag = 0;

void KeyScan(void)
{
/*
  static uint8_t KeyState=KEYUP;
  
  if(KeyState)
  {
    if((GPIO_ReadInputData(KEY_PORT) & KEY_PIN) == 0x00)
    {
      Delay_ms(50);
      if((GPIO_ReadInputData(KEY_PORT) & KEY_PIN) == 0x00)
      {
        KeyState = KEYDOWN;
        
        switch(WorkMode)//��⹤��״̬
        {
          case WORK_NOMAL_LOW://����ǵ͵������л�Ϊ�ߵ�
            WorkMode = WORK_NOMAL_HI;
            LedState = WORK_NOMAL_HI;
            Duty = DUTY_HIGH;
            Cycle = CYCLE;
            break;
          case WORK_NOMAL_HI://����Ǹߵ������л�Ϊ����
            WorkMode = WORK_STOP;
            LedState = WORK_STOP;
            //����͹�������
            do{
              Delay_ms(200);
            }
            while(!(GPIO_ReadInputData(KEY_PORT) & KEY_PIN));
            JumpHalt();
            break;
          default:break;
        }
      }
    }
  }
  if((GPIO_ReadInputData(KEY_PORT) & KEY_PIN)) KeyState = KEYUP;//����
  */

  if(KeyDownFlag==1)
  {
    KeyDownFlag = 2;
    switch(WorkMode)//��⹤��״̬
    {
      case WORK_NOMAL_LOW://����ǵ͵������л�Ϊ�ߵ�
        WorkMode = WORK_NOMAL_HI;
        LedState = WORK_NOMAL_HI;
        Duty = DUTY_HIGH;
        Cycle = CYCLE;
        break;
      case WORK_NOMAL_HI://����Ǹߵ������л�Ϊ����
        WorkMode = WORK_STOP;
        LedState = WORK_STOP;
        //����͹�������
//        do{
//          Delay_ms(200);
//        }
//        while(!(GPIO_ReadInputData(KEY_PORT) & KEY_PIN));
        JumpHalt();
        break;
      default:break;
    }
  }

}