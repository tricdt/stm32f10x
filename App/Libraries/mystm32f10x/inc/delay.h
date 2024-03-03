#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"

void delay_init(uint8_t SYSCLK);
void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);

#endif