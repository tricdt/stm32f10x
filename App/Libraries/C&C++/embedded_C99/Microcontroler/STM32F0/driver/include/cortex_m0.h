#ifndef _CORTEXT_M0_H_
#define _CORTEXT_M0_H_

#include <common.h>
#include <define.h>
//==============================================================================================================================================================
//==================================================                 Using Functions            ================================================================
//==============================================================================================================================================================
void STK_Init(unsigned int Load);               //IRQ trigger = Load * 1000 / FSYS (us), FSYS KHz





//==============================================================================================================================================================
//============================================================        System timer         =====================================================================
//==============================================================================================================================================================
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CTRL, unsigned int,                    //              0x0000'0000     SysTick control and status register
    ENABLE                              , 1,    //0             0               Counter enable
    TICK_INT                            , 1,    //1             0               SysTick exception request enable
    CLK_SOURCE                          , 1,    //2             0               Clock source selection (0: AHB/8, 1: AHB)
    _reserved                           , 13,
    COUNT_FLAG                          , 1,    //16            0               Returns 1 if timer counted to 0 since last time this was read
    _reserved1                          , 15);
  unsigned int LOAD;                            //              0x0000'0000     SysTick reload value register
  unsigned int VALUE;                           //              0x0000'0000     SysTick current value register
  unsigned int const CALIB;                     //              0x0000'0000     SysTick calibration value register
} STK_TypeDef;
__root __no_init volatile STK_TypeDef STK       __at(0xE000E010);

#endif