#ifdef STM32F10X_MD


#include "mystm32f10x.h"
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
//#pragma data_alignment = 64

RCC_ClocksTypeDef RCC_ClockFreq;



volatile FlagStatus myTimer = 0;
void GPIO_Config(void);
u32 clk;
int main(void){
   
   SetSysClock();
   RCC_GetClocksFreq(&RCC_ClockFreq);
   GPIO_Config();
   GPIO_DeInit(LED_Port);
   //MyGPIO_Init(LED_Port, LED_Pin, LED_Mode, LED_Speed,LED_Bus);
// MyGPIO_Init(LED_Port, LED_Pin, LED_Mode, LED_Speed, 
   clk = RCC_ClockFreq.SYSCLK_Frequency;
  


//   MyTimer_Start(TIM1);
   //TIM2_Config();
  //TIM1_Config();
   while(1){
      //PCout(13) = 1;
     LED_ACTIVE;
      //DWTDelay_ms(100);
    delay_ms(100);
      //PCout(13) = 0;
      LED_IDLE;
      //DWTDelay_ms(100);
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


void TIM2_IRQHandler(void){
   
   if(TIM_GetFlagStatus(TIM2, TIM_IT_Update!=RESET))
   {
      MyGPIO_Toggle(LED_Port, 13);
      TIM_ClearFlag(TIM2, TIM_FLAG_Update);
   }
}
#endif
#ifdef STM32F10X_HD

/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GPIO LED application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-10-30
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"


/* Private functions ---------------------------------------------------------*/
void GPIO_Configuration(void);

/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay (uint32_t nCount)
{
 for(; nCount != 0; nCount--);
}


/*******************************************************************************
* Function Name  : main
* Description    : Main Programme
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
	GPIO_Configuration();
   /* Infinite loop */
   while (1){
     /*====LED-ON=======*/
	  GPIO_SetBits(GPIOC , GPIO_Pin_6);
	  GPIO_SetBits(GPIOC , GPIO_Pin_7);
	  GPIO_SetBits(GPIOD , GPIO_Pin_6);
	  GPIO_SetBits(GPIOD , GPIO_Pin_13);
	  Delay(0xfffff);
	  Delay(0xfffff);
	  /*====LED-OFF=======*/ 
	  GPIO_ResetBits(GPIOC , GPIO_Pin_6);
	  GPIO_ResetBits(GPIOC , GPIO_Pin_7);
	  GPIO_ResetBits(GPIOD , GPIO_Pin_6);
	  GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	  Delay(0xfffff);
	  Delay(0xfffff);			
   }
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configure GPIO Pin
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GPIO_Configuration(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
 
 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 						 
 /**
 *  LED1 -> PC6, LED2 -> PC7 LED3 -> PD13 , LED4 -> PD6
 */			
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; ; 
 GPIO_Init(GPIOC, &GPIO_InitStructure);
 
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD , ENABLE); 						 
 /**
 *  LED1 -> PC6, LED2 -> PC7 LED3 -> PD13 , LED4 -> PD6
 */				
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_13;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; ; 
 GPIO_Init(GPIOD, &GPIO_InitStructure);
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
 /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

 /* Infinite loop */
 while (1)
 {
 }
}
#endif

/*********************************************************************************************************
     END FILE
*********************************************************************************************************/

#endif


