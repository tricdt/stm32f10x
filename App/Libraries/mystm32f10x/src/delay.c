
#include "mystm32f10x_delay.h"

static u8  fac_us=0;
static uint16_t fac_ms=0;


void delay_init(uint8_t SYSCLK)
{
  SysTick->CTRL&=0xfffffffb;
  fac_us = SYSCLK/8;
  fac_ms=(uint16_t)(fac_us*1000);
}

void delay_ms(uint32_t nms)
{	 		  	  
  uint32_t temp;		   
  SysTick->LOAD=(uint32_t)(nms*fac_ms);
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

void delay_us(uint32_t nus)
{		
  uint32_t temp;	    	 
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