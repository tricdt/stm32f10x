/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            ������ʾUSART��ƴ�����뷨
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
#include "Mem.h"	
#include "USART.h"

/* Private variables ---------------------------------------------------------*/			
MEMTcb* USARTIndex;
extern uint8_t USARTMemQ[MEM_USART_MAX];  			/* �հ��ڴ�� */


/*******************************************************************************
* Function Name  : DelayMs
* Description    : Delay Time
* Input          : - N: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void DelayMs(unsigned long N)
{
	long count=14200;
	while(N)
	{
		count=14200;
		while(count--);
		N--;
	}
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
 	/* ���ò����� */
	USART_Configuration(115200);
	/* �����ڴ�������� */
	USARTIndex = (MEMTcb *)MemCreate(USARTMemQ,MEM_USART_BLK,MEM_USART_MAX/MEM_USART_BLK);
	DelayMs(10);
	/* ��ӭ����	*/
	USART_DispFun("*****************************************************************\r\n");
    USART_DispFun("*                                                               *\r\n");
	USART_DispFun("*  Thank you for using HY-STM32-Series Development Board ��^_^  *\r\n");
	USART_DispFun("*                                                               *\r\n");
	USART_DispFun("*****************************************************************\r\n");
	DelayMs(100);	/* ������գ���������ֽڣ��������ճ�ʱ�ж� */
	USART_RecvData(6,1);
	USART_DispFun("������ƴ��!\r\n");
  	while (1)
  	{
		DelayMs(100);
	}
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
