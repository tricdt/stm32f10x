/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               USART.c
** Descriptions:            USART的驱动函数
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
#define USART_SEND_MAX_Q	  	(MEM_USART_BLK-4)	    /* 发送内存块内的最大空间 */
#define USART_SEND_MAX_BOX		20	   					/* 发送内存块的最大数量	*/
#define USART_RECV_MAX_Q	  	32						/* 内存块内的最大空间 */
#define ERR_NO_SPACE	        0xff					/* 错误定义 */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
unsigned char Num;
unsigned char *Index;
}
USARTSendTcb;

/* Private variables ---------------------------------------------------------*/			
unsigned char USARTSendQBoxHost = 0;					/* 内存块头指针 */							
unsigned char USARTSendQBoxTail = 0;					/* 内存块尾指针 */
unsigned int  USARTSendQFree = USART_SEND_MAX_BOX;   
unsigned char USARTSendOVF = 0; 						/* USART发送任务块溢出标志	*/
unsigned char USARTRunningFlag = 0;

USARTSendTcb USARTSendTCB[USART_SEND_MAX_BOX];

unsigned char USARTQRecvBuffer[USART_RECV_MAX_Q];		/* 接收内存块 */	
unsigned char USARTRecvOVF=0; 							/* USART接收任务块溢出标志 */  
unsigned int Recv1Index=0x00;
unsigned int Recv1Count=0x00;
unsigned char USARTRecvFlag=0;

extern uint8_t USARTMemQ[MEM_USART_MAX];  		        /* 空白内存块 */
extern MEMTcb* USARTIndex;

extern char *PYSearch(unsigned char *msg);

