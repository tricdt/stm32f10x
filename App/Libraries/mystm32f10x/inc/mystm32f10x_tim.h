#ifndef __MY_STM32F10x_TIM_H
#define __MY_STM32F10x_TIM_H
#include "stm32f10x.h"
#define USE_TIMER
#define INPUTMAX     59702385 //911*65535 最大计数
#define COEFFICIENT  911    //72M下不分频最大计时us  

void TIM2_Config(void);
void MyTimer_Init(TIM_TypeDef *timer,u16 second,u16 millisecond,u16 microsecond,u8 Prioritygroup,u8 preemprionPriority,u8 subPriority);
FlagStatus MyTimer_Conversion(u16 s, u16 ms, u16 us);
void MyTimer_OnOrOffIrq(TIM_TypeDef *timer, FlagStatus Switch);
void MyTimer_ClearCNT(TIM_TypeDef *timer);
#endif
