#include <n76e003.h>
#include <i2c.h>

void I2CM_Start()
{
  I2CON.REG = BIT6;
  I2CON.BITS.STA = 1;
  while (!I2CON.BITS.SI);
  I2CON.BITS.STA = 0;
}
unsigned char I2CM_WriteAddress(unsigned char Address)
{
  I2DAT = Address;
  I2CON.BITS.SI = 0;
  while (!I2CON.BITS.SI);
  return (I2STAT.REG == I2CM_STATUS_TRANS_ADDR_ACK) && (I2STAT.REG == I2CM_STATUS_RECV_ADDR_ACK);
}
unsigned char I2CM_ReadByte(unsigned char IsNotLast)
{
  I2CON.BITS.AA = IsNotLast;
  I2DAT = 0xFF;
  I2CON.BITS.SI = 0;
  while (!I2CON.BITS.SI);
  return I2DAT;
}
unsigned char I2CM_WriteByte(unsigned char Data)
{
  I2DAT = Data;
  I2CON.BITS.SI = 0;
  while (!I2CON.BITS.SI);
  return I2STAT.REG != I2CM_STATUS_TRANS_DATA_ACK;
}