/*******************************************************************************
* Function Name  : USART_SendUpdate
* Description    : 检查结构体里面有没有数据还未发送完毕，若没有发送，则继续发送，若发送完毕，退出
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
	/* 如果现在的内存块的数据还没有发送完毕，启动发送，Num减一 */
	if( (USARTSendTCB[USARTSendQBoxTail].Num) && (USARTSendQBoxTail != USARTSendQBoxHost) )
	{
		USARTSendTCB[USARTSendQBoxTail].Num--;
		USART_SendByte(*(USARTSendTCB[USARTSendQBoxTail].Index+count));
		count++;
	}
	/* 一个发送块已经发送完毕了,USARTSendQFree++,尾指针加一。指向下一个发送块	*/
	else if( USARTSendQBoxTail != USARTSendQBoxHost )
	{		
		MemDelete(USARTIndex,USARTSendTCB[USARTSendQBoxTail].Index);
		if( ++USARTSendQBoxTail >= USART_SEND_MAX_BOX )  USARTSendQBoxTail = 0;
		if( ++USARTSendQFree >= USART_SEND_MAX_BOX )  USARTSendQFree = USART_SEND_MAX_BOX;
		count = 0;
		/* USARTSendQBoxTail等于USARTSendQBoxTail的时候就标志这发送结束了，可以直接退出 */
		if( (USARTSendQBoxTail != USARTSendQBoxHost) )
//		if( (USARTSendTCB[USARTSendQBoxTail].Num) && (USARTSendQBoxTail != USARTSendQBoxHost) )
		{
			USARTSendTCB[USARTSendQBoxTail].Num--;
			USART_SendByte(*(USARTSendTCB[USARTSendQBoxTail].Index+count));
			count++;
		}
		else
		{	
		    /* USARTSendQBoxTail等于USARTSendQBoxTail的时候就标志这发送结束了，可以直接退出 */
			USARTRunningFlag = 0;
			USARTSendQFree = USART_SEND_MAX_BOX;
			count = 0;
		}	
	}
	/* 由于头指针一直是指向空的发送块的,所以USARTSendQBoxTail等于USARTSendQBoxTail的时候就标志这发送结束了,可以直接退出*/ 
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
* Description    : 检查发送缓冲区的大小，若空间足够，将待发送的数据放入到发送缓冲区中去,并且启动发送
* Input          : - buffer: 待发送的数据的指针
*				   - count: 待发送的数据的数量
* Output         : None
* Return         : 若正确放入到发送缓冲区中去了，就返回0x00	 ，否则返回0x01
* Attention		 : None
*******************************************************************************/
unsigned char USART_WriteDataToBuffer(unsigned char *buffer,unsigned char count)
{
	unsigned char i=count;
	uint8_t err;

	/* 此处可以加入信号灯或者关闭中断 */
	if( count == 0 ) 
	{
	   return 0xff;
	}
	USART_StopSendISR();
	/* 计算放入count个数据需要多少个内存块 */
	if( count % USART_SEND_MAX_Q )
	{
	   count = count / USART_SEND_MAX_Q+1;
	}
	else 
	{
	   count = count / USART_SEND_MAX_Q;
	}
	/* 需要count个数据块 */
	/* 如果内存不足，直接返回 */		 
	if(USARTSendQFree<count)
	{
	   USART_StartSendISR();
	   return ERR_NO_SPACE;
	}
	/* 首先申请内存块，USARTSendQBoxHost在下一个内存申请后才加一 */
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
			/* 需要一个新的内存块存放接下来的数据，所以更新USARTSendQBoxHost */
			if( ++USARTSendQBoxHost >= USART_SEND_MAX_BOX )
			{
			   USARTSendQBoxHost = 0;
			}
			/* 需要一个新的内存块存放接下来的数据 */	
			USARTSendTCB[USARTSendQBoxHost].Index = (uint8_t *)MemGet(USARTIndex,&err);
			/* 空的发送任务块减一 */			
			USARTSendQFree--;
			count = 0;
		}
		buffer++;
		i--;
	}
	/* 此处是尚未整块存完的数据，它们也要存放在一个新的内存块里 */
	if( count != 0 )
	{
		USARTSendTCB[USARTSendQBoxHost].Num = count; 
		USARTSendQFree--;
		if( ++USARTSendQBoxHost >= USART_SEND_MAX_BOX )
		{
		   USARTSendQBoxHost = 0;
		}
	}
	/* 如果是第一次，就启动发送，如果是已经启动就没有这个必要了 */
	if( USARTRunningFlag == 0 )
	{
#if	  	DMA_MODE
		USART_DMA_Configuration(USARTSendTCB[USARTSendQBoxTail].Index,USARTSendTCB[USARTSendQBoxTail].Num);
#else	
		USART_SendUpdate();
#endif		
		USARTRunningFlag=1;
	}
	/* 此处可以开启信号灯或者打开中断 */
	USART_StartSendISR();
	return 0x00;
}

/*******************************************************************************
* Function Name  : USART_DispFun
* Description    : 检查发送缓冲区的大小，若空间足够，将待发送的数据放入到发送缓冲
*				   区中去,并且启动发送,与USART_WriteDataToBuffer不同的是，启动发送
*                  函数世不需要指定文件大小的，这就给调用提供了方便
* Input          : - buffer: 待发送的数据的指针
* Output         : None
* Return         : 若正确放入到发送缓冲区中去了，就返回0x00	 ，否则返回0x01
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
* Description    : 当发生超时中断的时候，将接收的指针归零，并且关闭检查超时的时钟
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
		USART_DispFun("\r\n错误的拼音代码，请重新输入!\r\n");
		while( Count != 0 )
		{
		   PinYinIndex[Count--] = 0;	
		}
	}			
}

/*******************************************************************************
* Function Name  : USART_RecvFun
* Description    : 当接收到完整的一帧数据以后的处理函数
* Input          : - ptr: 接收到的数据帧的头指针，接收到的数据帧的数据个数
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
* Description    : 处理接收到一个数据
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
		/* 知道接收到指定数量的数据	*/
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
* Description    : 当接收到完整的一帧数据以后的处理函数
* Input          : - count: 要接收到的一帧数据数据的个数
*				   - flag: 1开启超时中断
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
* Description    : USART_DMA的驱动函数
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

