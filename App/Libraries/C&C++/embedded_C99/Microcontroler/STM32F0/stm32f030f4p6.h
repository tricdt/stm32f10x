#ifndef _STM32F030F4P6_H_
#define _STM32F030F4P6_H_

#include <cortex_m0.h>

#include <gpio.h>
__root __no_init volatile GPIO_TypeDef GPIOA            @ 0x48000000;
__root __no_init volatile GPIO_TypeDef GPIOB            @ 0x48000400;
__root __no_init volatile GPIO_TypeDef GPIOC            @ 0x48000800;
__root __no_init volatile GPIO_TypeDef GPIOD            @ 0x48000C00;
__root __no_init volatile GPIO_TypeDef GPIOF            @ 0x48001400;

#include <rcc.h>
__root __no_init volatile RCC_TypeDef RCC               @ 0x40021000;

#include <spi.h>
__root __no_init volatile SPI_TypeDef SPI1              @ 0x40013000;

#endif