/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The ID application function
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
#include <string.h>
#include <stdio.h>

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private function prototypes -----------------------------------------------*/
void GetLockCode(void);
void TIM_Configuration(void);
void GPIO_Configuration(void); 
void NVIC_Configuration(void);
void USART_Configuration(void);	
int SetLockCode(void);
int USART_Scanf(void);
int TryGetLockCode(void);


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
	GPIO_Configuration();	
	NVIC_Configuration();
	TIM_Configuration();  
	USART_Configuration();
	printf("******************************************************************\r\n");
    printf("*                                                                *\r\n");
	printf("*  Thank you for using HY-FireBull V1.0 Development Board ! ^_^  *\r\n");
	printf("*                                                                *\r\n");
	printf("******************************************************************\r\n");

	GetLockCode();		/*���м����㷨�õ�ID���� */
	if(TryGetLockCode()==ENABLE)
	{
		printf("��ϵͳ�����ַ���! \r\n");
		while(1);
	}
	else
	{
		printf("��ϵͳû�м�����! \r\n");
		/* ���򵽴���֮��,���Ǵ������ϵͳ�İ취,�����û����ɷ��� */
		/* ...................................................... */
	}

	printf("������������� code��CODE \r\n");
							   
    /* Infinite loop */
    while (1)
	{
	  while( !USART_Scanf() );	  /* ͨ�����ڷ��ͼ�������code��CODE ��HY-Smart,������������ */
	
	  if(SetLockCode()==ENABLE)
	  {
		printf("�Ѿ�Ϊ��ϵͳ���ü�����!�븴λϵͳ \r\n");
		while(1);
	  }
	  else
	  {
	    printf("���ü�����ʧ��! \r\n");
	  }
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
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD , ENABLE); 						 
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
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
  TIM_DeInit(TIM2);
  TIM_TimeBaseStructure.TIM_Period=2000;		 					/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
																	/* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
  TIM_TimeBaseStructure.TIM_Prescaler= (36000 - 1);				    /* ʱ��Ԥ��Ƶ��   ���磺ʱ��Ƶ��=72MHZ/(ʱ��Ԥ��Ƶ+1) */
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 			/* ������Ƶ */
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		/* ���ϼ���ģʽ */
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    /* �������жϱ�־ */
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM2, ENABLE);											/* ����ʱ�� */
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configuration the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
	 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : USART_Scanf
* Description    : USART Receive
* Input          : None
* Output         : None
* Return         : ����1�ɹ� ����0ʧ��
* Attention		 : None
*******************************************************************************/
int USART_Scanf(void)
{
  uint16_t index = 0;
  uint8_t tmp[4] = {0, 0, 0, 0};

  while (index <4)
  {
    /* Loop until RXNE = 1 */
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) ;
  
    tmp[index++] = (USART_ReceiveData(USART1));

	if( tmp[index - 1] == 0x0D ) { index--; continue; }
  }

  if ( !( memcmp(tmp,"code",4)==0 || memcmp(tmp,"CODE",4)==0 ) )
  {
	printf("������������� code��CODE \r\n");
    return DISABLE;
  }

  return ENABLE;
}


/* Private variables ---------------------------------------------------------*/
uint32_t CpuID[3];   /* CPUΨһID  96BIT */
uint32_t Lock_Code;

/* Private define ------------------------------------------------------------*/
#define LOCK_ADDR	0x0801F000		/* �����ֵĴ洢λ��Flashҳ�׵�ַ 128K */


/*******************************************************************************
* Function Name  : GetLockCode
* Description    : ���ü�����
* Input          : None
* Output         : None
* Return         : None
* Attention		 : һ���ڳ���ʼ��ʱ�����,��Ҫ�Ѽ���ģʽ���ӻ�������Ľ��˺���
*******************************************************************************/
void GetLockCode(void)
{
	/* ��ȡCPUΨһID */
	CpuID[0]=*(vu32*)(0x1ffff7e8);
	CpuID[1]=*(vu32*)(0x1ffff7ec);
	CpuID[2]=*(vu32*)(0x1ffff7f0);
	/* �����㷨,�ܼ򵥵ļ����㷨 */
	/* ��γ���Ƚ����ױ�����࣬�����Ҫ�����ӵļ��ܷ�ʽ��Ӧ�þ������Ⱪ¶IDλ�úͼ��ܹ�ʽ */
	Lock_Code=(CpuID[0]>>1)+(CpuID[1]>>2)+(CpuID[2]>>3);
}

/*******************************************************************************
* Function Name  : TryGetLockCode
* Description    : ��ȡ������
* Input          : None
* Output         : None
* Return         : ����1�ɹ� ����0ʧ��
* Attention		 : None
*******************************************************************************/
int TryGetLockCode(void)
{
	uint32_t CPUID;
	/* ��ȡ����λ */
	CPUID=*(vu32*)(LOCK_ADDR);
	if(CPUID!=Lock_Code)
	{
		return(DISABLE);
	}
	else
		return(ENABLE);
	
}

/*******************************************************************************
* Function Name  : SetLockCode
* Description    : ���ü�����
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int SetLockCode(void)
{
	uint32_t CPUID;

	/* ��ȡ����λ */
	CPUID=*(vu32*)(LOCK_ADDR);
	/* д����λ */
	if(CPUID!=Lock_Code)
	{
		FLASH_Unlock();
		if(CPUID!=0xffffffff)	/* ���Ҫд��ĵ�ַ�ǿ�,����Ҫˢ�� */
		{
			FLASH_ErasePage(LOCK_ADDR);
		}
		
		FLASH_ProgramWord(LOCK_ADDR,Lock_Code);
		FLASH_Lock();
		
		CPUID=*(vu32*)(LOCK_ADDR);
		if(CPUID==Lock_Code)
		{
			return(ENABLE);
		}
		else
			return(DISABLE);
	}
	else
	{
		return(ENABLE);
	}
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

