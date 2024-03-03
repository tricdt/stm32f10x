#ifndef TEST_LIBRARIES
//==============================================================================================================================================================
#include <digital_output.h>
#include <config.h>
//==============================================================================================================================================================
extern __no_init DigitalOutputEx_TypeDef DigitalOutputEx_f1[DIGITAL_OUTPUT_EX_QUANTITY_1];
void DigitalOutputEx_Turn_1(reg8 DigitalOutputIndex, reg8 IsOn);
//==============================================================================================================================================================
void DigitalOutput_BeginEx_1()
{
  reg8 DigitalOutputIndex;
  for (DigitalOutputIndex = 0; DigitalOutputIndex < DIGITAL_OUTPUT_EX_QUANTITY_1; DigitalOutputIndex++)
  {
    DigitalOutputEx_TypeDef* DigitalOutputEx = &DigitalOutputEx_f1[DigitalOutputIndex];
    DigitalOutputEx->IsOn = DigitalOutputEx->CountEdgeTime = DigitalOutputEx->Times = 0;
    DigitalOutputEx_Turn_1(DigitalOutputIndex, 0);
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_ProcessIndexEx_1(reg8 DigitalOutputIndex, void Finish(reg8 DigitalOutputIndex))
{
  DigitalOutputEx_TypeDef* DigitalOutputEx = &DigitalOutputEx_f1[DigitalOutputIndex];
  if (DigitalOutputEx->Times)
  {
    if (++DigitalOutputEx->CountEdgeTime > DigitalOutputEx->EdgeTime[DigitalOutputEx->IsOn])
    {
      DigitalOutputEx->CountEdgeTime = 1;
      DigitalOutputEx_Turn_1(DigitalOutputIndex, (DigitalOutputEx->IsOn = !DigitalOutputEx->IsOn));
      if (DigitalOutputEx->Times != DIGITAL_OUTPUT_ALWAYS_BLINK)
      {
        if (!(--DigitalOutputEx->Times) && Finish)
          Finish(DigitalOutputIndex);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_ProcessEx_1(void Finish(reg8 DigitalOutputIndex))
{
  reg8 DigitalOutputIndex;
  for (DigitalOutputIndex = 0; DigitalOutputIndex < DIGITAL_OUTPUT_EX_QUANTITY_1; DigitalOutputIndex++)
    DigitalOutput_ProcessIndex_1(DigitalOutputIndex, Finish);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void DigitalOutput_BlinkEx_1(reg8 DigitalOutputIndex, reg8 Times, reg8 HighEdgeTime, reg8 LowEdgeTime)
{
  DigitalOutputEx_TypeDef* DigitalOutputEx = &DigitalOutputEx_f1[DigitalOutputIndex];
  DigitalOutputEx_Turn_1(DigitalOutputIndex, (DigitalOutputEx->IsOn = 0));
  DigitalOutputEx->CountEdgeTime = 0xFE;
  if (Times > 100)
    DigitalOutputEx->Times = DIGITAL_OUTPUT_ALWAYS_BLINK;
  else
    DigitalOutputEx->Times = Times * 2;
  DigitalOutputEx->EdgeTime[1] = HighEdgeTime;
  DigitalOutputEx->EdgeTime[0] = LowEdgeTime;
}
//==============================================================================================================================================================
#endif