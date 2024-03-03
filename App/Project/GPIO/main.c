#include "stm32f10x_conf.h"
//#include "mystm32f10x.h"
#include "mystm32f10x_rcc.h"
#include "led.h"
#include "delay.h"

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
void GPIO_Config(void);
int main(void){
   SetSysClock();
   
   RCC_GetClocksFreq(&RCC_ClockFreq);
   GPIO_Config();

   while(1){
      LED_ACTIVE;	
      delay_ms(10);
      LED_IDLE;
      delay_ms(100);
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
