#ifndef _RCC_H_
#define _RCC_H_

#include <define.h>
//                                      |       //Address       Default         Description
typedef struct
{
  BUNION(CR, unsigned int,                      //                              Clock control register
    HSION                               , 1,    //0             1               Internal high-speed clock enable
    const HSI_RDY                       , 1,    //1             1               Internal high-speed clock ready flag
    _reserved                           , 1,
    HSI_TRIM                            , 5,    //3:7           16              Internal high-speed clock trimming
    const HSI_CAL                       , 8,    //8:15          -               Internal high-speed clock calibration
    HSE_ON                              , 1,    //16            0               HSE clock enable
    const HSE_RDY                       , 1,    //17            0               External high-speed clock ready flag
    HSE_PYB                             , 1,    //18            0               External high-speed clock bypass
    CSS_ON                              , 1,    //19            0               Clock security system enable
    _reserved1                          , 4,
    PLL_ON                              , 1,    //24            0               PLL enable
    const PLL_RDY                       , 1,    //25            0               PLL clock ready flag
    _reserved2                          , 6);
  BUNION(CFGR, unsigned int,                    //                              Clock configuration register
    SW                                  , 2,    //0-1           0               System clock switch
    const SWS                           , 2,    //2-3           0               System clock switch status
    HPRE                                , 4,    //4:7           0               AHB prescaler
    PPRE                                , 3,    //8:10          0               APB low-speed prescaler (APB1)
    _reserved                           , 3,    //11:13         0               APB high-speed prescaler (APB2)
    ADC_PRE                             , 1,    //14-15         0               ADC prescaler
    _reserved1                          , 1,
    PLL_SRC                             , 1,    //16            0               PLL entry clock source
    PLL_XTPRE                           , 1,    //17            0               HSE divider for PLL entry
    PLL_MUL                             , 4,    //18:21         0               PLL multiplication factor
    _reserved2                          , 2,
    MCO                                 , 4,    //24:27         0               Microcontroller clock output
    MCO_PRE                             , 3,    //28:30         0               Microcontroller Clock Output Prescaler
    PLL_NODIV_MCO                       , 1);   //31            0               PLL clock not divided 2 for MCO
  BUNION(CIR, unsigned int,                     //              0               Clock interrupt register
    const LSI_RDYF                      , 1,    //0             0               LSI ready interrupt flag
    const LSE_RDYF                      , 1,    //1             0               LSE ready interrupt flag
    const HSI_RDYF                      , 1,    //2             0               HSI ready interrupt flag
    const HSE_RDYF                      , 1,    //3             0               HSE ready interrupt flag
    const PLL_RDYF                      , 1,    //4             0               PLL ready interrupt flag
    const HSI14_RDYF                    , 1,    //5             0               HSI14 ready interrupt flag
    _reserved                           , 1,
    const CSSF                          , 1,    //7             0               Clock security system interrupt flag
    LSI_RDY_IE                          , 1,    //8             0               LSI ready interrupt enable
    LSE_RDY_IE                          , 1,    //9             0               LSE ready interrupt enable
    HSI_RDY_IE                          , 1,    //10            0               HSI ready interrupt enable
    HSE_RDY_IE                          , 1,    //11            0               HSE ready interrupt enable
    PLL_RDY_IE                          , 1,    //12            0               PLL ready interrupt enable
    HSI14_RDY_IE                        , 1,    //13            0               PLL2 ready interrupt enable
    _reserved1                          , 2,
    LSI_RDYC                            , 1,    //16            0               LSI ready interrupt clear
    LSE_RDYC                            , 1,    //17            0               LSE ready interrupt clear
    HSI_RDYC                            , 1,    //18            0               HSI ready interrupt clear
    HSE_RDYC                            , 1,    //19            0               HSE ready interrupt clear
    PLL_RDYC                            , 1,    //20            0               PLL ready interrupt clear
    HSI14_RDYC                          , 1,    //21            0               PLL2 ready interrupt clear
    _reserved2                          , 1,
    CSSC                                , 1,    //23            0               Clock security system interrupt clear
    _reserved3                          , 8);
  BUNION(APB2_RSTR, unsigned int,               //                              APB2 peripheral reset register
    SYS_CFG                             , 1,    //0             0               SYSCFG reset
    _reserved                           , 4,
    UART6                               , 1,    //5             0               USART6 reset
    _reserved1                          , 3,
    ADC                                 , 1,    //9             0               ADC 1 interface reset
    _reserved2                          , 1,
    TIM1                                , 1,    //11            0               TIM1 timer reset
    SPI1                                , 1,    //12            0               SPI1 reset
    _reserved3                          , 1,
    UART1                               , 1,    //14            0               UART1 reset
    _reserved4                          , 1,
    TIM15                               , 1,    //16            0               TIM15 timer reset
    TIM16                               , 1,    //17            0               TIM10 timer reset
    TIM17                               , 1,    //18            0               TIM11 timer reset
    _reserved5                          , 3,
    DBGMCU                              , 1,    //22            0               Debug MCU reset
    _reserved6                          , 9);
  BUNION(APB1_RSTR, unsigned int,               //                              APB1 peripheral reset register
    _reserved                           , 1,
    TIM3                                , 1,    //1             0               TIM3 timer reset
    _reserved1                          , 2,
    TIM6                                , 1,    //4             0               TIM6 timer reset
    TIM7                                , 1,    //5             0               TIM7 timer reset
    _reserved2                          , 1,
    TIM14                               , 1,    //8             0               TIM14 timer reset
    _reserved3                          , 2,
    WWDG                                , 1,    //11            0               Window watchdog reset
    _reserved4                          , 2,
    SPI2                                , 1,    //14            0               SPI2 reset
    _reserved5                          , 2,
    UART2                               , 1,    //17            0               UART2 reset
    UART3                               , 1,    //18            0               UART3 reset
    UART4                               , 1,    //19            0               UART4 reset
    UART5                               , 1,    //20            0               UART5 reset
    I2C1                                , 1,    //21            0               I2C1 reset
    I2C2                                , 1,    //22            0               I2C2 reset
    USB                                 , 1,    //23            0               USB reset
    _reserved6                          , 4,
    PWR                                 , 1,    //28            0               Power interface reset
    _reserved7                          , 3);
  BUNION(AHB_ENR, unsigned int,                 //                              AHB peripheral clock enable register
    DMA1                                , 1,    //0             0               DMA1 clock enable
    _reserved                           , 1,
    SRAM                                , 1,    //2             1               SRAM interface clock enable
    _reserved1                          , 1,
    FLITF                               , 1,    //4             1               FLITF clock enable
    _reserved2                          , 1,
    CRC                                 , 1,    //6             0               CRC clock enable
    _reserved3                          , 10,
    IOA                                 , 1,    //17            0
    IOB                                 , 1,    //18            0
    IOC                                 , 1,    //19            0
    IOD                                 , 1,    //20            0
    _reserved4                          , 1,
    IOF                                 , 1,    //22            0
    _reserved5                          , 9);
  BUNION(APB2_ENR, unsigned int,                //                              APB2 peripheral clock enable register
    SYSCFG                              , 1,    //0             0               Alternate function IO clock enable
    _reserved                           , 4,
    UART6                               , 1,    //5             0
    _reserved1                          , 3,
    ADC                                 , 1,    //9             0               ADC 1 interface clock enable
    _reserved2                          , 1,
    TIM1                                , 1,    //11            0               TIM1 timer clock enable
    SPI1                                , 1,    //12            0               SPI1 clock enable
    _reserved3                          , 1,
    UART1                               , 1,    //14            0               UART1 clock enable
    _reserved4                          , 1,
    TIM15                               , 1,    //16            0               TIM15 timer clock enable
    TIM16                               , 1,    //17            0               TIM16 timer clock enable
    TIM17                               , 1,    //18            0               TIM17 timer clock enable
    _reserved5                          , 3,
    DBGMCU                              , 1,    //22            0               MCU debug module clock enable
    _reserved6                          , 9);
  BUNION(APB1_ENR, unsigned int,                //                              APB1 peripheral clock enable register
    _reserved                           , 1,
    TIM3                                , 1,    //1             0               TIM3 timer clock enable
    _reserved1                          , 2,
    TIM6                                , 1,    //4             0               TIM6 timer clock enable
    TIM7                                , 1,    //5             0               TIM7 timer clock enable
    _reserved2                          , 2,
    TIM14                               , 1,    //8             0               TIM14 timer clock enable
    _reserved3                          , 2,
    WWDG                                , 1,    //11            0               Window watchdog clock enable
    _reserved4                          , 2,
    SPI2                                , 1,    //14            0               SPI 2 clock enable
    _reserved5                          , 2,
    UART2                               , 1,    //17            0               UART2 clock enable
    UART3                               , 1,    //18            0               UART3 clock enable
    UART4                               , 1,    //19            0               UART4 clock enable
    UART5                               , 1,    //20            0               UART5 clock enable
    I2C1                                , 1,    //21            0               I2C1 clock enable
    I2C2                                , 1,    //22            0               I2C2 clock enable
    USB                                 , 1,    //23            0               USB clock enable
    _reserved6                          , 4,
    PWR                                 , 1,    //28            0               Power interface clock enable
    _reserved7                          , 3);
  BUNION(BDCR, unsigned int,                    //                              Backup domain control register
    LSE_ON                              , 1,    //0             0               External low-speed oscillator enable
    const LSE_RDY                       , 1,    //1             0               External low-speed oscillator ready
    LSE_BYP                             , 1,    //2             0               External low-speed oscillator bypass
    LSE_DRV                             , 2,    //3-4           0               LSE oscillator drive capability
    _reserved                           , 3,
    RTC_SEL                             , 2,    //8-9           0               RTC clock source selection
    _reserved1                          , 5,
    RTC_EN                              , 1,    //15            0               RTC clock enable
    BD_RST                              , 1,    //16            0               Backup domain software reset
    _reserved2                          , 15);
  BUNION(CSR, unsigned int,                     //                              Control/status register
    LSI_ON                              , 1,    //0             0               Internal low-speed oscillator enable
    const LSI_RDY                       , 1,    //1             0               Internal low-speed oscillator ready
    _reserved                           , 21,
    const V18PWR_RSTF                   , 1,    //23            -               Reset flag of the 1.8 V domain
    RMVF                                , 1,    //24            0               Remove reset flag
    const OB_LRSTF                      , 1,    //25            -               Option byte loader reset flag
    const PIN_RSTF                      , 1,    //26            1               1: PIN reset flag
    const POR_RSTF                      , 1,    //27            1               1: POR/PDR reset flag
    const SFT_RSTF                      , 1,    //28            0               Software reset flag
    const IWDG_RSTF                     , 1,    //29            0               Independent watchdog reset flag
    const WWDG_RSTF                     , 1,    //30            0               Window watchdog reset flag
    const LPW_RSTF                      , 1);   //31            0               Low-power reset flag
  BUNION(AHB_RSTR, unsigned int,                //                              AHB peripheral clock reset register
    _reserved                           , 17,
    IOA                                 , 1,    //17
    IOB                                 , 1,    //18
    IOC                                 , 1,    //19
    IOD                                 , 1,    //20
    _reserved1                          , 1,
    IOF                                 , 1,    //22
    _reserved2                          , 9);
  BUNION(CFGR2, unsigned int,                   //                              Clock configuration register 2
    PRE_DIV                             , 4,    //0:3           0               PREDIV division factor
    _reserved                           , 28);
} RCC_TypeDef;
//==============================================================================================================================================================
//===========================================================       LEVEL 1      ===============================================================================
//==============================================================================================================================================================
typedef struct
{
  enum
  {
    RCC_SOURCE_HSI              = 0,
    RCC_SOURCE_HSE              = 1,
    RCC_SOURCE_PLL              = 2,
  } Source;                                     //0-1           0
  union
  {
    unsigned int REG;
    struct
    {
      unsigned int _reserved            : 16;
      enum
      {
        PLL_SOURCE_HSI_DIV_2    = 0,
        PLL_SOURCE_HSE          = 1,
        PLL_SOURCE_HSE_DIV_2    = 3,
      } Source                          : 2;    //16-17         0
      unsigned int Multiple             : 4;    //18:21         (16 - 2)        F_SYS = F_PLL * (Multiple + 2)
      unsigned int _reserved1           : 10;
    } BITS;
  } PLL;
  union
  {
    unsigned int REG;
    struct
    {
      unsigned int _reserved            : 4;
      enum
      {
        AHB_PRESCALE_1          = 0 ,
        AHB_PRESCALE_2          = 8 ,
        AHB_PRESCALE_4          = 9 ,
        AHB_PRESCALE_8          = 10,
        AHB_PRESCALE_16         = 11,
        AHB_PRESCALE_64         = 12,
        AHB_PRESCALE_128        = 13,
        AHB_PRESCALE_256        = 14,
        AHB_PRESCALE_512        = 15,
      } AHB                             : 4;    //4:7           0               max 72MHz
      enum
      {
        APB_PRESCALE_1          = 0,
        APB_PRESCALE_2          = 4,
        APB_PRESCALE_4          = 5,
        APB_PRESCALE_8          = 6,
        APB_PRESCALE_16         = 7,
      } APB1                            : 3,    //8:10          4               max 36MHz
        APB2                            : 3;    //11:13         0               max 72MHz
      enum
      {
        ADC_PRESCALE_2          = 0,
        ADC_PRESCALE_4          = 1,
        ADC_PRESCALE_6          = 2,
        ADC_PRESCALE_8          = 3,
      } ADC                             : 2;    //14-15         0               max 14MHz
      unsigned int _reserved1           : 6;
      unsigned int USB_NotDiv           : 1;    //22            1               0 : USB = F_SYS / 1.5
      unsigned int _reserved2           : 9;
    } BITS;
  } Prescale;
} RCCInit_TypeDef;
/*
+) EXAMPLE:
//RCC: Source = HSI (8MHz); PLL: Source = HSI/2 (4MHz) & Multiple = 16; AHB = 8MHz (max 72Mhz), APB1 = 4MHz (max 36MHz), APB2 = 8MHz (max 72Mhz), ADC = 4MHz (max 14Mhz), USB = must 48MHz
RCCInit_TypeDef RCCInit = (RCCInit_TypeDef){
  .Source = RCC_SOURCE_HSI,
  .PLL = {.BITS = { .Source = PLL_SOURCE_HSI_DIV_2, .Multiple = 14, }},         //Real multiple += 2
  .Prescale = {.BITS = { .AHB = AHB_PRESCALE_1, .APB1 = APB_PRESCALE_2, .APB2 = APB_PRESCALE_1, .ADC = ADC_PRESCALE_2, .USB_NotDiv = 1, }},     
};
RCC_Init(&RCC, &RCCInit);
+) NOTE:
FSYS > 24MHz, "FLASH.ACR.BITS.LATENCY = 1;" (wait 1 cycle to access flash)
FSYS > 48MHz, "FLASH.ACR.BITS.LATENCY = 2;" (wait 2 cycle to access flash)
*/
void RCC_Init(volatile RCC_TypeDef* RCC, const RCCInit_TypeDef* RCCInit);
//==============================================================================================================================================================

#endif