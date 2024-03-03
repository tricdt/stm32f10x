#ifndef _STM32F103RCT_H_
#define _STM32F103RCT_H_

/*
+) NOTE:
  -)Any peripheral must enable clock by RCC
*/

#include <cortex_m3.h>
#include <bitband.h>

#include <general_timer.h>
__no_init volatile GENERAL_TIMER_TypeDef TIM2                           @ 0x40000000;
__no_init volatile GENERAL_TIMER_BITBAND_TypeDef TIM2_BITBAND           @ BITBAND_PERIPHERAL_ADDRESS(0x40000000, 0);
__no_init volatile GENERAL_TIMER_TypeDef TIM3                           @ 0x40000400;
__no_init volatile GENERAL_TIMER_BITBAND_TypeDef TIM3_BITBAND           @ BITBAND_PERIPHERAL_ADDRESS(0x40000400, 0);
__no_init volatile GENERAL_TIMER_TypeDef TIM4                           @ 0x40000800;
__no_init volatile GENERAL_TIMER_BITBAND_TypeDef TIM4_BITBAND           @ BITBAND_PERIPHERAL_ADDRESS(0x40000800, 0);
__no_init volatile GENERAL_TIMER_TypeDef TIM5                           @ 0x40000C00;
__no_init volatile GENERAL_TIMER_BITBAND_TypeDef TIM5_BITBAND           @ BITBAND_PERIPHERAL_ADDRESS(0x40000C00, 0);

#include <basic_timer.h>
__no_init volatile BASIC_TIMER_TypeDef TIM6                             @ 0x40001000;
__no_init volatile BASIC_TIMER_BITBAND_TypeDef TIM6_BITBAND             @ BITBAND_PERIPHERAL_ADDRESS(0x40001000, 0);
__no_init volatile BASIC_TIMER_TypeDef TIM7                             @ 0x40001400;
__no_init volatile BASIC_TIMER_BITBAND_TypeDef TIM7_BITBAND             @ BITBAND_PERIPHERAL_ADDRESS(0x40001400, 0);

#include <rtc.h>
__no_init volatile RTC_TypeDef RTC                                      @ 0x40002800;
__no_init volatile RTC_BITBAND_TypeDef RTC_BITBAND                      @ BITBAND_PERIPHERAL_ADDRESS(0x40002800, 0);

#include <wwdg.h>
__no_init volatile WWDG_TypeDef WWDG                                    @ 0x40002C00;
__no_init volatile WWDG_BITBAND_TypeDef WWDG_BITBAND                    @ BITBAND_PERIPHERAL_ADDRESS(0x40002C00, 0);

#include <idwg.h>
__no_init volatile IDWG_TypeDef IDWG                                    @ 0x40003000;
__no_init volatile IDWG_BITBAND_TypeDef IDWG_BITBAND                    @ BITBAND_PERIPHERAL_ADDRESS(0x40003000, 0);

#include <spi.h>
__no_init volatile SPI_TypeDef SPI2                                     @ 0x40003800;
__no_init volatile SPI_BITBAND_TypeDef SPI2_BITBAND                     @ BITBAND_PERIPHERAL_ADDRESS(0x40003800, 0);
__no_init volatile SPI_TypeDef SPI3                                     @ 0x40003C00;
__no_init volatile SPI_BITBAND_TypeDef SPI3_BITBAND                     @ BITBAND_PERIPHERAL_ADDRESS(0x40003C00, 0);
__no_init volatile SPI_TypeDef SPI1                                     @ 0x40013000;
__no_init volatile SPI_BITBAND_TypeDef SPI1_BITBAND                     @ BITBAND_PERIPHERAL_ADDRESS(0x40013000, 0);

#include <uart.h>
__no_init volatile UART_TypeDef UART2                                   @ 0x40004400;
__no_init volatile UART_BITBAND_TypeDef UART2_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40004400, 0);
__no_init volatile UART_TypeDef UART3                                   @ 0x40004800;
__no_init volatile UART_BITBAND_TypeDef UART3_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40004800, 0);
__no_init volatile UART_TypeDef UART4                                   @ 0x40004C00;
__no_init volatile UART_BITBAND_TypeDef UART4_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40004C00, 0);
__no_init volatile UART_TypeDef UART5                                   @ 0x40005000;
__no_init volatile UART_BITBAND_TypeDef UART5_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40005000, 0);
__no_init volatile UART_TypeDef UART1                                   @ 0x40013800;
__no_init volatile UART_BITBAND_TypeDef UART1_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40013800, 0);

#include <i2c.h>
__no_init volatile I2C_TypeDef I2C1                                     @ 0x40005400;
__no_init volatile I2C_BITBAND_TypeDef I2C1_BITBAND                     @ BITBAND_PERIPHERAL_ADDRESS(0x40005400, 0);
__no_init volatile I2C_TypeDef I2C2                                     @ 0x40005800;
__no_init volatile I2C_BITBAND_TypeDef I2C2_BITBAND                     @ BITBAND_PERIPHERAL_ADDRESS(0x40005800, 0);

//#include <usb.h>
//__no_init volatile USB_TypeDef USB                                      @ 0x40005C00;
//__no_init volatile USB_BITBAND_TypeDef USB_BITBAND                      @ BITBAND_PERIPHERAL_ADDRESS(0x40005C00, 0);

//#include <bxcan.h>
//__no_init volatile BXCAN_TypeDef BXCAN                                @ 0x40006400;

