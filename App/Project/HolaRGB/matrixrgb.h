#ifndef __matrixrgb_h
#define __matrixrgb_h
#include "stm32f10x.h"
#include "stdlib.h"
#define ROW1_ACTIVE   GPIO_ResetBits(ROW1_Port, ROW1_Pin)
#define ROW1_IDLE     GPIO_SetBits(ROW1_Port, ROW1_Pin)

#define ROW2_ACTIVE   GPIO_ResetBits(ROW2_Port, ROW2_Pin)
#define ROW2_IDLE     GPIO_SetBits(ROW2_Port, ROW2_Pin)

#define ROW3_ACTIVE   GPIO_ResetBits(ROW3_Port, ROW3_Pin)
#define ROW3_IDLE     GPIO_SetBits(ROW3_Port, ROW3_Pin)

#define ROW4_ACTIVE   GPIO_ResetBits(ROW4_Port, ROW4_Pin)
#define ROW4_IDLE     GPIO_SetBits(ROW4_Port, ROW4_Pin)

#define LAT_ACTIVE    GPIO_ResetBits(LAT_Port, LAT_Pin)
#define LAT_IDLE      GPIO_SetBits(LAT_Port, LAT_Pin)

#define SCLK_ACTIVE   GPIO_ResetBits(SCLK_Port, SCLK_Pin)
#define SCLK_IDLE     GPIO_SetBits(SCLK_Port, SCLK_Pin)

#define SDA1_ACTIVE   GPIO_ResetBits(SDA1_Port, SDA1_Pin)
#define SDA1_IDLE     GPIO_SetBits(SDA1_Port, SDA1_Pin)

#define SDA2_ACTIVE   GPIO_ResetBits(SDA2_Port, SDA2_Pin)
#define SDA2_IDLE     GPIO_SetBits(SDA2_Port, SDA2_Pin)

#define SDA3_ACTIVE   GPIO_ResetBits(SDA3_Port, SDA3_Pin)
#define SDA3_IDLE     GPIO_SetBits(SDA3_Port, SDA3_Pin)

#define SDA4_ACTIVE   GPIO_ResetBits(SDA4_Port, SDA4_Pin)
#define SDA4_IDLE     GPIO_SetBits(SDA4_Port, SDA4_Pin)

#define LAT_Pin   GPIO_Pin_12
#define LAT_Speed GPIO_Speed_50MHz
#define LAT_Mode  GPIO_Mode_Out_PP
#define LAT_Port  GPIOB
#define LAT_Bus   RCC_APB2Periph_GPIOB

#define SCLK_Pin   GPIO_Pin_13
#define SCLK_Speed GPIO_Speed_50MHz
#define SCLK_Mode  GPIO_Mode_Out_PP
#define SCLK_Port  GPIOB
#define SCLK_Bus   RCC_APB2Periph_GPIOB

#define SDA1_Pin   GPIO_Pin_9
#define SDA1_Speed GPIO_Speed_50MHz
#define SDA1_Mode  GPIO_Mode_Out_PP
#define SDA1_Port  GPIOA
#define SDA1_Bus   RCC_APB2Periph_GPIOA

#define SDA2_Pin   GPIO_Pin_8
#define SDA2_Speed GPIO_Speed_50MHz
#define SDA2_Mode  GPIO_Mode_Out_PP
#define SDA2_Port  GPIOA
#define SDA2_Bus   RCC_APB2Periph_GPIOA

#define SDA3_Pin   GPIO_Pin_14
#define SDA3_Speed GPIO_Speed_50MHz
#define SDA3_Mode  GPIO_Mode_Out_PP
#define SDA3_Port  GPIOB
#define SDA3_Bus   RCC_APB2Periph_GPIOB

#define SDA4_Pin   GPIO_Pin_15
#define SDA4_Speed GPIO_Speed_50MHz
#define SDA4_Mode  GPIO_Mode_Out_PP
#define SDA4_Port  GPIOB
#define SDA4_Bus   RCC_APB2Periph_GPIOB

