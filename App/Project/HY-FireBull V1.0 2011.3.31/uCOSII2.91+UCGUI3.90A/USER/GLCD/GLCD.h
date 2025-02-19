/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			GLCD.h
** Descriptions:		None
**
**------------------------------------------------------------------------------------------------------
** Created by:			AVRman
** Created date:		2011-3-29
** Version:				2.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:		
********************************************************************************************************/

#ifndef __GLCD_H 
#define __GLCD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdlib.h>

/* Private define ------------------------------------------------------------*/
#define DISP_ORIENTATION  90  /* angle 0 90 */ 

#if  ( DISP_ORIENTATION == 90 ) || ( DISP_ORIENTATION == 270 )

#define  MAX_X  320
#define  MAX_Y  240   

#elif  ( DISP_ORIENTATION == 0 ) || ( DISP_ORIENTATION == 180 )

#define  MAX_X  240
#define  MAX_Y  320   

#endif

/*
#define Set_Cs        GPIO_SetBits(GPIOD , GPIO_Pin_12);
#define Clr_Cs        GPIO_ResetBits(GPIOD , GPIO_Pin_12);

#define Set_Rs        GPIO_SetBits(GPIOD , GPIO_Pin_13);
#define Clr_Rs        GPIO_ResetBits(GPIOD , GPIO_Pin_13);

#define Set_nWr       GPIO_SetBits(GPIOD , GPIO_Pin_14);
#define Clr_nWr       GPIO_ResetBits(GPIOD , GPIO_Pin_14);

#define Set_nRd       GPIO_SetBits(GPIOD , GPIO_Pin_15);
#define Clr_nRd       GPIO_ResetBits(GPIOD , GPIO_Pin_15);

*/
#define Set_Cs        GPIOD->ODR  |= ( 1<<12 );
#define Clr_Cs        GPIOD->ODR  &= ~( 1<<12 );

#define Set_Rs        GPIOD->ODR  |= ( 1<<13 );
#define Clr_Rs        GPIOD->ODR  &= ~( 1<<13 );

#define Set_nWr       GPIOD->ODR  |= ( 1<<14 );
#define Clr_nWr       GPIOD->ODR  &= ~( 1<<14 );

#define Set_nRd       GPIOD->ODR  |= ( 1<<15 );
#define Clr_nRd       GPIOD->ODR  &= ~( 1<<15 );

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

/******************************************************************************
* Function Name  : RGB565CONVERT
* Description    : 24位转换16位
* Input          : - red: R
*                  - green: G 
*				   - blue: B
* Output         : None
* Return         : RGB 颜色值
* Attention		 : None
*******************************************************************************/
#define RGB565CONVERT(red, green, blue)\
(uint16_t)( (( red   >> 3 ) << 11 ) | \
(( green >> 2 ) << 5  ) | \
( blue  >> 3 ))

/* Private function prototypes -----------------------------------------------*/
void LCD_Initializtion(void);
void LCD_Clear(uint16_t Color);
uint16_t LCD_GetPoint(uint16_t Xpos,uint16_t Ypos);
void LCD_SetPoint(uint16_t Xpos,uint16_t Ypos,uint16_t point);
void LCD_DrawLine( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color );
void PutChar( uint16_t Xpos, uint16_t Ypos, uint8_t ASCI, uint16_t charColor, uint16_t bkColor );
void GUI_Text(uint16_t Xpos, uint16_t Ypos, uint8_t *str,uint16_t Color, uint16_t bkColor);
void PutChinese(uint16_t Xpos,uint16_t Ypos,uint8_t *str,uint16_t Color,uint16_t bkColor);
void GUI_Chinese(uint16_t Xpos, uint16_t Ypos, uint8_t *str,uint16_t Color, uint16_t bkColor);
#endif 
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