#include <bkp.h>
__no_init volatile BKP_TypeDef BKP                                      @ 0x40006C00;
__no_init volatile BKP_BITBAND_TypeDef BKP_BITBAND                      @ BITBAND_PERIPHERAL_ADDRESS(0x40006C00, 0);

#include <pwr.h>
__no_init volatile PWR_TypeDef PWR                                      @ 0x40007000;
__no_init volatile PWR_BITBAND_TypeDef PWR_BITBAND                      @ BITBAND_PERIPHERAL_ADDRESS(0x40007000, 0);

#include <dac.h>
__no_init volatile DAC_TypeDef DAC                                      @ 0x40007400;
__no_init volatile DAC_BITBAND_TypeDef DAC_BITBAND                      @ BITBAND_PERIPHERAL_ADDRESS(0x40007400, 0);

#include <afio.h>
__no_init volatile AFIO_TypeDef AFIO                                    @ 0x40010000;
__no_init volatile AFIO_BITBAND_TypeDef AFIO_BITBAND                    @ BITBAND_PERIPHERAL_ADDRESS(0x40010000, 0);  

#include <exti.h>
__no_init volatile EXTI_TypeDef EXTI                                    @ 0x40010400;
__no_init volatile EXTI_BITBAND_TypeDef EXTI_BITBAND                    @ BITBAND_PERIPHERAL_ADDRESS(0x40010400, 0);  

#include <gpio.h>
__no_init volatile GPIO_TypeDef GPIOA                                   @ 0x40010800;
__no_init volatile GPIO_BITBAND_TypeDef GPIOA_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40010800, 0);
__no_init volatile GPIO_TypeDef GPIOB                                   @ 0x40010C00;
__no_init volatile GPIO_BITBAND_TypeDef GPIOB_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40010C00, 0);
__no_init volatile GPIO_TypeDef GPIOC                                   @ 0x40011000;
__no_init volatile GPIO_BITBAND_TypeDef GPIOC_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40011000, 0);
__no_init volatile GPIO_TypeDef GPIOD                                   @ 0x40011400;
__no_init volatile GPIO_BITBAND_TypeDef GPIOD_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40011400, 0);
__no_init volatile GPIO_TypeDef GPIOE                                   @ 0x40011800;
__no_init volatile GPIO_BITBAND_TypeDef GPIOE_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40011800, 0);
__no_init volatile GPIO_TypeDef GPIOF                                   @ 0x40011C00;
__no_init volatile GPIO_BITBAND_TypeDef GPIOF_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40011C00, 0);
__no_init volatile GPIO_TypeDef GPIOG                                   @ 0x40012000;
__no_init volatile GPIO_BITBAND_TypeDef GPIOG_BITBAND                   @ BITBAND_PERIPHERAL_ADDRESS(0x40012000, 0);

#include <adc.h>
__no_init volatile ADC_TypeDef ADC1                                     @ 0x40012400;
__no_init volatile ADC_BITBAND_TypeDef ADC1_BITBAND                     @ BITBAND_PERIPHERAL_ADDRESS(0x40012400, 0);
__no_init volatile ADC_TypeDef ADC2                                     @ 0x40012800;
__no_init volatile ADC_BITBAND_TypeDef ADC2_BITBAND                     @ BITBAND_PERIPHERAL_ADDRESS(0x40012800, 0);
__no_init volatile ADC_TypeDef ADC3                                     @ 0x40013C00;
__no_init volatile ADC_BITBAND_TypeDef ADC3_BITBAND                     @ BITBAND_PERIPHERAL_ADDRESS(0x40013C00, 0);

#include <advanced_timer.h>
__no_init volatile ADVANCED_TIMER_TypeDef TIM1                          @ 0x40012C00;
__no_init volatile ADVANCED_TIMER_BITBAND_TypeDef TIM1_BITBAND          @ BITBAND_PERIPHERAL_ADDRESS(0x40012C00, 0);
__no_init volatile ADVANCED_TIMER_TypeDef TIM8                          @ 0x40013400;
__no_init volatile ADVANCED_TIMER_BITBAND_TypeDef TIM8_BITBAND          @ BITBAND_PERIPHERAL_ADDRESS(0x40013400, 0);

#include <sdio.h>
__no_init volatile SDIO_TypeDef SDIO                                    @ 0x40018000;
__no_init volatile SDIO_BITBAND_TypeDef SDIO_BITBAND                    @ BITBAND_PERIPHERAL_ADDRESS(0x40018000, 0);

#include <dma.h>
__no_init volatile DMA_TypeDef DMA1                                     @ 0x40020000;
__no_init volatile DMA_BITBAND_TypeDef DMA1_BITBAND                     @ BITBAND_PERIPHERAL_ADDRESS(0x40020000, 0);

#include <rcc.h>
__root __no_init volatile RCC_TypeDef RCC                               @ 0x40021000;
__root __no_init volatile RCC_BITBAND_TypeDef RCC_BITBAND               @ BITBAND_PERIPHERAL_ADDRESS(0x40021000, 0); 

#include <flash.h>
__no_init volatile FLASH_TypeDef FLASH                                  @ 0x40022000;
__no_init volatile FLASH_BITBAND_TypeDef FLASH_BITBAND                  @ BITBAND_PERIPHERAL_ADDRESS(0x40022000, 0);

#include <crc.h>
__no_init volatile CRC_TypeDef CRC                                      @ 0x40022000;
__no_init volatile CRC_BITBAND_TypeDef CRC_BITBAND                      @ BITBAND_PERIPHERAL_ADDRESS(0x40022000, 0);

#endif