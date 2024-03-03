#ifndef TEST_LIBRARIES
//==============================================================================================================================================================
#include <digital_output.h>
#include <config.h>
//==============================================================================================================================================================
extern __no_init DigitalOutputEx_TypeDef DigitalOutputEx_f0;
//==============================================================================================================================================================
void DigitalOutput_BeginEx_0()
{
  DigitalOutputEx_f0.IsOn = DigitalOutputEx_f0.CountEdgeTime = DigitalOutputEx_f0.Times = 0;
  DIGITAL_OUTPUT_EX_TURN_0(0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_ProcessEx_0(void Finish())
{
  if (DigitalOutputEx_f0.Times)
  {
    if (++DigitalOutputEx_f0.CountEdgeTime > DigitalOutputEx_f0.EdgeTime[DigitalOutputEx_f0.IsOn])
    {
      DigitalOutputEx_f0.CountEdgeTime = 1;
      DIGITAL_OUTPUT_EX_TURN_0((DigitalOutputEx_f0.IsOn = !DigitalOutputEx_f0.IsOn));
      if (DigitalOutputEx_f0.Times != DIGITAL_OUTPUT_ALWAYS_BLINK)
      {
        if (!(--DigitalOutputEx_f0.Times) && Finish)
          Finish();
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_BlinkEx_0(reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime)
{
  DigitalOutputEx_f0.IsOn = 0;
  DIGITAL_OUTPUT_EX_TURN_0(0);
  DigitalOutputEx_f0.CountEdgeTime = 0xFE;
  if (Times > 100)
    DigitalOutputEx_f0.Times = DIGITAL_OUTPUT_ALWAYS_BLINK;
  else
    DigitalOutputEx_f0.Times = Times << 1;
  DigitalOutputEx_f0.EdgeTime[1] = HighEdgeTime;
  DigitalOutputEx_f0.EdgeTime[0] = LowEdgeTime;
}
//==============================================================================================================================================================
#endif