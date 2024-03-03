#include <spi.h>
#include <n76e003.h>

void SPI1_Init(SPIInit_TypeDef SPIInit)
{
  SPCR.REG = 0;
  SPSR.REG = 0x08;
  SPCR.REG = SPIInit.Mode.REG | SPIInit.Type | BIT6;
}
void SPI1_WriteByte(unsigned char Data)
{
  while (SPSR.BITS.TXBUF);
  SPDR = Data;
}
void SPI1_WriteBytes(const unsigned char __gptr* Data, unsigned char Length)
{
  while (Length--)
  {
    while (SPSR.BITS.TXBUF);
    SPDR = Data[0];
    Data++;
  }
}
void SPI1_WriteCodeBytes(const unsigned char __code* Data, unsigned char Length)
{
  while (Length--)
  {
    while (SPSR.BITS.TXBUF);
    SPDR = Data[0];
    Data++;
  }
}
void SPI1_WriteXdataBytes(const unsigned char __xdata* Data, unsigned char Length)
{
  while (Length--)
  {
    while (SPSR.BITS.TXBUF);
    SPDR = Data[0];
    Data++;
  }
}
void SPI1_WriteDataBytes(const unsigned char __data* Data, unsigned char Length)
{
  while (Length--)
  {
    while (SPSR.BITS.TXBUF);
    SPDR = Data[0];
    Data++;
  }
}