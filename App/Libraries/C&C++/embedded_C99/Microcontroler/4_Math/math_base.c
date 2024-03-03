#include <math.h>

reg8 Math_BCD(reg8 BValue)
{
  return (BValue >> 4) * 10 + (BValue & 0x0F);
}
reg8 Math_DCB(reg8 DValue)
{
  return ((DValue / 10) << 4) | (DValue % 10);
}