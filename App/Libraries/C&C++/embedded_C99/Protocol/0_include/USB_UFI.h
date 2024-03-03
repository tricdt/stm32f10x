#ifndef _USB_UFI_H_
#define _USB_UFI_H_

#include <common.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef enum
{
  UFI_COMMAND_FORMAT_UNIT               = 0x04,
  UFI_COMMAND_INQUIRY                   = 0x12,
  UFI_COMMAND_MODE_SELECT6              = 0x15,
  UFI_COMMAND_MODE_SELECT10             = 0x55,
  UFI_COMMAND_MODE_SENSE6               = 0x1A,
  UFI_COMMAND_MODE_SENSE10              = 0x5A,
  UFI_COMMAND_ALLOW_MEDIUM_REMOVAL      = 0x1E,
  UFI_COMMAND_READ6                     = 0x08,
  UFI_COMMAND_READ10                    = 0x28,
  UFI_COMMAND_READ12                    = 0xA8,
  UFI_COMMAND_READ16                    = 0x88,
  
  UFI_COMMAND_READ_CAPACITY10           = 0x25,
  UFI_COMMAND_READ_CAPACITY16           = 0x9E,
  
  UFI_COMMAND_REQUEST_SENSE             = 0x03,
  UFI_COMMAND_START_STOP_UNIT           = 0x1B,
  UFI_COMMAND_TEST_UNIT_READY           = 0x00,
  UFI_COMMAND_WRITE6                    = 0x0A,
  UFI_COMMAND_WRITE10                   = 0x2A,
  UFI_COMMAND_WRITE12                   = 0xAA,
  UFI_COMMAND_WRITE16                   = 0x8A,

  UFI_COMMAND_VERIFY10                  = 0x2F,
  UFI_COMMAND_VERIFY12                  = 0xAF,
  UFI_COMMAND_VERIFY16                  = 0x8F,
  
  UFI_COMMAND_SEND_DIAGNOSTIC           = 0x1D,
  UFI_COMMAND_READ_FORMAT_CAPACITIES    = 0x23,
} UFI_COMMAND;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                      |       //Address       Default         Description
__packed typedef struct
{
  UFI_COMMAND Command;
  unsigned char Info;                           //                              LUN usually at 3 bit high, refer doccument for special bits
  __packed union
  {
    RSTRUCT(INQUIRY, unsigned char,
      _reserved                         [2],
      _AllocationLength                    ,    //              0x24
      _reserved1                        [11]);
    RSTRUCT(, unsigned char,
      LogicalBlockAddress               [4],    //                              MSB
      _reserved                            ,
      Length                            [2],    //                              MSB
      _reserved1                        [7])
      READ_10, WRITE_10, VERIFY;
    RSTRUCT(REQUEST_SENSE, unsigned char,
      _reserved                         [2],
      AllocationLength                     ,    //              18
      _reserved1                        [11]);
    RSTRUCT(, unsigned char,
      _reserved1                        [14])
      TEST_UNIT_READY, READ_CAPACITY;
    RSTRUCT(MODE_SENSE_10, unsigned char,
      PageCode                             ,    //                              6 bit low is used
      _reserved                         [4],
      ParameterListLength               [2],    //                              MSB
      _reserved1                        [7]);
    RSTRUCT(MODE_SENSE_6, unsigned char,
      PageCode                          ,       //                              6 bit low is used
      SubPageCode                       ,
      AllocationLength                  ,
      Control                           );
    RSTRUCT(FORMAT_UNIT, unsigned char,
      VendorSpecific                       ,
      Interleave                        [2],    //                              MSB
      _reserved1                        [11]);
    RSTRUCT(READ_TOC, unsigned char,
      FormatA                              ,
      _reserved                         [4],
      AllocationLength                  [2],    //                              MSB
      _reserved1                        [7]);
    RSTRUCT(READ_FORMAT_CAPACITIES, unsigned char,
      _reserved                         [5],
      AllocationLength                  [2],    //                              MSB
      _reserved1                        [7]);
  };
} USB_UFI_Command_TypeDef;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef union
{
  RSTRUCT(INQUIRY, unsigned char,
    PeripheralDeviceType                   ,    //                              Identifies the device currently connected to the requested logical unit, 5 bit low is used
                                                //                                      0x00: SBC Direct-access device (e.g., UHD Floppy disk)
                                                //                                      0x05: CD-ROM device
                                                //                                      0x07:  Optical memory device (e.g., Non-CD optical disks)
                                                //                                      0x0E:  RBC Direct-access device (e.g., UHD Floppy disk)
    RMB                                    ,    //                              Removable Media Bit: this shall be set to one to indicate removable media at bit 7
    _reserved                           [2],    //              [0x00, 0x01]
    _AdditionalLength                      ,    //              0x1F
    _reserved1                          [3],
    VendorIdentification                [8],    //                              ASCII data identifying the vendor of the product
    ProductIdentification               [16],   //                              ASCII data as defined by the vendor
    ProductRevisionLevel                [4]);   //                              ASCII data as defined by the vendor
  struct
  {
    BUNION(Status, unsigned char,
      ErrorCode                         , 7,    //                              0x70 or 0x71
      Valid                             , 1);
    unsigned char _SegmentNumber;
    BUNION(Info, unsigned char,
      SenseKey                          , 4,
      _reserved                         , 1,
      ILI                               , 1,
      _reserved1                        , 2);
    REGS(unsigned char,
      Information                       [4],
      AdditionalSenseLength                ,    //                              (n - 7)
      CommandSpecificInfo               [4],
      AdditionalSenseCode                  ,
      AdditionalSenseCodeQualifier         );
      //_reserved[n]);
  } REQUEST_SENSE;
  RSTRUCT(READ_CAPACITY, unsigned char,
    LastLogicalBlockAddress             [4],    //                              MSB
    BlockLength                         [4]);   //                              MSB (in bytes)
    RSTRUCT(READ_FORMAT_CAPACITIES, unsigned char,
      _reserved                         [3],
      CapacityListLength                   ,    //                              = block size / max packet usb bus size
      NumberOfBlocks                    [4],    //                              MSB, note sub by 1
      DescriptorCode                       ,    //                              0x01: Unformatted Media - Maximum formattable capacity for this cartridge
                                                //                              0x02: Formatted Media - Current media capacity
                                                //                              0x03: No Cartridge in Drive - Maximum formattable capacity for any cartridge
      BlockLength                       [3]);   //                              MSB
//  RSTRUCT(ReadTOC, unsigned char,
//    TOCDataLength                       [2],    //              0x0A            MSB
//    FirstCompleteSessionNumber             ,
//    LastCompleteSessionNumber              ,
//    _reserved                           [2],
//     FirstTrackNumber                      ,
//    _reserved                              ,
//    LogicalBlockAddress                 [4]);   //                              MSB
  RSTRUCT(UFI_COMMAND_REQUEST_SENSE, unsigned char,
    ErrorCode                           ,       //              0x70|Valid      Valid: bit 7
    _reserved                           ,
    SenseKey                            ,
    Information                         [4],    //                              MSB
    AdditionalSenseLength               ,       //              10
    _reserved1                          [4],
    AdditionalSenseCode                 ,
    AdditionalSenseCodeQualifier        ,
    _reserved2                          [4]);
} USB_UFI_Respond_TypeDef;

#endif