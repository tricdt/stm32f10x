#include "stm32f10x_conf.h"
//#include "mystm32f10x.h"
#include "mystm32f10x_rcc.h"
#include "mystm32f10x_tim.h"
#include "led.h"
#include "delay.h"
#include "matrixrgb.h"

RCC_ClocksTypeDef RCC_ClockFreq;
volatile u8 cnt = 0;


int main(void){
   SetSysClock();
   RCC_GetClocksFreq(&RCC_ClockFreq);
   TIM2_Config(); 
//   MatrixRGB_Config();
//   HieuUng36();
   while(1){

  }

}


void TIM2_IRQHandler(void)
{
  if(TIM_GetFlagStatus(TIM2, TIM_IT_Update!=RESET))
  {
    MatrixRGB_ScanPWM();
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  }
}