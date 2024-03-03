#ifndef _PWM_H_
#define _PWM_H_

#define PWM_Enable_1(Channels)                  SFR_PAGE(1); PIOCON1.REG |= Channels; SFR_PAGE(0)
#define PWM_Disable_1(Channels)                 SFR_PAGE(1); PIOCON1.REG &= ~(Channels); SFR_PAGE(0)
#define PWM_Enable(Channels)                    PIOCON0.REG |= Channels
#define PWM_Disable(Channels)                   PIOCON0.REG &= ~(Channels)
#define PWM_SetChannel(Channel, Value)          SFR_PAGE((Channel) > 3); PWM##Channel##H = (Value) >> 8; PWM##Channel##L = (Value) & 0xFF; SFR_PAGE(0)
/*
  real cycle (us) = CycleValue / 16
  real divide = 2^Divide
*/
#define PWM_Config(CycleValue, Divide)          PWMCON0.REG = 0; PWMPH = (CycleValue) >> 8; PWMPL = (CycleValue) & 0xFF; PWMCON1.REG = Divide
#define PWM_Stop()                              PWMCON0.REG = 0
#define PWM_Start()                             PWMCON0.REG = BIT6 | BIT7

#endif