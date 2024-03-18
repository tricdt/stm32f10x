/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               USART.c
** Descriptions:            USART����������
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

/* Private define ------------------------------------------------------------*/
#define USART_SEND_MAX_Q	  	(MEM_USART_BLK-4)	    /* �����ڴ���ڵ����ռ� */
#define USART_SEND_MAX_BOX		20	   					/* �����ڴ����������	*/
#define USART_RECV_MAX_Q	  	32						/* �ڴ���ڵ����ռ� */
#define ERR_NO_SPACE	        0xff					/* ������ */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
unsigned char Num;
unsigned char *Index;
}
USARTSendTcb;

/* Private variables ---------------------------------------------------------*/			
unsigned char USARTSendQBoxHost = 0;					/* �ڴ��ͷָ�� */							
unsigned char USARTSendQBoxTail = 0;					/* �ڴ��βָ�� */
unsigned int  USARTSendQFree = USART_SEND_MAX_BOX;   
unsigned char USARTSendOVF = 0; 						/* USART��������������־	*/
unsigned char USARTRunningFlag = 0;

USARTSendTcb USARTSendTCB[USART_SEND_MAX_BOX];

unsigned char USARTQRecvBuffer[USART_RECV_MAX_Q];		/* �����ڴ�� */	
unsigned char USARTRecvOVF=0; 							/* USART��������������־ */  
unsigned int Recv1Index=0x00;
unsigned int Recv1Count=0x00;
unsigned char USARTRecvFlag=0;

extern uint8_t USARTMemQ[MEM_USART_MAX];  		        /* �հ��ڴ�� */
extern MEMTcb* USARTIndex;

extern char *PYSearch(unsigned char *msg);

/*******************************************************************************
* Function Name  : USART_SendUpdate
* Description    : ���ṹ��������û�����ݻ�δ������ϣ���û�з��ͣ���������ͣ���������ϣ��˳�
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_SendUpdate(void)
{
	static unsigned char count = 0;
	
	if( USARTSendQFree == USART_SEND_MAX_BOX ) 
	{
	   return;
	}
	USART_StopSendISR();
	/* ������ڵ��ڴ������ݻ�û�з�����ϣ��������ͣ�Num��һ */
	if( (USARTSendTCB[USARTSendQBoxTail].Num) && (USARTSendQBoxTail != USARTSendQBoxHost) )
	{
		USARTSendTCB[USARTSendQBoxTail].Num--;
		USART_SendByte(*(USARTSendTCB[USARTSendQBoxTail].Index+count));
		count++;
	}
	/* һ�����Ϳ��Ѿ����������,USARTSendQFree++,βָ���һ��ָ����һ�����Ϳ�	*/
	else if( USARTSendQBoxTail != USARTSendQBoxHost )
	{		
		MemDelete(USARTIndex,USARTSendTCB[USARTSendQBoxTail].Index);
		if( ++USARTSendQBoxTail >= USART_SEND_MAX_BOX )  USARTSendQBoxTail = 0;
		if( ++USARTSendQFree >= USART_SEND_MAX_BOX )  USARTSendQFree = USART_SEND_MAX_BOX;
		count = 0;
		/* USARTSendQBoxTail����USARTSendQBoxTail��ʱ��ͱ�־�ⷢ�ͽ����ˣ�����ֱ���˳� */
		if( (USARTSendQBoxTail != USARTSendQBoxHost) )
//		if( (USARTSendTCB[USARTSendQBoxTail].Num) && (USARTSendQBoxTail != USARTSendQBoxHost) )
		{
			USARTSendTCB[USARTSendQBoxTail].Num--;
			USART_SendByte(*(USARTSendTCB[USARTSendQBoxTail].Index+count));
			count++;
		}
		else
		{	
		    /* USARTSendQBoxTail����USARTSendQBoxTail��ʱ��ͱ�־�ⷢ�ͽ����ˣ�����ֱ���˳� */
			USARTRunningFlag = 0;
			USARTSendQFree = USART_SEND_MAX_BOX;
			count = 0;
		}	
	}
	/* ����ͷָ��һֱ��ָ��յķ��Ϳ��,����USARTSendQBoxTail����USARTSendQBoxTail��ʱ��ͱ�־�ⷢ�ͽ�����,����ֱ���˳�*/ 
	else
	{
		USARTRunningFlag = 0;
		USARTSendQFree = USART_SEND_MAX_BOX;
		count = 0;
	}
	USART_StartSendISR();	
}

