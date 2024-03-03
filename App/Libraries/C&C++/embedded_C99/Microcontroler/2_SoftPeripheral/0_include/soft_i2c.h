/*
MODE 0:
  +) Config:
    #define SI2C_CONFIG_SDA_0(IsSet)                SDA = IsSet
    #define SI2C_CONFIG_SCL_0(IsSet)                SCL = IsSet
    #define SI2C_CONFIG_SDA_MODE_0(IsOutput)        SDA_Mode(IsOutput)
    #define SI2C_READ_SDA_0()                       SDA
    #define SI2C_DELAY_0()                          //
  +) Declare:

  +) Using:
    void SI2C_Start_0();
    void SI2C_Stop_0();
    reg8 SI2C_WriteByte_0(const reg8 Data);
    reg8 SI2C_WriteBytes_0(const reg8 SlaveAddr, const reg8 DataAddr, const unsigned char __gptr *Data, reg8 Length);
    reg8 SI2C_ReadByte_0(const reg8 NACK);
    reg8 SI2C_ReadBytes_0(const reg8 SlaveAddr, const reg8 DataAddr, unsigned char *Buffer, reg8 Length);
MODE 1:
  +) Config:

  +) Declare:
    void SI2C_ConfigSDA(reg8 IsSet) { SDA = IsSet; }
    reg8 SI2C_ReadSDA() {return SDA; }
    void SI2C_ConfigSCL(reg8 IsSet) { SCL = IsSet; }
    void SI2C_ConfigSDAMode(reg8 IsOutput) {SDA_Mode(IsOutput); }
    void SI2C_Delay() {};
    const SI2CFunction_TypeDef SI2CFunction = {SI2C_ConfigSDA, SI2C_ReadSDA, SI2C_ConfigSCL, SI2C_ConfigSDAMode, SI2C_Delay};
  +) Using:
    void SI2C_Start_1(const SI2CFunction_TypeDef __gptr *SI2CFunction);
    void SI2C_Stop_1(const SI2CFunction_TypeDef __gptr *SI2CFunction);
    reg8 SI2C_WriteByte_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 Data);
    reg8 SI2C_WriteBytes_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 SlaveAddr, const reg8 DataAddr, const unsigned char __gptr *Data, reg8 Length);
    reg8 SI2C_ReadByte_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 NACK);
    reg8 SI2C_ReadBytes_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 SlaveAddr, const reg8 DataAddr, unsigned char *Buffer, reg8 Length);
*/
#ifndef _SOFT_I2C_H_
#define _SOFT_I2C_H_

#include <data_stream.h>
#include <common.h>
#include <define.h>
//                                      |       //Address       Default         Description
//==============================================================================================================================================================
//===========================================================       LEVEL 1      ===============================================================================
//==============================================================================================================================================================
typedef struct
{
  void (__code* ConfigSDA)(reg8 IsSet);
  reg8 (__code* ReadSDA)();
  void (__code* ConfigSCL)(reg8 IsSet);
  void (__code* ConfigSDAMode)(reg8 IsOutput);
  void (__code* Delay)();
} SI2CFunction_TypeDef;
//==============================================================================================================================================================
void SI2C_Start_0();
void SI2C_Stop_0();
reg8 SI2C_WriteByte_0(reg8 Data);
reg8 SI2C_WriteBytes_0(const reg8 SlaveAddr, const reg8 DataAddr, const unsigned char __gptr *Data, reg8 Length);
reg8 SI2C_ReadByte_0(const reg8 NACK);
reg8 SI2C_ReadBytes_0(const reg8 SlaveAddr, const reg8 DataAddr, unsigned char *Buffer, reg8 Length);
//==============================================================================================================================================================
void SI2C_Start_1(const SI2CFunction_TypeDef __gptr *SI2CFunction);
void SI2C_Stop_1(const SI2CFunction_TypeDef __gptr *SI2CFunction);
reg8 SI2C_WriteByte_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 Data);
reg8 SI2C_WriteBytes_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 SlaveAddr, const reg8 DataAddr, const unsigned char __gptr *Data, reg8 Length);
reg8 SI2C_ReadByte_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 NACK);
reg8 SI2C_ReadBytes_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 SlaveAddr, const reg8 DataAddr, unsigned char *Buffer, reg8 Length);
  
#endif