#include "stm32f10x_conf.h"
#include "mystm32f10x.h"
#include "matrixrgb.h"

RCC_ClocksTypeDef RCC_ClockFreq;
volatile u8 cnt = 0;
int main(void)
{
   SetSysClock();
   RCC_GetClocksFreq(&RCC_ClockFreq);
   TIM2_Config(); 
   MatrixRGB_Config();
   HieuUng36();
  while(1)
  {
    HieuUng36();
    HieuUng36();
    HieuUng35();
    HieuUng34(0);
    HieuUng33();
    HieuUng32();
    HieuUng31();
    HieuUng30();
    HieuUng29();
    HieuUng28();
    HieuUng27();
    HieuUng26();
    HieuUng25();
    HieuUng24();
    HieuUng23(0);
    HieuUng22();
    HieuUng20();
    HieuUng19();
    HieuUng18();
    HieuUng16();
    HieuUng15();
    HieuUng14();
    HieuUng13();
    HieuUng12();
    HieuUng11();
    HieuUng10(0);
    HieuUng10(1);
    HieuUng10(2);
    HieuUng9();
    HieuUng8();
    HieuUng7();
    HieuUng6();
    HieuUng5();
    HieuUng4();
    HieuUng3(1);
    HieuUng3(0);
    HieuUng2();
    HieuUng1();
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









