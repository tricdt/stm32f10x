
#include "stm32f10x_conf.h"

#include "mystm32f10x.h"
#include "led.h"




#define LED_Pin   GPIO_Pin_13
#define LED_Speed GPIO_Speed_50MHz
#define LED_Mode  GPIO_Mode_Out_PP
#define LED_Port  GPIOC
#define LED_Bus   RCC_APB2Periph_GPIOC



#define LED_ACTIVE   GPIO_ResetBits(LED_Port, LED_Pin)
#define LED_IDLE     GPIO_SetBits(LED_Port, LED_Pin)


/*
   When breakpoint disapppear 
   The solution is go to st-link options -> debug tab -> 
   download options -> Uncheck Download to flash. 
   Now debugger works perfectly
*/

RCC_ClocksTypeDef RCC_ClockFreq;

volatile FlagStatus myTimer = 0;
void GPIO_Config(void);
u32 clk;
int main(void){
//   SetSysClock();
   RCC_GetClocksFreq(&RCC_ClockFreq);
 
   GPIO_Config();
   GPIO_DeInit(LED_Port);
   MyGPIO_Init(LED_Port, LED_Pin, LED_Mode, LED_Speed,LED_Bus);
// MyGPIO_Init(LED_Port, LED_Pin, LED_Mode, LED_Speed, 
   clk = RCC_ClockFreq.SYSCLK_Frequency;
 
   DWTDelay_Init();
   MyTimer_Init(TIM1, 0, 100, 0, 0, 0, 0);
   MyTimer_OnOrOffIrq(TIM1, SET);
//   MyTimer_Start(TIM1);
   //TIM2_Config();
  //TIM1_Config();
   while(1){
//      LED_ACTIVE;	
//      DWTDelay_ms(100);
//      // delay_ms(100);
//      LED_IDLE;
//      DWTDelay_ms(1000);
//      // delay_ms(1000);
      
  }

}



void GPIO_Config(void){
   GPIO_DeInit(LED_Port);

   GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(LED_Bus, ENABLE);
   GPIO_InitStructure.GPIO_Mode = LED_Mode;
   GPIO_InitStructure.GPIO_Speed = LED_Speed;
   GPIO_InitStructure.GPIO_Pin = LED_Pin;
   GPIO_Init(LED_Port, &GPIO_InitStructure);
}

void TIM1_UP_IRQHandler(void) {
  if(TIM_GetFlagStatus(TIM1, TIM_FLAG_Update)){
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	 MyGPIO_Toggle(LED_Port, 13);
  }
   TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
}

void TIM2_IRQHandler(void){
   
   if(TIM_GetFlagStatus(TIM2, TIM_IT_Update!=RESET))
   {
      MyGPIO_Toggle(LED_Port, 13);
      TIM_ClearFlag(TIM2, TIM_FLAG_Update);
   }
}


