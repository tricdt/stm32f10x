#include <n76e003.h>
#include <adc.h>
#include <iap.h>

unsigned short ADC_GetValue()
{
  unsigned short value;
  value = ADCRH;
  value *= 16;
  value |= ADCRL;
  return value;
}

unsigned short ADC_Read(unsigned char Channel)
{
  ADC_Start(Channel);
  ADC_Wait();
  return ADC_GetValue();
}

unsigned short ADC_GetBandgap()
{
  unsigned short value;
  value = IAP_AP_ReadByte(0x0C);
  value <<= 4;
  value |= IAP_AP_ReadByte(0x0D) & 0x0F;
  return value;
}