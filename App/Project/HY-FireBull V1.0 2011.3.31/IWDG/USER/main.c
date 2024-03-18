/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            IWDG���ڿ��Ź�ʵ��
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
#include "systick.h"
#include <stdio.h>

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);
void IWDG_Configuration(void);
void USART_Configuration(void);


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
  delay_init();
  GPIO_Configuration();
  IWDG_Configuration(); 
  USART_Configuration();
  printf("******************************************************************\r\n");
  printf("*                                                                *\r\n");
  printf("*  Thank you for using HY-FireBull V1.0 Development Board ! ^_^  *\r\n");
  printf("*                                                                *\r\n");
  printf("******************************************************************\r\n");
												  
  /* System Reset */
  if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)  /* ���ϵͳ��Ϊ���Ź���λ */
  {	
     printf("IWDG RESET \r\n");
	 RCC_ClearFlag();
  }

  /* Infinite loop */
  while(1)
  {
    /*====LED-ON=======*/
	GPIO_SetBits(GPIOD , GPIO_Pin_8);
	GPIO_SetBits(GPIOD , GPIO_Pin_9);
	GPIO_SetBits(GPIOD , GPIO_Pin_10);
	GPIO_SetBits(GPIOD , GPIO_Pin_11);
    delay_ms(500); /* delay 500ms */ 

	/*====LED-OFF=======*/ 
	GPIO_ResetBits(GPIOD , GPIO_Pin_8);
	GPIO_ResetBits(GPIOD , GPIO_Pin_9);
	GPIO_ResetBits(GPIOD , GPIO_Pin_10);
	GPIO_ResetBits(GPIOD , GPIO_Pin_11);
    delay_ms(500); /* delay 500ms */

    if( !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) )   /* User Button */
    {
	   	delay_ms(20);                           /* ���������� */
		if( !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) )
		IWDG_ReloadCounter();	   /* ι�� */
    }	
  }
}

/*******************************************************************************
* Function Name  : IWDG_Configuration
* Description    : ���Ź�����
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void IWDG_Configuration(void)
{
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); 	/* д��0x5555,�����������Ĵ���д�빦�� */
  IWDG_SetPrescaler(IWDG_Prescaler_256);            /* �ڲ�����ʱ��256��Ƶ 40K/256=156HZ(6.4ms) */ 
  /* ���Ź���ʱ�����ʱ�� */
  IWDG_SetReload(781);							    /* ι��ʱ�� 5s/6.4MS=781 .ע�ⲻ�ܴ���0xfff*/
  IWDG_ReloadCounter();								/* ι��*/
  IWDG_Enable(); 									/* ʹ�ܿ��Ź�*/
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
* Function Name  : USART_Configuration
* Description    : Configure USART1 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_Configuration(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
  /*
  *  USART1_TX -> PA9 , USART1_RX ->	PA10
  */				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);		   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
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