// SDA4 PB15 SDA3 PB14  SDA2 PA8  SDA1 PA9
#define LED_Pin   GPIO_Pin_15
#define LED_Speed GPIO_Speed_50MHz
#define LED_Mode  GPIO_Mode_Out_PP
#define LED_Port  GPIOA
#define LED_Bus   RCC_APB2Periph_GPIOA

#define ROW1_Pin   GPIO_Pin_3
#define ROW1_Speed GPIO_Speed_50MHz
#define ROW1_Mode  GPIO_Mode_Out_PP
#define ROW1_Port  GPIOB
#define ROW1_Bus   RCC_APB2Periph_GPIOB

#define ROW2_Pin   GPIO_Pin_8
#define ROW2_Speed GPIO_Speed_50MHz
#define ROW2_Mode  GPIO_Mode_Out_PP
#define ROW2_Port  GPIOB
#define ROW2_Bus   RCC_APB2Periph_GPIOB

#define ROW3_Pin   GPIO_Pin_9
#define ROW3_Speed GPIO_Speed_50MHz
#define ROW3_Mode  GPIO_Mode_Out_PP
#define ROW3_Port  GPIOB
#define ROW3_Bus   RCC_APB2Periph_GPIOB

#define ROW4_Pin   GPIO_Pin_15
#define ROW4_Speed GPIO_Speed_50MHz
#define ROW4_Mode  GPIO_Mode_Out_PP
#define ROW4_Port  GPIOA
#define ROW4_Bus   RCC_APB2Periph_GPIOA

#define DELAY   50

typedef enum
{ BLUE = 0x04,
  RED = 0x02,
  GREEN = 0x01,
  MAGENTA = 0x06,
  YELLOW = 0x03, 
  CYAN = 0x05,
  WHITE = 0x07,
  BLACK = 0x00
}ColorRGB;

typedef enum
{
  SW_in = 0x00,
  SW_out = 0x01
}modeSW;

void MatrixRGB_Config(void);
void ShiftOut4Row(u8 data1, u8 data2, u8 data3, u8 data4);
void MatrixRGB_ScanPWM(void);

void SetPixel(s8 row, u8 col, u8 blue, u8 red, u8 green);
u8 ReadPixel(s8 row, u8 col, u8 color);
void SweepOut(u8 data[]);
void SweepIn(u8 data[]);
u8 Mirror(u8 point);
void SetHalfRow(s8 row, u8 data[], u8 blue, u8 red, u8 green);
void SetFullRow(s8 row, u8 data[], u8 blue, u8 red, u8 green);
void RotateHalf(s8 row);
void RotateReverseHalf(s8 row);
void RotateMatrix(s8 row);
void RotateReverseMatrix(s8 row);
void RollOut(void);
void RollIn(void);
void TransferColor(u8 startColor, u8 endColor, u8 step);
void Spectrum2RGB(u8 color);
void TurnOnHalfRow(s8 row, u8 data[], u8 blue, u8 red, u8 green);
void SetChuVan(u8 x, u8 y, u8 graph, u8 step, u8 color);

void HieuUng1(void);
void HieuUng2(void);
void HieuUng3(u8 mode);
void HieuUng4(void);
void HieuUng5(void);
void HieuUng6(void);
void HieuUng7(void);
void HieuUng8(void);
void HieuUng9(void);
void HieuUng10(u8 mode);
void HieuUng11(void);
void HieuUng12(void);
void HieuUng13(void);
void HieuUng14(void);
void HieuUng15(void);
void HieuUng16(void);
void HieuUng17(void);
void HieuUng18(void);
void HieuUng19(void);
void HieuUng20(void);
void HieuUng21(void);
void HieuUng22(void);
void HieuUng23(u8 mode);
void HieuUng24(void);
void HieuUng25(void);
void HieuUng26(void);
void HieuUng27(void);
void HieuUng28(void);
void HieuUng29(void);
void HieuUng30(void);
void HieuUng31(void);
void HieuUng32(void);
void HieuUng33(void);
void HieuUng34(u8 mode);
void HieuUng35(void);
void HieuUng36(void);
void HieuUng37(void);

ErrorStatus Check(u8 point);
#endif
