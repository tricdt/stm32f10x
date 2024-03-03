#include <soft_i2c.h>

#define SI2C_START()    SI2CFunction->ConfigSDA(0);SI2CFunction->ConfigSCL(0)
#define SI2C_STOP()     SI2CFunction->ConfigSCL(1);SI2CFunction->ConfigSDA(1)

void SI2C_Start_1(const SI2CFunction_TypeDef __gptr *SI2CFunction)
{
  SI2C_START();
}
void SI2C_Stop_1(const SI2CFunction_TypeDef __gptr *SI2CFunction)
{
  SI2CFunction->ConfigSDA(0);
  SI2C_STOP();
}
reg8 SI2C_WriteByte_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 Data)
{
  reg8 ret;
  SI2CFunction->ConfigSDA(!!(Data & BIT7)); SI2CFunction->ConfigSCL(1); SI2CFunction->ConfigSCL(0);
  SI2CFunction->ConfigSDA(!!(Data & BIT6)); SI2CFunction->ConfigSCL(1); SI2CFunction->ConfigSCL(0);
  SI2CFunction->ConfigSDA(!!(Data & BIT5)); SI2CFunction->ConfigSCL(1); SI2CFunction->ConfigSCL(0);
  SI2CFunction->ConfigSDA(!!(Data & BIT4)); SI2CFunction->ConfigSCL(1); SI2CFunction->ConfigSCL(0);
  SI2CFunction->ConfigSDA(!!(Data & BIT3)); SI2CFunction->ConfigSCL(1); SI2CFunction->ConfigSCL(0);
  SI2CFunction->ConfigSDA(!!(Data & BIT2)); SI2CFunction->ConfigSCL(1); SI2CFunction->ConfigSCL(0);
  SI2CFunction->ConfigSDA(!!(Data & BIT1)); SI2CFunction->ConfigSCL(1); SI2CFunction->ConfigSCL(0);
  SI2CFunction->ConfigSDA(!!(Data & BIT0)); SI2CFunction->ConfigSCL(1); SI2CFunction->ConfigSCL(0);
  
  SI2CFunction->ConfigSDAMode(0);
  SI2CFunction->ConfigSCL(1);
  ret = SI2CFunction->ReadSDA();
  SI2CFunction->ConfigSDA(ret);
  SI2CFunction->ConfigSDAMode(1);
  SI2CFunction->ConfigSCL(0);
  SI2CFunction->Delay();
  return ret;
}
reg8 SI2C_WriteBytes_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 SlaveAddr, const reg8 DataAddr, const unsigned char *Data, reg8 Length)
{
  SI2C_START();
  if (SI2C_WriteByte_1(SI2CFunction, SlaveAddr))
    goto FAIL;
  if (SI2C_WriteByte_1(SI2CFunction, DataAddr))
    goto FAIL;
  while (Length--)
  {
    if (SI2C_WriteByte_1(SI2CFunction, *Data++))
      goto FAIL;
  }
  SI2C_STOP();
  return 1;
FAIL:
  SI2CFunction->ConfigSDA(0);
  SI2C_STOP();
  return 0;
}
reg8 SI2C_ReadByte_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 NACK)
{
  reg8 result;
  SI2CFunction->ConfigSDAMode(0);
  for (reg8 i = 0; i < 8; i++)
  {
    result <<= 1;
    SI2CFunction->ConfigSCL(1);
    result |= SI2CFunction->ReadSDA();
    SI2CFunction->ConfigSCL(0);
  }
  SI2CFunction->ConfigSDA(NACK);
  SI2CFunction->ConfigSDAMode(1);
  SI2CFunction->ConfigSCL(1); SI2CFunction->ConfigSCL(0);
  SI2CFunction->Delay();
  return result;
}
reg8 SI2C_ReadBytes_1(const SI2CFunction_TypeDef __gptr *SI2CFunction, const reg8 SlaveAddr, const reg8 DataAddr, unsigned char *Buffer, reg8 Length)
{
  reg8 ret = 1;
  SI2C_START();
  if (SI2C_WriteByte_1(SI2CFunction, SlaveAddr) || SI2C_WriteByte_1(SI2CFunction, DataAddr))
  {
    ret = 0;
    goto END;
  }
  SI2C_STOP();
  //restart
  SI2C_START();
  if (SI2C_WriteByte_1(SI2CFunction, (SlaveAddr | 0x01)))
  {
    ret = 0;
    goto END;
  }
  while (--Length)
    *Buffer++ = SI2C_ReadByte_1(SI2CFunction, 0);
  *Buffer = SI2C_ReadByte_1(SI2CFunction, 1);
END:
  SI2CFunction->ConfigSDA(0);
  SI2C_STOP();
  return ret;
}