#include "mystm32f10x_tim.h"

void TIM2_Config(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_Initstructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_TimeBaseInitStructure.TIM_Prescaler = 256;
  TIM_TimeBaseInitStructure.TIM_Period = 1500;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
  NVIC_Initstructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_Initstructure);  
}

