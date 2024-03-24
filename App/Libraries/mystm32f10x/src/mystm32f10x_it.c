#include "mystm32f10x.h"
#include "stm32f10x_it.h"

#ifdef USE_CAPTURE_TIM1

#endif

void TIM1_UP_IRQHandler(void) {
   #if defined USE_TIMER1
   if(TIM_GetFlagStatus(TIM1, TIM_FLAG_Update)){
      TIM_ClearFlag(TIM1, TIM_FLAG_Update);
       
   }
   TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
   TIM1_IRQn();	
   #endif
}