/*******************************************************************************
* Function Name  : USART_WriteDataToBuffer
* Description    : ��鷢�ͻ������Ĵ�С�����ռ��㹻���������͵����ݷ��뵽���ͻ�������ȥ,������������
* Input          : - buffer: �����͵����ݵ�ָ��
*				   - count: �����͵����ݵ�����
* Output         : None
* Return         : ����ȷ���뵽���ͻ�������ȥ�ˣ��ͷ���0x00	 �����򷵻�0x01
* Attention		 : None
*******************************************************************************/
unsigned char USART_WriteDataToBuffer(unsigned char *buffer,unsigned char count)
{
	unsigned char i=count;
	uint8_t err;

	/* �˴����Լ����źŵƻ��߹ر��ж� */
	if( count == 0 ) 
	{
	   return 0xff;
	}
	USART_StopSendISR();
	/* �������count��������Ҫ���ٸ��ڴ�� */
	if( count % USART_SEND_MAX_Q )
	{
	   count = count / USART_SEND_MAX_Q+1;
	}
	else 
	{
	   count = count / USART_SEND_MAX_Q;
	}
	/* ��Ҫcount�����ݿ� */
	/* ����ڴ治�㣬ֱ�ӷ��� */		 
	if(USARTSendQFree<count)
	{
	   USART_StartSendISR();
	   return ERR_NO_SPACE;
	}
	/* ���������ڴ�飬USARTSendQBoxHost����һ���ڴ������ż�һ */
	USARTSendTCB[USARTSendQBoxHost].Index = (uint8_t *)MemGet(USARTIndex,&err);
	if( USARTSendQBoxHost >= USART_SEND_MAX_BOX )
	{
	   USARTSendQBoxHost = 0;
	}	
	count = 0;
	while( i != '\0' )										 
	{
		*(USARTSendTCB[USARTSendQBoxHost].Index+count) = *buffer;
		count++;
		if( count >= USART_SEND_MAX_Q )
		{
			USARTSendTCB[USARTSendQBoxHost].Num = USART_SEND_MAX_Q;
			/* ��Ҫһ���µ��ڴ���Ž����������ݣ����Ը���USARTSendQBoxHost */
			if( ++USARTSendQBoxHost >= USART_SEND_MAX_BOX )
			{
			   USARTSendQBoxHost = 0;
			}
			/* ��Ҫһ���µ��ڴ���Ž����������� */	
			USARTSendTCB[USARTSendQBoxHost].Index = (uint8_t *)MemGet(USARTIndex,&err);
			/* �յķ���������һ */			
			USARTSendQFree--;
			count = 0;
		}
		buffer++;
		i--;
	}
	/* �˴�����δ�����������ݣ�����ҲҪ�����һ���µ��ڴ���� */
	if( count != 0 )
	{
		USARTSendTCB[USARTSendQBoxHost].Num = count; 
		USARTSendQFree--;
		if( ++USARTSendQBoxHost >= USART_SEND_MAX_BOX )
		{
		   USARTSendQBoxHost = 0;
		}
	}
	/* ����ǵ�һ�Σ����������ͣ�������Ѿ�������û�������Ҫ�� */
	if( USARTRunningFlag == 0 )
	{
#if	  	DMA_MODE
		USART_DMA_Configuration(USARTSendTCB[USARTSendQBoxTail].Index,USARTSendTCB[USARTSendQBoxTail].Num);
#else	
		USART_SendUpdate();
#endif		
		USARTRunningFlag=1;
	}
	/* �˴����Կ����źŵƻ��ߴ��ж� */
	USART_StartSendISR();
	return 0x00;
}

/*******************************************************************************
* Function Name  : USART_DispFun
* Description    : ��鷢�ͻ������Ĵ�С�����ռ��㹻���������͵����ݷ��뵽���ͻ���
*				   ����ȥ,������������,��USART_WriteDataToBuffer��ͬ���ǣ���������
*                  ����������Ҫָ���ļ���С�ģ���͸������ṩ�˷���
* Input          : - buffer: �����͵����ݵ�ָ��
* Output         : None
* Return         : ����ȷ���뵽���ͻ�������ȥ�ˣ��ͷ���0x00	 �����򷵻�0x01
* Attention		 : None
*******************************************************************************/
unsigned char USART_DispFun(unsigned char *buffer)
{
	unsigned long count = 0;
	while( buffer[count] != '\0' ) 
	{
	   count++;
	}
	return ( USART_WriteDataToBuffer(buffer,count) );
}

