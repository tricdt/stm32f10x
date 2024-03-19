#ifndef __MYSTM32F10X_DELAY_H
#define __MYSTM32F10X_DELAY_H
#include "stm32f10x.h"

void delay_init(uint8_t SYSCLK);
void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);
u32 DWTDelay_Init(void);



__STATIC_INLINE void DWTDelay_us(volatile u32 au32Microseconds){
    u32 au32InitialTicks = DWT->CYCCNT;
    u32 au32Ticks = (SystemCoreClock / 1000000);
    au32Microseconds *= au32Ticks;
    while ((DWT->CYCCNT - au32InitialTicks) < au32Microseconds - au32Ticks);
}

// This Function Provides Delay In Milliseconds Using DWT
__STATIC_INLINE void DWTDelay_ms(volatile u32 au32Milliseconds) {
    u32 au32InitialTicks = DWT->CYCCNT;
    u32 au32Ticks = (SystemCoreClock / 1000);
    au32Milliseconds *= au32Ticks;
    while ((DWT->CYCCNT - au32InitialTicks) < au32Milliseconds);
}


__STATIC_INLINE u32 getSystemTicks() {
    return DWT->CYCCNT;
}

__STATIC_INLINE u32 currentMilliSeconds() {
    return (getSystemTicks() / (SystemCoreClock / 1000));
}

__STATIC_INLINE uint64_t currentMicroSeconds() {
    return (getSystemTicks() / (SystemCoreClock / 1000000));
}


#endif