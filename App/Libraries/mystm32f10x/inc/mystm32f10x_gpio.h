#ifndef __MY_STM32F10x_GPIO_H
#define __MY_STM32F10x_GPIO_H
#include "stm32f10x.h"

void MyGPIO_Deinit(void);
void MyGPIO_Init(GPIO_TypeDef *port, uint16_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, u32 bus);
void MyGPIO_DisableSWJTAG(BitAction disableSW , BitAction disableJtag);
void MyGPIO_SetLevel(GPIO_TypeDef *port, u16 pin, BitAction level);
FlagStatus MyGPIO_GetLevel(GPIO_TypeDef *port, u16 pin);
void MyGPIO_Toggle(GPIO_TypeDef *port, u16 pin);
void MyGPIO_ChangeMode(GPIO_TypeDef *port, uint16_t pin, GPIOMode_TypeDef mode);
#endif