/*******************************************************************************
* Function Name  : USART_RecvResetBufferIndex
* Description    : ��������ʱ�жϵ�ʱ�򣬽����յ�ָ����㣬���ҹرռ�鳬ʱ��ʱ��
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_RecvResetBufferIndex(void)
{	
	static uint8_t PinYinIndex[6];
	static uint8_t Count=0xff;

	USART_WriteDataToBuffer(USARTQRecvBuffer ,Recv1Index);
	USART_StopCounter();
	Recv1Index=0;
	if( Count == 0xff )
	{
	   Count = 0;
	   return;
	}
	if( ((*USARTQRecvBuffer >= 'a') && (*USARTQRecvBuffer <= 'z')) || ((*USARTQRecvBuffer >= 'A') && (*USARTQRecvBuffer <= 'Z')) )
	{
		if( Count < 6 )
		{
			PinYinIndex[Count++] = *USARTQRecvBuffer ;
		}
		else 
		{
			USART_DispFun("\r\n");
			USART_DispFun( (uint8_t *)PYSearch(PinYinIndex) );
			USART_DispFun("\r\n");
			while(Count!=0)
			{
			   PinYinIndex[Count--] = 0;
			}		
		}		  
	}	
	else if( *USARTQRecvBuffer == '\r' )
	{
		if( Count != 0 )
		{
			USART_DispFun("\r\n");
			USART_DispFun( (uint8_t *)PYSearch(PinYinIndex) );
			USART_DispFun("\r\n");
			while(Count!=0)
			{
			   PinYinIndex[Count--] = 0;
			}
		}
	}
	else 
	{
		USART_DispFun("\r\n�����ƴ�����룬����������!\r\n");
		while( Count != 0 )
		{
		   PinYinIndex[Count--] = 0;	
		}
	}			
}

/*******************************************************************************
* Function Name  : USART_RecvFun
* Description    : �����յ�������һ֡�����Ժ�Ĵ�����
* Input          : - ptr: ���յ�������֡��ͷָ�룬���յ�������֡�����ݸ���
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_RecvFun(unsigned char *ptr,unsigned int count)
{
	USART_WriteDataToBuffer(ptr,8);
}

/*******************************************************************************
* Function Name  : USART_RecvUpdate
* Description    : ������յ�һ������
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/	
void USART_RecvUpdate(void)
{
	if( Recv1Index < Recv1Count )
	{
		USARTQRecvBuffer [Recv1Index++] = (unsigned char)USART_RecvByte();
		/* ֪�����յ�ָ������������	*/
		if( Recv1Index >= Recv1Count )
		{
			Recv1Index = 0;
			USART_StopCounter();
			USART_RecvFun(USARTQRecvBuffer ,Recv1Count);
		}
		if( USARTRecvFlag == 1 ) 
		{
		   USART_StartCounter();
		}	
		else 
		{
		   USART_StopCounter();
		}	
	}	
}

/*******************************************************************************
* Function Name  : USART_RecvData
* Description    : �����յ�������һ֡�����Ժ�Ĵ�����
* Input          : - count: Ҫ���յ���һ֡�������ݵĸ���
*				   - flag: 1������ʱ�ж�
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/		
unsigned char USART_RecvData(unsigned int count,unsigned char flag)
{
	if( count != 0 )
	{
		Recv1Count = count;
		USARTRecvFlag = flag;
		if( flag == 1 )
		{
		   USART_StartRecvISR();
		}
	}
	else if( count > USART_RECV_MAX_Q ) 
	{
	   return ERR_NO_SPACE;
	}
	return 0x00;
}

/*******************************************************************************
* Function Name  : USART_DMAUpdate
* Description    : USART_DMA����������
* Input          : None
*				   None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/	
void USART_DMAUpdate(void)
{
	if( USARTSendQBoxTail != USARTSendQBoxHost )
	{
		MemDelete(USARTIndex,USARTSendTCB[USARTSendQBoxTail].Index);
		if( ++USARTSendQBoxTail >= USART_SEND_MAX_BOX )
		{
		   USARTSendQBoxTail = 0;
		}
		if( ++USARTSendQFree >= USART_SEND_MAX_BOX )
		{
		   USARTSendQFree = USART_SEND_MAX_BOX;
		}
		if( USARTSendQBoxTail != USARTSendQBoxHost )
		{
			USART_DMA_Configuration(USARTSendTCB[USARTSendQBoxTail].Index,USARTSendTCB[USARTSendQBoxTail].Num);	
		}
		else 
		{
		   USARTRunningFlag = 0;	
		}
	}
	else 
	{		
		MemDelete(USARTIndex,USARTSendTCB[USARTSendQBoxTail].Index);
		if( ++USARTSendQBoxTail >= USART_SEND_MAX_BOX )
		{
		   USARTSendQBoxTail = 0;
		}
		if( ++USARTSendQFree >= USART_SEND_MAX_BOX )
		{
		   USARTSendQFree = USART_SEND_MAX_BOX;
		}
		USARTRunningFlag = 0;
	}	
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

