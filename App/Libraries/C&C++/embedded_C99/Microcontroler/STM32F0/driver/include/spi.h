#ifndef _SPI_H_
#define _SPI_H_

#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CR1, unsigned long,                    //              0x0000'0000     SPI control register 1 (not used in I2S mode)
    CPHA                                , 1,    //0             0               Clock phase
    CPOL                                , 1,    //1             0               Clock polarity
    MSTR                                , 1,    //2             0               Master selection
    BR                                  , 3,    //3:5           0               Baud rate control
    SPE                                 , 1,    //6             0               SPI enable
    LSBFIRST                            , 1,    //7             0               Frame format
    SSI                                 , 1,    //8             0               longernal slave select
    SSM                                 , 1,    //9             0               Software slave management
    RXONLY                              , 1,    //10            0               Receive only
    CRCL                                , 1,    //11            0               CRC length0: 8 bit, 1: 16 bit
    CRCNEXT                             , 1,    //12            0               CRC transfer next
    CRCEN                               , 1,    //13            0               Hardware CRC calculation enable
    BIDIOE                              , 1,    //14            0               Output enable in bidirectional mode
    BIDIMODE                            , 1,    //15            0               Bidirectional data mode enable
    _reserved                           , 16);
  BUNION(CR2, unsigned long,                    //              0x0000'0000     SPI control register 2
    RXDMAEN                             , 1,    //0             0               Rx buffer DMA enable
    TXDMAEN                             , 1,    //1             0               Tx buffer DMA enable
    SSOE                                , 1,    //2             0               SS output enable
    NSSP                                , 1,    //3             0               NSS pulse management
    FRF                                 , 1,    //4,            0               Frame format: 0: Motorola mode, 1: TI mode
    ERRIE                               , 1,    //5             0               Error longerrupt enable
    RXNEIE                              , 1,    //6             0               RX buffer not empty longerrupt enable
    TXEIE                               , 1,    //7             0               Tx buffer empty longerrupt enable
    DS                                  , 4,    //8:11          7               Data size = DS + 1, min: 4
    FRXTH                               , 1,    //12            0               FIFO reception threshold
    LDMA_RX                             , 1,    //13            0               Last DMA transfer for reception
    LDMA_TX                             , 1,    //14            0               Last DMA transfer for transmission
    _reserved1                          , 17);
  BUNION(SR, unsigned long,                     //              0x0000'0002     SPI status register
    const RXNE                          , 1,    //0             0               Receive buffer not empty
    const TXE                           , 1,    //1             1               Transmit buffer empty
    _reserved                           , 2,
    CRCERR                              , 1,    //4             0               CRC error flag
    const MODF                          , 1,    //5             0               Mode fault
    const OVR                           , 1,    //6             0               Overrun flag
    const BSY                           , 1,    //7             0               Busy flag
    const FRE                           , 1,    //8             0               Frame format error
    const FRLVL                         , 2,    //9-10          0               FIFO reception level
    const FTLVL                         , 2,    //11-12         0               FIFO Transmission Level
    _reserved1                          , 19);
  unsigned long DR;                             //              0x0000'0000     SPI data register
  unsigned long CRCPR;                          //              0x0000'0007     SPI CRC polynomial register (SPI_CRCPR) (not used in I2S mode)
  unsigned long const RXCRCR;                   //              0x0000'0000     SPI RX CRC register (SPI_RXCRCR) (not used in I2S mode)
  unsigned long const TXCRCR;                   //              0x0000'0000     SPI TX CRC register (SPI_TXCRCR) (not used in I2S mode)
} SPI_TypeDef;
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
typedef union
{
  unsigned long REG;
  struct
  {
    BUNION(Mode, unsigned short,
      Phase                             , 1,    //0             0
      Polarity                          , 1,    //1             0
      IsMaster                          , 1,    //2             1
      Baudrate_Div                      , 3,    //3:5           2               Baud rate = (F-SPI / (2^(Baudrate_Div + 1))) (MAX 18MHz)
      _reserved                         , 1,
      IsLowBitFirst                     , 1,    //7             0
      _reserved1                        , 7,
      IsHalfDuplex                      , 1);   //15            0
    BUNION(DMA, unsigned char,
      Rx                                , 1,    //0             0
      Tx                                , 1,    //1             0
      _reserved                         , 6);
    BUNION(Interrupt, unsigned char,
      _reserved                         , 5,
      Error                             , 1,    //5             0
      Rx_NotEmpty                       , 1,    //6             0
      Tx_Empty                          , 1);   //7             0
  };
} SPIInit_TypeDef;
/*
+) EXAMPLE:     default data size is 8 bit, if wanna another, config CR2.DS
RCC_BITBAND.APB2_ENR.SPI1 = 1;
SPIInit_TypeDef SPIInit = (SPIInit_TypeDef){
  .Mode = {.BITS = {.Phase = 0, .Polarity = 0, .IsMaster = 1, .Baudrate_Div = 2, .IsLowBitFirst = 0, .IsHalfDuplex = 0, }, },  //F_SPI = F_BUS / 2 ^ (Baudrate_Div + 1) (MAX 18MHz)
  .DMA = {.BITS = {  .Rx = 0, .Tx = 0, }, }, 
  .longerrupt = {.BITS = {  .Error = 0, .Rx_NotEmpty = 0, .Tx_Empty = 0, }, }, 
};
SPI_Init(&SPI1, &SPIInit);
*/
void SPI_Init(volatile SPI_TypeDef* SPI, SPIInit_TypeDef* SPIInit);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define SPI_Wait(SPI)   while((SPI)->SR.BITS.BSY)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void SPI_Write(volatile SPI_TypeDef* SPI, unsigned long Data);                   //Data: 8 bit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void SPI_Write16(volatile SPI_TypeDef* SPI, unsigned long Data);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long SPI_Read(volatile SPI_TypeDef* SPI);                              //return: 8 bit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long SPI_WriteRead(volatile SPI_TypeDef* SPI, unsigned long Data);     //Data: 8 bit, return: 8 bit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long SPI_WriteRead16(volatile SPI_TypeDef* SPI, unsigned long Data);   //Data: 16 bit, return: 16 bit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void SPI_Writes(volatile SPI_TypeDef* SPI, unsigned char* Data, unsigned long Length);          //Length: 16 bit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void SPI_Write16s(volatile SPI_TypeDef* SPI, unsigned short* Data, unsigned long Length);       //Length: 16 bit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Read fast
+) NOTE: pause spi bus (by longerrupt, usb,...) maybe get wrong rx data
*/
void SPI_Reads(volatile SPI_TypeDef* SPI, unsigned char* Contain, unsigned long Length);                //Length: 16 bit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void SPI_WriteReads(volatile SPI_TypeDef* SPI, unsigned char* Contain, unsigned long Length);           //Length: 16 bit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void SPI_Read16s(volatile SPI_TypeDef* SPI, unsigned short* Contain, unsigned long Length);             //Length: 16 bit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void SPI_WriteRead16s(volatile SPI_TypeDef* SPI, unsigned short* Contain, unsigned long Length);        //Length: 16 bit


#endif