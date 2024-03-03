#ifndef _ADC_H_
#define _ADC_H_

#define ADC_Init(Channels)      AINDIDS.REG = Channels; ADCCON1.REG = BIT0      //Channels = AINs
#define ADC_Start(Channel)      ADCCON0.REG = BIT6 | Channel                    //Channel = 0:8
#define ADC_Wait()              while (!ADCCON0.BITS.ADCF)

unsigned short ADC_GetValue();
unsigned short ADC_Read(unsigned char Channel);
unsigned short ADC_GetBandgap();

#endif