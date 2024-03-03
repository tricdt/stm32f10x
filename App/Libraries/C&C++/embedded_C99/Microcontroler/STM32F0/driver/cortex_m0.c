#include <cortex_m0.h>

void STK_Init(unsigned int Load)
{  
  STK.LOAD = Load;
  STK.CTRL.REG = 7;
}