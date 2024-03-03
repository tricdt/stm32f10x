#ifndef _GPIO_H_
#define _GPIO_H_

#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  xBUNION(MODE, unsigned long, b, 0, 15, 2);    //              0x0000'0000     GPIO port mode register (0x2800'0000 for port A reset)
                                                //                                      00: Input mode (reset state)
                                                //                                      01: General purpose output mode
                                                //                                      10: Alternate function mode
                                                //                                      11: Analog mode  
  xBUNION(O_TYPE, unsigned long, b, 0, 15, 1);  //              0x0000'0000     GPIO port output type register: 0: push-pull, 1: open-drain
  xBUNION(O_SPEED, unsigned long, b, 0, 15, 2); //              0x0000'0000     GPIO port output speed register (0x0C00'0000 for port A reset)
                                                //                                      x0: Low speed
                                                //                                      01: Medium speed
                                                //                                      11: High speed
  xBUNION(I_PULL, unsigned long, b, 0, 15, 2);  //              0x0000'0000     GPIO port pull-up/pull-down register (0x2400'0000 for port A reset)
                                                //                                      00: No pull-up, pull-down
                                                //                                      01: Pull-up
                                                //                                      10: Pull-down
  xBUNION(, unsigned long, b, 0, 15, 1)
    IDR,                                        //              0x----'----     GPIO port input data register
    ODR;                                        //              0x0000'0000     GPIO port output data register
  union
  {
    unsigned long REG;
    struct
    {
      xBUNION(BSR, unsigned short, b, 0, 15, 1);//              0x0000          Write 1 to set pin output, set has priority 
      xBUNION(BR, unsigned short, b, 0, 15, 1); //              0x0000          Write 1 to clear pin output
    };
  } BSRR;                                       //                              Port bit set/reset register
  BUNION(LCKR, unsigned long,                   //              0x0000'0000     Port configuration lock register
    xBITS_B(b, 0, 15, 1),                       //
    LOCK                              , 1);     //16            0               LOCK key writing sequence: write 1 -> 0 -> 1 -> read 0 -> 1
  union
  {
    unsigned long REGS[2];
    xBSTRUCT(BITS, unsigned long, b, 0, 15, 4); //              0x0000 0000     value -> AF value-th
  } AFR;                                        //                              GPIO alternate function
  xBUNION(BRR, unsigned long, b, 0, 15, 1);     //              0x0000'0000     GPIO port bit reset register  
} GPIO_TypeDef;
//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
/*NOTE: default:
  +)SWD debugger:
    -PA13: SWDIO
    -PA14: SWCLK
  >>config by GPIO.MODE
  +)Remeber turn on RCC:
    RCC_BITBAND.APB2_ENR.IOPA = 1;
    RCC_BITBAND.APB2_ENR.IOPB = 1;
    RCC_BITBAND.APB2_ENR.IOPC = 1;
    RCC_BITBAND.APB2_ENR.IOPD = 1;
    RCC_BITBAND.APB2_ENR.IOPE = 1;
    RCC_BITBAND.APB2_ENR.IOPF = 1;
    RCC_BITBAND.APB2_ENR.IOPG = 1;
*/

typedef enum
{
  GPIO_MODE_INPUT               = 0,
  GPIO_MODE_OUTPUT              = 1,
  GPIO_MODE_ALTERNATE           = 2,
  GPIO_MODE_ANALOG              = 3,
} GPIO_MODE;
void GPIO_Mode(volatile GPIO_TypeDef* GPIO, unsigned long PIN, GPIO_MODE Mode);
void GPIO_OutPull(volatile GPIO_TypeDef* GPIO, unsigned long PIN, unsigned long IsOpenDrain);
typedef enum
{
  GPIO_SPEED_LOW                = 0,
  GPIO_SPEED_MEDIUM             = 1,
  GPIO_SPEED_HIGH               = 3,
} GPIO_SPEED;
void GPIO_OutSpeed(volatile GPIO_TypeDef* GPIO, unsigned long PIN, GPIO_SPEED Speed);
typedef enum
{
  GPIO_PULL_NO                  = 0,
  GPIO_PULL_UP                  = 1,
  GPIO_PULL_DOWN                = 2,
} GPIO_PULL;
void GPIO_InPull(volatile GPIO_TypeDef* GPIO, unsigned long PIN, GPIO_PULL Pull);
















