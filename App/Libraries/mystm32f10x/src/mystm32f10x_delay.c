
#include "mystm32f10x.h"

static u8  fac_us=0;
static uint16_t fac_ms=0;


void delay_init(uint8_t SYSCLK)
{
  SysTick->CTRL&=0xfffffffb;
  fac_us = SYSCLK/8;
  fac_ms=(uint16_t)(fac_us*1000);
}

void delay_ms(u32 nms)
{	 		  	  
  u32 temp;		   
  SysTick->LOAD=(u32)(nms*fac_ms);
  SysTick->VAL =0x00;           
  SysTick->CTRL=0x01;         
  do
  {
     temp=SysTick->CTRL;
  }
  while((temp&0x01)&&(!(temp&(1<<16)))); 
  SysTick->CTRL=0x00;       
  SysTick->VAL =0X00;       	    
}  

void delay_us(u32 nus)
{		
  u32 temp;	    	 
  SysTick->LOAD=nus*fac_us;   		 
  SysTick->VAL=0x00;        
  SysTick->CTRL=0x01 ;      	 
  do
  {
          temp=SysTick->CTRL;
  }
  while((temp&0x01)&&(!(temp&(1<<16))));   
  SysTick->CTRL=0x00;       
  SysTick->VAL =0X00;        
}

u32 DWTDelay_Init(void){
   if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
      /* Disable TRC */
      CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000
      /* Enable TRC */
      CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000
      /* Disable clock cycle counter */
      DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
      /* Enable  clock cycle counter */
      DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

      /* Reset the clock cycle counter value */
      DWT->CYCCNT = 0;

      /* 3 NO OPERATION instructions */
      __ASM volatile ("NOP");
      __ASM volatile ("NOP");
      __ASM volatile ("NOP");
   }


   /* Check if clock cycle counter has started */
   return DWT->CYCCNT ? 0 : 1; // 0 - clock cycle counter started, 1 - clock cycle counter not started
}


