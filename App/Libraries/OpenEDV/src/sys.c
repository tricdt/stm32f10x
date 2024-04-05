#include "sys.h"

///////////////////////////////////////////////////// ////////////////////////////////////
//This program is for learning only and may not be used for any other purpose without the author's permission.
//ALIENTEK STM32 development board
//System interrupt group setting
//On-point atom @ALIENTEK
//Technical Forum: www.openedv.com
//Modification date:2012/9/10
//Version: V1.4
//Copyright, piracy will be investigated.
//Copyright(C) Punctual Atom 2009-2019
//All rights reserved

//************************************************ *********************************

//THUMB instruction does not support assembly inlining
//Use the following method to implement the assembly instruction WFI
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}

//Close all interrupts
void INTX_DISABLE(void)
{		  
  __ASM volatile("cpsid i");
}

//Enable all interrupts
void INTX_ENABLE(void)
{
  __ASM volatile("cpsie i");		  
}


//Set the top address of the stack
//addr: top address of stack
// __asm ​​void MSR_MSP(u32 addr)
//{
// MSR MSP, r0 //set Main Stack value
// BX r14
//}

/* define compiler specific symbols */
#if defined ( __CC_ARM   )   /*!< asm keyword for ARM Compiler          */

void MSR_MSP(uint32_t addr)
{
  //__ASM volatile ("MSR MSP, r0");
  //__ASM volatile ("BX r14");
}
#elif defined ( __ICCARM__ )   /*!< asm keyword for IAR Compiler          */
void MSR_MSP(uint32_t addr)
{
  __ASM volatile ("MSR MSP, r0");
  __ASM volatile ("BX r14");
}

#elif defined   (  __GNUC__  ) /*!< asm keyword for GNU Compiler          */


#elif defined   (  __TASKING__  ) /*!< asm keyword for TASKING Compiler      */


#endif





