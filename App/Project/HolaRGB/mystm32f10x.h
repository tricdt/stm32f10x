#ifndef __mystm32f10x_h
#define __mystm32f10x_h
#include "stm32f10x.h"
#define SYSCLK_FREQ_72MHz
static uint8_t  fac_us=0;
static uint16_t fac_ms=0;
typedef struct _PIN {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_TypeDef* GPIOx;
  uint32_t GPIO_Bus;
} PIN;
void SetSysClock(void);
void SetSysClockToHSE(void);
void SetSysClockTo24(void);
void SetSysClockTo36(void);
void SetSysClockTo48(void);
void SetSysClockTo56(void);
void SetSysClockTo72(void);
void NVIC_Configuration(void);
//void Delay(__IO uint32_t nCount);
void Delay(u32 nCount);
void Delayus(u32 nCount);
void delay_init(uint8_t SYSCLK);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);
void TIM2_Config(void);

//#define DB0_Pin   GPIO_Pin_14
//#define DB0_Speed GPIO_Speed_50MHz
//#define DB0_Mode  GPIO_Mode_AF_PP
//#define DB0_Port  GPIOD
//#define DB0_Bus   RCC_APB2Periph_GPIOD

//static PIN pins[]={
//  {{DB0_Pin,DB0_Speed,DB0_Mode},DB0_Port,DB0_Bus}
//};

//uint32_t i;
//  for(i=0;i<sizeof(pins)/sizeof(PIN);i++) {
//    RCC_APB2PeriphClockCmd(pins[i].GPIO_Bus,ENABLE);
//    GPIO_Init(pins[i].GPIOx,&pins[i].GPIO_InitStructure);
//  }

#endif