/*NOTE: default:
  +)JTAG debugger:
    -PA15: JTDI
    -PB3: JTDO
    -PB4: NJTRST
  +)SWD debugger:
    -PA13: SWDIO
    -PA14: SWCLK
  >>config by AFIO:
    RCC_BITBAND.APB2_ENR.AFIO = 1;
    AFIO.MAPR.BITS.SWJ_CFG = 0; //reset state
    AFIO.MAPR.BITS.SWJ_CFG = 1; //x(NJTRST)
    AFIO.MAPR.BITS.SWJ_CFG = 2; //x(JTAG)
    AFIO.MAPR.BITS.SWJ_CFG = 3; //x(JTAG & SWD)

  +)Remeber turn on RCC:
    RCC_BITBAND.APB2_ENR.IOPA = 1;
    RCC_BITBAND.APB2_ENR.IOPB = 1;
    RCC_BITBAND.APB2_ENR.IOPC = 1;
    RCC_BITBAND.APB2_ENR.IOPD = 1;
    RCC_BITBAND.APB2_ENR.IOPE = 1;
    RCC_BITBAND.APB2_ENR.IOPF = 1;
    RCC_BITBAND.APB2_ENR.IOPG = 1;
*/
////==============================================================================================================================================================
//typedef enum
//{
//  GPIO_MODE_INPUT_ANALOG                = (0 << 2) | 0,
//  GPIO_MODE_INPUT_FLOAT                 = (1 << 2) | 0,
//  GPIO_MODE_INPUT_PULL                  = (2 << 2) | 0,
//  
//  GPIO_MODE_OUTPUT_PUSHPULL_10MHz       = (0 << 2) | 1,
//  GPIO_MODE_OUTPUT_OPEN_10MHz           = (1 << 2) | 1,
//  GPIO_MODE_AF_OUTPUT_PUSHPULL_10MHz    = (2 << 2) | 1,
//  GPIO_MODE_AF_OUTPUT_OPEN_10MHz        = (3 << 2) | 1,
//  
//  GPIO_MODE_OUTPUT_PUSHPULL_2MHz        = (0 << 2) | 2,
//  GPIO_MODE_OUTPUT_OPEN_2MHz            = (1 << 2) | 2,
//  GPIO_MODE_AF_OUTPUT_PUSHPULL_2MHz     = (2 << 2) | 2,
//  GPIO_MODE_AF_OUTPUT_OPEN_2MHz         = (3 << 2) | 2,
//  
//  GPIO_MODE_OUTPUT_PUSHPULL_50MHz       = (0 << 2) | 3,
//  GPIO_MODE_OUTPUT_OPEN_50MHz           = (1 << 2) | 3,
//  GPIO_MODE_AF_OUTPUT_PUSHPULL_50MHz    = (2 << 2) | 3,
//  GPIO_MODE_AF_OUTPUT_OPEN_50MHz        = (3 << 2) | 3,  
//} GPIO_MODE;
//void GPIO_Mode(volatile GPIO_TypeDef* GPIO, unsigned long PIN, GPIO_MODE Mode);
////==============================================================================================================================================================
///*Fast init GPIO by define, Example:
//  GPIO_ModeHigh(&GPIOA, PIN_Clr(11) | PIN_Clr(12), PIN_OutAFOpen50(11) | PIN_OutAFOpen50(12));  //= GPIO_Mode(&GPIOA, BIT11 | BIT12, OUTPUT_AF_PUSHPULL_50MHZ);
//  GPIO_ModeHigh(&GPIOB, PIN_Clr(0) | PIN_Clr(1), PIN_OutPush2(0) | PIN_OutPush2(1));            //= GPIO_Mode(&GPIOB, BIT1 | BIT2, OUTPUT_PUSHPULL_50MHZ);
//*/
//#define PIN_Clr(index)                          (0xFUL << (4 * (index % 8)))
//#define PIN_OutPush10(index)                    (0x1UL << (4 * (index % 8)))
//#define PIN_OutPush2(index)                     (0x2UL << (4 * (index % 8)))
//#define PIN_OutPush50(index)                    (0x3UL << (4 * (index % 8)))
//#define PIN_OutOpen10(index)                    (0x5UL << (4 * (index % 8)))
//#define PIN_OutOpen2(index)                     (0x6UL << (4 * (index % 8)))
//#define PIN_OutOpen50(index)                    (0x7UL << (4 * (index % 8)))
//#define PIN_OutAFPush10(index)                  (0x9UL << (4 * (index % 8)))
//#define PIN_OutAFPush2(index)                   (0xAUL << (4 * (index % 8)))
//#define PIN_OutAFPush50(index)                  (0xBUL << (4 * (index % 8)))
//#define PIN_OutAFOpen10(index)                  (0xDUL << (4 * (index % 8)))
//#define PIN_OutAFOpen2(index)                   (0xEUL << (4 * (index % 8)))
//#define PIN_OutAFOpen50(index)                  (0xFUL << (4 * (index % 8)))
//#define PIN_InAnalog(index)                     (0x0UL << (4 * (index % 8)))
//#define PIN_InFloat(index)                      (0x4UL << (4 * (index % 8)))
//#define PIN_InPushDown(index)                   (0x8UL << (4 * (index % 8)))    //ODR.PIN = 0
//#define PIN_InPushUp(index)                     (0x8UL << (4 * (index % 8)))    //ODR.PIN = 1
//#define GPIO_ModeLow(GPIO, PIN_Clear, PIN_Mode)   (GPIO)->CR.REGS.LOW &= ~(PIN_Clear); (GPIO)->CR.REGS.LOW |= (PIN_Mode)        //for pin 0->7
//#define GPIO_ModeHigh(GPIO, PIN_Clear, PIN_Mode)  (GPIO)->CR.REGS.HIGH &= ~(PIN_Clear); (GPIO)->CR.REGS.HIGH |= (PIN_Mode)      //for pin 8->15

#endif