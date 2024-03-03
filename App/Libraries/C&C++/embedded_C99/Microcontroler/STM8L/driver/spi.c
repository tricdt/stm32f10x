#include <spi.h>
//==============================================================================================================================================================
#ifdef SPI_DIRECT
  #define SPI_MASK              SPI_DIRECT
  #define PROTOTYPE_0           
  #define PROTOTYPE_1           
  #define PARAM_0               
  #define PARAM_1               SPI
  extern __no_init volatile SPI_TypeDef SPI_MASK;
#else
  #define SPI_MASK              (*SPI)
  #define PROTOTYPE_0           volatile SPI_TypeDef* SPI
  #define PROTOTYPE_1           volatile SPI_TypeDef* SPI, 
  #define PARAM_0               SPI
  #define PARAM_1               SPI, 
#endif
//==============================================================================================================================================================
void SPI_Begin(PROTOTYPE_0)
{
  SPI_MASK.CR2.REG = BIT0 | BIT1;
  SPI_MASK.CR1.REG = BIT2 | BIT6;
}
void SPI_Write(PROTOTYPE_1 unsigned char Data)
{
  while (!SPI_MASK.SR.BITS.TXE);
  SPI_MASK.DR = Data;
}
//==============================================================================================================================================================
void SPI_Writes(PROTOTYPE_1 const unsigned char* Data, unsigned short Length)
{
  while (Length--)
  {
    while (!SPI_MASK.SR.BITS.TXE);
    SPI_MASK.DR = *Data++;
  }
}
//==============================================================================================================================================================
unsigned char SPI_WriteRead(PROTOTYPE_1 unsigned char Data)
{  
  SPI_MASK.DR = Data;
  while (!SPI_MASK.SR.BITS.TXE);
  while (!SPI_MASK.SR.BITS.RXNE);
  return SPI_MASK.DR;
}
//==============================================================================================================================================================
unsigned char SPI_Read(PROTOTYPE_0)
{
  while (!SPI_MASK.SR.BITS.RXNE);
  return SPI_MASK.DR;
}
//==============================================================================================================================================================
void SPI_Reads(PROTOTYPE_1 unsigned char* Buffer, unsigned short Length)
{
  while (Length--)
  {
    SPI_MASK.DR = 0xFF;
    while (!SPI_MASK.SR.BITS.TXE);
    while (!SPI_MASK.SR.BITS.RXNE);
    *Buffer++ = SPI_MASK.DR;
  }
}