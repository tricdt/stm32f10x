#include <uart.h>
//==============================================================================================================================================================
#ifdef UART_DIRECT
  #define UART_MASK             UART_DIRECT
  #define FUNC_PARAM_MASK_0     
  #define FUNC_PARAM_MASK_1     
  extern __no_init volatile UART_TypeDef UART_DIRECT;
#else
  #define UART_MASK             (*UART)
  #define FUNC_PARAM_MASK_0     volatile UART_TypeDef* UART
  #define FUNC_PARAM_MASK_1     volatile UART_TypeDef* UART, 
#endif
//==============================================================================================================================================================
void UART_Init(FUNC_PARAM_MASK_1 const UARTInit_TypeDef* UARTInit)
{
#ifndef UART_BAUD
  #define UART_BAUD     UARTInit->Baudrate
#endif
  unsigned short baud = ((unsigned long)F_SYS * 10 + UART_BAUD - 1) / UART_BAUD;
  UART_MASK.BRR.r2 = ((baud >> 8) & 0xF0) | (baud & 0x0F);
  UART_MASK.BRR.r1 = baud >> 4;
  UART_MASK.CR2.REG = UARTInit->Mode.REG;
}
//==============================================================================================================================================================
void UART_WriteByte(FUNC_PARAM_MASK_1 unsigned char Data)
{
  while (!UART_MASK.SR.BITS.TXE);
  UART_MASK.DR = Data;
}
//==============================================================================================================================================================
void UART_WriteBytes(FUNC_PARAM_MASK_1 const unsigned char* Data, unsigned short Length)
{
  while (Length--)
  {
    while (!UART_MASK.SR.BITS.TXE);
    UART_MASK.DR = *Data++;
  }
}