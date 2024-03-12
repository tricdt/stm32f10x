/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            本实验进入停止模式方式，并使用User Button来唤醒
**                          注意：进入停止模式可能会导致调试工具不能下载。
**                          解决方法：不断按User Button唤醒CPU，并同时下载。
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
#include <stdio.h>


/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void EXTI_Configuration(void);


/*******************************************************************************
* Function Name  : Delay
* Description    : 延迟函数 
* Input          : - cnt: delay time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/  
void Delay(vu16 cnt)
{
  uint16_t i,j;
  for (i=0;i<cnt;i++)
   for (j=0;j<1000;j++); 
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
	SystemInit();
	NVIC_Configuration();
	GPIO_Configuration();
	EXTI_Configuration();
    /* Infinite loop */
    while (1)
	{
        /*====LED-ON=======*/
	    GPIO_SetBits(GPIOD , GPIO_Pin_8);
	    GPIO_SetBits(GPIOD , GPIO_Pin_9);
	    GPIO_SetBits(GPIOD , GPIO_Pin_10);
	    GPIO_SetBits(GPIOD , GPIO_Pin_11);
		Delay(1000);

	    /*====LED-OFF=======*/ 
	    GPIO_ResetBits(GPIOD , GPIO_Pin_8);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_9);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_10);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_11);
        Delay(1000);

        /*====LED-ON=======*/
	    GPIO_SetBits(GPIOD , GPIO_Pin_8);
	    GPIO_SetBits(GPIOD , GPIO_Pin_9);
	    GPIO_SetBits(GPIOD , GPIO_Pin_10);
	    GPIO_SetBits(GPIOD , GPIO_Pin_11);
		Delay(1000);

	    /*====LED-OFF=======*/ 
	    GPIO_ResetBits(GPIOD , GPIO_Pin_8);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_9);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_10);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_11);
        Delay(1000);

        PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);  /* 进入停止模式 */

        /*====LED-ON=======*/
	    GPIO_SetBits(GPIOD , GPIO_Pin_8);
	    GPIO_SetBits(GPIOD , GPIO_Pin_9);
	    GPIO_SetBits(GPIOD , GPIO_Pin_10);
	    GPIO_SetBits(GPIOD , GPIO_Pin_11);
		Delay(1000);

	    /*====LED-OFF=======*/ 
	    GPIO_ResetBits(GPIOD , GPIO_Pin_8);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_9);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_10);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_11);
        Delay(1000);

        /*====LED-ON=======*/
	    GPIO_SetBits(GPIOD , GPIO_Pin_8);
	    GPIO_SetBits(GPIOD , GPIO_Pin_9);
	    GPIO_SetBits(GPIOD , GPIO_Pin_10);
	    GPIO_SetBits(GPIOD , GPIO_Pin_11);
		Delay(1000);

	    /*====LED-OFF=======*/ 
	    GPIO_ResetBits(GPIOD , GPIO_Pin_8);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_9);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_10);
	    GPIO_ResetBits(GPIOD , GPIO_Pin_11);
        Delay(1000);
    }
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD , ENABLE); 						 
  /**
  *  User Button -> PA8 
  */				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /**
  *  LED1 -> PD8 , LED2 -> PD9 , LED3 -> PD10 , LED4 -> PD11
  */			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; ; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}


/*******************************************************************************
* Function Name  : EXTI_Configuration
* Description    : Configures the different EXTI lines.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void EXTI_Configuration(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);	   /* PA8连接到外部中断通道8 */
  EXTI_ClearITPendingBit(EXTI_Line8);

  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_Line = EXTI_Line8 ;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;   
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	      
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
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
