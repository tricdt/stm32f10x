#include <soft_i2c.h>
#include <config.h>

#define SI2C_START()    SI2C_CONFIG_SDA_0(0);SI2C_CONFIG_SCL_0(0)
#define SI2C_STOP()     SI2C_CONFIG_SCL_0(1);SI2C_CONFIG_SDA_0(1)

void SI2C_Start_0()
{
  SI2C_START();
}
void SI2C_Stop_0()
{
  SI2C_CONFIG_SDA_0(0);
  SI2C_STOP();
}
reg8 SI2C_WriteByte_0(reg8 Data)
{
  reg8 ret;
  SI2C_CONFIG_SDA_0(!!(Data & BIT7)); SI2C_CONFIG_SCL_0(1); Data <<= 1; SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT7)); SI2C_CONFIG_SCL_0(1); Data <<= 1; SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT7)); SI2C_CONFIG_SCL_0(1); Data <<= 1; SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT7)); SI2C_CONFIG_SCL_0(1); Data <<= 1; SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT7)); SI2C_CONFIG_SCL_0(1); Data <<= 1; SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT7)); SI2C_CONFIG_SCL_0(1); Data <<= 1; SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT7)); SI2C_CONFIG_SCL_0(1); Data <<= 1; SI2C_CONFIG_SCL_0(0);
  SI2C_CONFIG_SDA_0(!!(Data & BIT7)); SI2C_CONFIG_SCL_0(1); Data <<= 1; SI2C_CONFIG_SCL_0(0);
  
  SI2C_CONFIG_SDA_MODE_0(0);
  SI2C_CONFIG_SCL_0(1);
  ret = SI2C_READ_SDA_0();
  SI2C_CONFIG_SDA_0(ret);
  SI2C_CONFIG_SDA_MODE_0(1);
  SI2C_CONFIG_SCL_0(0);
  SI2C_DELAY_0();
  return ret;
}
reg8 SI2C_WriteBytes_0(const reg8 SlaveAddr, const reg8 DataAddr, const unsigned char *Data, reg8 Length)
{
  SI2C_START();
  if (SI2C_WriteByte_0(SlaveAddr))
    goto FAIL;
  if (SI2C_WriteByte_0(DataAddr))
    goto FAIL;
  while (Length--)
  {
    if (SI2C_WriteByte_0(*Data++))
      goto FAIL;
  }
  SI2C_STOP();
  return 1;
FAIL:
  SI2C_CONFIG_SDA_0(0);
  SI2C_STOP();
  return 0;
}
reg8 SI2C_ReadByte_0(const reg8 NACK)
{
  reg8 result;
  SI2C_CONFIG_SDA_MODE_0(0);
  for (reg8 i = 0; i < 8; i++)
  {
    result <<= 1;
    SI2C_CONFIG_SCL_0(1);
    result |= SI2C_READ_SDA_0();
    SI2C_CONFIG_SCL_0(0);
  }
  SI2C_CONFIG_SDA_0(NACK);
  SI2C_CONFIG_SDA_MODE_0(1);
  SI2C_CONFIG_SCL_0(1); SI2C_CONFIG_SCL_0(0);
  SI2C_DELAY_0();
  return result;
}
reg8 SI2C_ReadBytes_0(const reg8 SlaveAddr, const reg8 DataAddr, unsigned char *Buffer, reg8 Length)
{
  reg8 ret = 1;
  SI2C_START();
  if (SI2C_WriteByte_0(SlaveAddr) || SI2C_WriteByte_0(DataAddr))
  {
    ret = 0;
    goto END;
  }
  SI2C_STOP();
  //restart
  SI2C_DELAY_0();
  SI2C_START();
  if (SI2C_WriteByte_0((SlaveAddr | 0x01)))
  {
    ret = 0;
    goto END;
  }
  while (--Length)
    *Buffer++ = SI2C_ReadByte_0(0);
  *Buffer = SI2C_ReadByte_0(1);
END:
  SI2C_CONFIG_SDA_0(0);
  SI2C_STOP();
  return ret;
}