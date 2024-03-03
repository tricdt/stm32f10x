#ifndef _I2C_H_
#define _I2C_H_

typedef enum
{
  //master mode
  I2CM_STATUS_START                     = 0x08,
  I2CM_STATUS_RE_START                  = 0x10,
  I2CM_STATUS_TRANS_ADDR_ACK            = 0x18,
  I2CM_STATUS_TRANS_ADDR_NACK           = 0x20,
  I2CM_STATUS_TRANS_DATA_ACK            = 0x28,
  I2CM_STATUS_TRANS_DATA_NACK           = 0x30,
  I2CM_STATUS_ARB_LOST                  = 0x38,
  I2CM_STATUS_RECV_ADDR_ACK             = 0x40,
  I2CM_STATUS_RECV_ADDR_NACK            = 0x48,
  I2CM_STATUS_RECV_DATA_ACK             = 0x50,
  I2CM_STATUS_RECV_DATA_NACK            = 0x58,
  I2CM_STATUS_BUS_ERROR                 = 0x00,
  //slave mode
  I2CS_STATUS_START_STOP                = 0xA0,
  I2CS_STATUS_TRANS_ADDR_ACK            = 0xA8,
  I2CS_STATUS_TRANS_ARB_LOST            = 0xB0,
  I2CS_STATUS_TRANS_DATA_ACK            = 0xB8,
  I2CS_STATUS_TRANS_DATA_NACK           = 0xC0,
  I2CS_STATUS_TRANS_LAST_DATA_ACK       = 0xC8,
  I2CS_STATUS_RECV_ADDR_ACK             = 0x60,
  I2CS_STATUS_RECV_ARB_LOST             = 0x68,
  I2CS_STATUS_RECV_DATA_ACK             = 0x80,
  I2CS_STATUS_RECV_DATA_NACK            = 0x88,
  //slave global mode
  I2CS_STATUS_GC_ADDR_ACK               = 0x70,
  I2CS_STATUS_GC_ARB_LOST               = 0x78,
  I2CS_STATUS_GC_DATA_ACK               = 0x90,
  I2CS_STATUS_GC_DATA_NACK              = 0x98,
} I2C_STATUS;

#define I2CM_Stop()                     I2CON.REG = BIT6 | BIT4

void I2CM_Start();
unsigned char I2CM_WriteAddress(unsigned char Address);         //return 1 to failed
unsigned char I2CM_ReadByte(unsigned char IsNotLast);           //return data
unsigned char I2CM_WriteByte(unsigned char Data);               //return 1 to failed

#endif