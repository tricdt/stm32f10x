#include "IRQHandler.h"

void TIM1_UP_IRQHandler(void) {
   #if defined USE_TIMER1
   if(TIM_GetFlagStatus(TIM1, TIM_FLAG_Update)){
      TIM_ClearFlag(TIM1, TIM_FLAG_Update);
       
   }
   TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);

   #endif
}

