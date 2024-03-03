#ifndef _SPI_H_
#define _SPI_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  unsigned char Type;                           //                              BIT4: master, BIT4: slave
  BUNION(Mode, unsigned char,
    ClockRate                           , 2,    //0-13                          0: 8MHz, 1: 4MHz, 2: 2MHz, 3: 1MHz
    Phase                               , 1,    //23
    Pol                                 , 1,    //3
    _reserved                           , 1,
    IsLSB                               , 1,    //5
    _reserved1                          , 2);
} SPIInit_TypeDef;
/*
  Example:
  SPIInit_TypeDef SPIInit = {
    .Type = BIT4,
    .Mode = {.BITS = { .ClockRate = 0, .Phase = 0, .Pol = 0, .IsLSB = 0, },},
  };
  SPI1_Init(SPIInit);
*/
void SPI1_Init(SPIInit_TypeDef SPIInit);
void SPI1_WriteByte(const unsigned char Data);
void SPI1_WriteBytes(const unsigned char __gptr* Data, unsigned char Length);
void SPI1_WriteCodeBytes(const unsigned char __code* Data, unsigned char Length);
void SPI1_WriteXdataBytes(const unsigned char __xdata* Data, unsigned char Length);
void SPI1_WriteDataBytes(const unsigned char __data* Data, unsigned char Length);

#endif