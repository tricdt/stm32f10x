#include <common.h>
#include <spi.h>

void SPI_Init(volatile SPI_TypeDef* SPI, SPIInit_TypeDef* SPIInit)
{
  if (SPIInit->Mode.BITS.IsMaster)
    SPIInit->REG |= BIT14 | BIT9 | BIT18;
  else if (SPIInit->Mode.BITS.IsHalfDuplex)
    SPIInit->REG |= BIT10;
  SPI->CR2.REG = SPIInit->Interrupt.REG | SPIInit->DMA.REG;
  SPI->CR1.REG = SPIInit->REG | BIT6;
}

void SPI_Write(volatile SPI_TypeDef* SPI, unsigned long Data)
{
  *((unsigned char*)&SPI->DR) = Data;
  while (!SPI->SR.BITS.TXE);
}

void SPI_Write16(volatile SPI_TypeDef* SPI, unsigned long Data)
{
  SPI->DR = Data;
  while (!SPI->SR.BITS.TXE);
}

unsigned long SPI_Read(volatile SPI_TypeDef* SPI)
{
  while (!SPI->SR.BITS.RXNE);
  return SPI->DR;
}
unsigned long SPI_WriteRead(volatile SPI_TypeDef* SPI, unsigned long Data)
{
  SPI_Write(SPI, Data);
  return SPI_Read(SPI);
}

unsigned long SPI_WriteRead16(volatile SPI_TypeDef* SPI, unsigned long Data)
{
  SPI_Write16(SPI, Data);
  return SPI_Read(SPI);
}

void SPI_Writes(volatile SPI_TypeDef* SPI, unsigned char* Data, unsigned long Length)
{
  unsigned long index;
  for (index = 0; index < Length; index++)
  {
    SPI->DR = ((unsigned short*)Data)[index];
    while (!SPI->SR.BITS.TXE);
  }
}

void SPI_Write16s(volatile SPI_TypeDef* SPI, unsigned short* Data, unsigned long Length)
{
  unsigned long index;
  for (index = 0; index < Length; index++)
  {
    SPI->DR = ((unsigned short*)Data)[index];
    while (!SPI->SR.BITS.TXE);
  }
}

/*NOTE: pause spi bus (by Interrupt, usb,...) maybe get wrong rx data*/
void SPI_Reads(volatile SPI_TypeDef* SPI, unsigned char* Contain, unsigned long Length)
{
  while (SPI->SR.BITS.BSY)
  {
    if (SPI->SR.BITS.RXNE)
      SPI->DR;
  }  
  SPI->DR = 0x55AA;
  while (!SPI->SR.BITS.TXE);
  SPI->DR = 0x55AA;
  while (!SPI->SR.BITS.TXE);
  unsigned long index;
  for (index = 0; index < Length; index++)
  {
    SPI->DR = index;
    while (!SPI->SR.BITS.TXE);
    ((unsigned short*)Contain)[index] = SPI->DR;
  }
}

void SPI_WriteReads(volatile SPI_TypeDef* SPI, unsigned char* Contain, unsigned long Length)
{
  while (SPI->SR.BITS.BSY)
  {
    if (SPI->SR.BITS.RXNE)
      SPI->DR;
  }
  unsigned long index;
  for (index = 0; index < Length; index++)
  {
    SPI->DR = index;
    while (!SPI->SR.BITS.TXE);
    while (!SPI->SR.BITS.RXNE);
    ((unsigned short*)Contain)[index] = SPI->DR;
  }
}

void SPI_Read16s(volatile SPI_TypeDef* SPI, unsigned short* Contain, unsigned long Length)
{
  while (SPI->SR.BITS.BSY)
  {
    if (SPI->SR.BITS.RXNE)
      SPI->DR;
  }  
  SPI->DR = 0x55AA;
  while (!SPI->SR.BITS.TXE);
  SPI->DR = 0x55AA;
  while (!SPI->SR.BITS.TXE);
  unsigned long index;
  for (index = 0; index < Length; index++)
  {
    SPI->DR = index;
    while (!SPI->SR.BITS.TXE);
    ((unsigned short*)Contain)[index] = SPI->DR;
  }
}

void SPI_WriteRead46s(volatile SPI_TypeDef* SPI, unsigned short* Contain, unsigned long Length)
{
  while (SPI->SR.BITS.BSY)
  {
    if (SPI->SR.BITS.RXNE)
      SPI->DR;
  }
  unsigned long index;
  for (index = 0; index < Length; index++)
  {
    SPI->DR = index;
    while (!SPI->SR.BITS.TXE);
    while (!SPI->SR.BITS.RXNE);
    ((unsigned short*)Contain)[index] = SPI->DR;
  }
}