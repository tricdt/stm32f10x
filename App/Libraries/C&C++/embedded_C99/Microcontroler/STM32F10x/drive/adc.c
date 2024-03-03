#include <adc.h>

void ADC_Start(volatile ADC_TypeDef* ADC, unsigned long Channel)
{
  ADC->CR2.REG = 0;
  ADC->SR.REG = 0;
  ADC->SQR.REGS.r1 = 0;
  ADC->SQR.REGS.r3 = Channel & 0x1F;
  ADC->CR2.REG =  BIT0;
  ADC->CR2.REG = (Channel & BIT23) | BIT22 | BIT0;
  ADC->CR2.REG = ADC->CR2.REG;
}
void ADC_StartGroup(volatile ADC_TypeDef* ADC, const unsigned char* Channels)
{
  
//        ADC1.SR.REG = 0;
//        ADC1.CR1.BITS.SCAN = 1;
//        ADC1.SQR.BITS.CN1 = 5;
//        ADC1.SQR.BITS.CN2 = 3;
//        ADC1.SQR.BITS.L = 1;
//        ADC1.CR2.BITS.ADON = 1;
//        ADC1.CR2.BITS.SWSTART = 1;
//        ADC1.CR2.BITS.ADON = 1;
//        
//        while (!ADC1.SR.BITS.EOC);
//        ADC1.CR2.BITS.ADON = 0;
  
  
  
  
  
  
  unsigned long number = 0;
  unsigned long value[3] = {0, 0, 0};
  if (Channels)
  {
    for (unsigned long i = 0; i < 16; i++)
    {
      if (*Channels > 17)
        break;
      number++;
      value[i / 6] |= *Channels << ((i % 6) * 5);
      Channels++;
    }
  }
  ADC->SR.REG = 0;
  ADC->CR2.REG = 0;
  if (number--)
  {
    ADC->SQR.REGS.r1 = value[2] | (number << 20);
    ADC->SQR.REGS.r2 = value[1];
    ADC->SQR.REGS.r3 = value[0];
    ADC->CR1.BITS.SCAN = 1;
    
    ADC->CR2.BITS.CONT = 1;
    ADC->CR2.BITS.DMA = 1;
    
        ADC->CR2.BITS.ADON = 1;
        ADC->CR2.BITS.SWSTART = 1;
        ADC->CR2.BITS.ADON = 1;
    
//    ADC->CR2.REG = BIT8 | BIT1 | BIT0;
//    ADC->CR2.REG = BIT22 | BIT8 | BIT1 | BIT0;
//    ADC->CR2.REG = BIT22 | BIT8 | BIT1 | BIT0;
  }
}
unsigned long ADC_Read(volatile ADC_TypeDef* ADC, unsigned long* OutValue)
{
  if (ADC->SR.BITS.EOC)
  {
    *OutValue += ADC->DR.REG;
    return 1;
  }
  return 0;
}