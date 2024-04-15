#ifndef __GPIO_H
#define __GPIO_H
#include "stm32f10x.h"
class GPIO
{
private:
   /* data */
public:
   GPIO(u8 pin);

   ~GPIO();
   static void setGPIO(void);
   void setPin(void);
};




#endif