#ifndef _MAIN_H_
#define _MAIN_H_

#include "sysclock.h"
#include "stm8s.h"

#define WAKE_NONE 0
#define WAKE_KEYMODE 1
#define WAKE_BATMODE 2

#define VBAT_HIGH 4100
#define VBAT_LOW 3500

#define HALT 0
#define LOWLEVEL 1
#define HILEVEL 2


#define LED_PORT GPIOB
#define LED_PIN GPIO_PIN_5

#define LED_ON 0
#define LED_OFF 1

#define LEDON() GPIO_WriteLow(LED_PORT,LED_PIN)
#define LEDOFF() GPIO_WriteHigh(LED_PORT,LED_PIN)
#define LEDTOGLE() GPIO_WriteReverse(LED_PORT,LED_PIN)

#define LED_LOWPOWER_FLICK_FRE 3000
#define LED_LOWPOWER_LIGHT 1000
//#define LED_LOWLEVEL_FLICK_FRE 150
//#define LED_HIGHLEVEL_FLICK_FRE 100
#define LED_CHARGE_FLICK_FRE 3000
#define LED_CHARTE_LIGHT 1000

#define CHARGE_CHECK_COUNT 1000

#define SUREKEYDOWNTIME 50   //�ж��ﰴ���͵�ƽʱ�� ȷ�ϰ�������

enum{
  WORK_NOMAL_LOW=1,//���������͵�λ  LED����
  WORK_NOMAL_HI,   //���������ߵ�λ
  WORK_LOWPOWER,//�͵�ѹ��ʾ   LED��˸
  WORK_CHARGE,//���  LED��˸
  WORK_FULL,//����   LED����
  WORK_STOP,//ֹͣ����   LEDϨ��
};

extern uint8_t WorkMode,LedState;
extern uint16_t LedFlickFre,LedLightTime;
extern uint8_t WorkStart_Flag,WorkOver_Flag;
extern uint8_t ChargeState;

#define CHARGEON 1
#define CHARGEOFF 0

extern uint8_t ChekcAd_flag;
extern uint8_t WaitKeyDwonTime;
extern uint8_t WaitKeyDownFlag;


void Gpio_Init(void);
void HartwareInit(void);
void CheckPower(void);
#endif
