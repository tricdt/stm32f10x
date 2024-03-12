/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               USARTConfig.c
** Descriptions:            USART的底层配置函数
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

/* Includes ------------------------------------------------------------------*/	
#include "stm32f10x.h"
#include "USART.h"

/* Private define ------------------------------------------------------------*/
#define USART1_DR_Base  0x40013804

/*******************************************************************************
* Function Name  : USART_Pin_Configuration
* Description    : 配置 USART Tx Rx
* Input          : None
*				   None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_Pin_Configuration(void)
{	
   GPIO_InitTypeDef GPIO_InitStructure;	

   RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA ,ENABLE);
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
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configuration the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TIM_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* 配置 DMA通道4的中断，中断优先级别为1，响应级别为2 */
  NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=10;
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : USART_ClearCounter
* Description    : USART ClearCounter
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_ClearCounter(void)
{
	TIM_SetCounter(TIM2,0x0000);
}

/*******************************************************************************
* Function Name  : USART_StartCounter
* Description    : USART StartCounter
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_StartCounter(void)
{
	USART_ClearCounter();
	TIM_Cmd(TIM2, ENABLE);
}

/*******************************************************************************
* Function Name  : USART_StopCounter
* Description    : USART StopCounter
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_StopCounter(void)
{
	TIM_Cmd(TIM2, DISABLE); 
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 Handler.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		TIM_ClearFlag(TIM2,TIM_IT_Update);
		USART_RecvResetBufferIndex();
	}
}

/*******************************************************************************
* Function Name  : USART_RecvByte
* Description    : USART Receive Byte
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
unsigned int USART_RecvByte(void)
{
	return USART_ReceiveData(USART1);
}

/*******************************************************************************
* Function Name  : TIM_Configuration
* Description    : TIM_Configuration program.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TIM_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

  TIM_DeInit(TIM2);
  TIM_NVIC_Configuration();
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
  TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure); 
  TIM_TimeBaseInitStructure.TIM_Period=9999;
  TIM_TimeBaseInitStructure.TIM_Prescaler=71;	
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;	 
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

  TIM_OCStructInit(&TIM_OCInitStruct);
  TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_Timing;
  TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High; 
  TIM_OCInitStruct.TIM_Pulse=4999;
  TIM_OC1Init(TIM2,&TIM_OCInitStruct);
		
  TIM_SelectInputTrigger(TIM2,TIM_TS_ITR1);
  TIM_ARRPreloadConfig(TIM2,ENABLE);
	
  TIM_Cmd(TIM2, ENABLE); 
  USART_StopCounter();
}

/*******************************************************************************
* Function Name  : USART_NVIC_Configuration
* Description    : USART NVIC Configuration program.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* 配置 DMA通道4的中断，中断优先级别为1，响应级别为2 */
  NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configure USART
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_Configuration(unsigned long baud)
{	
  USART_InitTypeDef USART_InitStructure;	 

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);

  USART_Pin_Configuration();
  /* 配置 USART1 参数：115200波特率，一位停止位，八位数据位，无硬件控制 */
  USART_DeInit(USART1);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate=baud;
  USART_InitStructure.USART_WordLength=USART_WordLength_8b;
  USART_InitStructure.USART_StopBits=USART_StopBits_1;
  USART_InitStructure.USART_Parity=USART_Parity_No;
  USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; 
  USART_Init(USART1,&USART_InitStructure);
#if	DMA_MODE
#else
  USART_ITConfig(USART1,USART_IT_TC,ENABLE);	 	
#endif
  USART_NVIC_Configuration();
  USART_Cmd(USART1,ENABLE);
  TIM_Configuration();
}

/*******************************************************************************
* Function Name  : USART_SendByte
* Description    : USART SendByte
* Input          : - temp: USART发送的数据
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_SendByte(unsigned char temp)
{
	USART_SendData(USART1,temp);
}

/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : USART1_IRQHandler（USART1发送）中断函数通道
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART1_IRQHandler(void)
{
    static uint8_t Flag=0;
	
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
	{
	    USART_ClearFlag(USART1,USART_FLAG_RXNE);   /* TCIE,TE,RE */
		if(Flag)
		{			
			USART_RecvUpdate();
		}
	}
	if(USART_GetFlagStatus(USART1,USART_FLAG_TC)==SET)
	{
	    USART_ClearFlag(USART1,USART_FLAG_TC);    /* TCIE,TE,RE */
		if(Flag)
		{
			USART_SendUpdate();
		}
	}
	Flag=1;
}

/*******************************************************************************
* Function Name  : USART_StopSendISR
* Description    : 停止发送中断
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_StopSendISR(void)
{
	USART_ITConfig(USART1,USART_IT_TC,DISABLE);	  	
}

/*******************************************************************************
* Function Name  : USART_StartSendISR
* Description    : 开启发送中断
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_StartSendISR(void)
{
	USART_ITConfig(USART1,USART_IT_TC,ENABLE);		 
}

/*******************************************************************************
* Function Name  : USART_StopRecvISR
* Description    : 停止接收中断
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_StopRecvISR(void)
{
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
}

/*******************************************************************************
* Function Name  : USART_StartRecvISR
* Description    : 开启接收中断
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_StartRecvISR(void)
{
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

/*******************************************************************************
* Function Name  : USART_DMA_Configuration
* Description    : DMA Configuration
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_DMA_Configuration(uint8_t *TxBuffer1,uint16_t num)
{
    DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    /* DMA1 Channel4 (triggered by USART1 Tx event) Config */
    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)TxBuffer1;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = num;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DMA_Cmd(DMA1_Channel4, ENABLE);
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	USART_Cmd(USART1,ENABLE);
}

/*******************************************************************************
* Function Name  : DMA1_Channel4_IRQHandler
* Description    : DMA1_Channel4_IRQHandler（USART1发送）DMA函数通道
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC4)==SET)
	{
	    DMA_ClearFlag(DMA1_IT_TC4);   /* TCIE,TE,RE	*/		
		USART_DMAUpdate();
	}
}




	 


