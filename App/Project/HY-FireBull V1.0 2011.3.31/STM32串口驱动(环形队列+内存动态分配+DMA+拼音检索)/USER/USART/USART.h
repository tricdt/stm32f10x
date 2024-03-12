/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               USART.h
** Descriptions:            The USART application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Ya Dan
** Created date:            2011-1-18
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

#ifndef  __USART_H
#define  __USART_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private define ------------------------------------------------------------*/
#define		DMA_MODE 		1 		/* 定义是采用DMA模式，还是普通的中断模式 */

/* 注意在串口接收的时候是打开了定时器 */
/* 其中：USART1-------TIM2 */
/* 其中：USART2-------TIM3 */
/* 其中：USART3-------TIM4 */
/* 其中：USART4-------TIM5 */
/* 其中：USART5-------TIM6 */

/* Private function prototypes -----------------------------------------------*/
void USART_DMAUpdate(void);
void USART_SendUpdate(void);
void USART_RecvUpdate(void);
void USART_StopCounter(void);
void USART_StopSendISR(void);
void USART_StartSendISR(void);
void USART_StartCounter(void);
void USART_StartRecvISR(void);
unsigned int USART_RecvByte(void);
void USART_RecvResetBufferIndex(void);
void USART_SendByte(unsigned char temp);
void USART_Configuration(unsigned long baud);
unsigned char USART_DispFun(unsigned char *buffer);	 
void USART_DMA_Configuration(uint8_t *TxBuffer1,uint16_t num);
unsigned char USART_RecvData(unsigned int count,unsigned char flag);
unsigned char USART_WriteDataToBuffer(unsigned char *buffer,unsigned char count);

#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
