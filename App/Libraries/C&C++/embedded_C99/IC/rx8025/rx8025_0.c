#include <rx8025.h>
#include <soft_i2c.h>
#include <math.h>

reg8 RX8025_Init_0()
{
  static const unsigned char config[] = {0x20, 0xA0};
  return RX8025_I2C_WRITES_0(0xE0, config, 2);
}
reg8 RX8025_Read(DateTime_TypeDef* DateTime)
{
  unsigned char buff[8];
  if (RX8025_I2C_READS_0(0, buff, 8))
  {
    DateTime->Second      = Math_BCD(buff[1]);
    DateTime->Minute      = Math_BCD(buff[2]);
    DateTime->Hour        = Math_BCD(buff[3]);
    DateTime->WeekDay     = Math_BCD(buff[4]);
    DateTime->Day         = Math_BCD(buff[5]);
    DateTime->Month       = Math_BCD(buff[6]);
    DateTime->Year        = Math_BCD(buff[7]);
    return 1;
  }
  return 0;
}

reg8 RX8025_Save(DateTime_TypeDef* DateTime)
{
  unsigned char buff[7];
  buff[0]       = Math_DCB(DateTime->Second );
  buff[1]       = Math_DCB(DateTime->Minute );
  buff[2]       = Math_DCB(DateTime->Hour   );
  buff[3]       = Math_DCB(DateTime->WeekDay);
  buff[4]       = Math_DCB(DateTime->Day    );
  buff[5]       = Math_DCB(DateTime->Month  );
  buff[6]       = Math_DCB(DateTime->Year   );
  if (RX8025_I2C_WRITES_0(0, buff, 7))
    return 1;
  return 0;
}