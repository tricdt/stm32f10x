#include <gpio.h>

static void Config(volatile unsigned long* Reg, unsigned long PIN, unsigned long Value)
{
  unsigned long reset = 0;
  unsigned long set = 0;
  for (unsigned long i = 0; i < 16; i++)
  {
    set <<= 2;
    reset <<= 2;
    if (PIN & (1UL << 15))
      set |= Value;
    else
      reset |= 3;
    PIN <<= 1;
  }
  *Reg &= reset;
  *Reg |= set;
}
void GPIO_Mode(volatile GPIO_TypeDef* GPIO, unsigned long PIN, GPIO_MODE Mode)
{
  Config(&GPIO->MODE.REG, PIN, Mode);
}
void GPIO_OutPull(volatile GPIO_TypeDef* GPIO, unsigned long PIN, unsigned long IsOpenDrain)
{
  if (IsOpenDrain)
    GPIO->O_TYPE.REG |= PIN;
  else
    GPIO->O_TYPE.REG &= ~PIN;
}
void GPIO_OutSpeed(volatile GPIO_TypeDef* GPIO, unsigned long PIN, GPIO_SPEED Speed)
{
  Config(&GPIO->O_SPEED.REG, PIN, Speed);
}
void GPIO_InPull(volatile GPIO_TypeDef* GPIO, unsigned long PIN, GPIO_PULL Pull)
{
  Config(&GPIO->I_PULL.REG, PIN, Pull);
}