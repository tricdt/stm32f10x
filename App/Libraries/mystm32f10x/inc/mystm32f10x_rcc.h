#ifndef __MY_STM32F10x_RCC_H
#define __MY_STM32F10x_RCC_H
#include "stm32f10x.h"




typedef struct _PIN {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_TypeDef* GPIOx;
  uint32_t GPIO_Bus;
  
} PIN;

void SetSysClock(void);
void SetSysClockToHSE(void);
void SetSysClockTo24(void);
void SetSysClockTo36(void);
void SetSysClockTo48(void);
void SetSysClockTo56(void);
void SetSysClockTo72(void);



#endif