/*

*/

#ifndef _RX8025_H_
#define _RX8025_H_

#define RX8025_I2C_ADDRESS      0x64

#include <date_time.h>
#include <common.h>
#include <soft_i2c.h>

reg8 RX8025_Init_0();
reg8 RX8025_Read_0(DateTime_TypeDef* DateTime);
reg8 RX8025_Save_0(const DateTime_TypeDef __gptr* DateTime);

reg8 RX8025_Init_1(const SI2CFunction_TypeDef __gptr *SI2CFunction);
reg8 RX8025_Read_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, DateTime_TypeDef* DateTime);
reg8 RX8025_Save_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const DateTime_TypeDef __gptr* DateTime);

void RX8025_CalibProcess_0(reg8 NowTemper, reg8 OffSet);                                                                        //must trigg x20(s), NowTemper & 0x7F: 0->52 (C), if (NowTemper & 0x00) : re-init
reg8 RX8025_CalibProcess_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, reg8 RefStage, reg8 NowTemper, reg8 OffSet);        //RefStage: 0:9, return RefStage


#endif