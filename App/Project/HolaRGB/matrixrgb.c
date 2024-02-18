#include "matrixrgb.h"
#include "mystm32f10x.h"
u8 matrix_temp[2*23];
u8 matrixPWM[2][368];
s8 peak[60];
u8 color[60];
u8 bMatrixByte;
u8 bit_pwm = 0;
u8 bluePWM, redPWM, greenPWM;
u16 timerClock4S[3] = {64, 128};
u8 chuvan[7] = {0x00, 0x74, 0x14, 0x7C, 0x50, 0x5C, 0x00};
void MatrixRGB_Config(void)
{
  GPIO_DeInit(GPIOA);
  GPIO_DeInit(GPIOB);
  GPIO_InitTypeDef GPIO_InitStructure;  
  RCC_APB2PeriphClockCmd(LAT_Bus,ENABLE);
  GPIO_InitStructure.GPIO_Pin = LAT_Pin;
  GPIO_InitStructure.GPIO_Mode = LAT_Mode;
  GPIO_InitStructure.GPIO_Speed = LAT_Speed;
  GPIO_Init(LAT_Port, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(SCLK_Bus,ENABLE);
  GPIO_InitStructure.GPIO_Pin = SCLK_Pin;
  GPIO_InitStructure.GPIO_Mode = SCLK_Mode;
  GPIO_InitStructure.GPIO_Speed = SCLK_Speed;
  GPIO_Init(SCLK_Port, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(SDA1_Bus,ENABLE);
  GPIO_InitStructure.GPIO_Pin = SDA1_Pin;
  GPIO_InitStructure.GPIO_Mode = SDA1_Mode;
  GPIO_InitStructure.GPIO_Speed = SDA1_Speed;
  GPIO_Init(SDA1_Port, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(SDA2_Bus,ENABLE);
  GPIO_InitStructure.GPIO_Pin = SDA2_Pin;
  GPIO_InitStructure.GPIO_Mode = SDA2_Mode;
  GPIO_InitStructure.GPIO_Speed = SDA2_Speed;
  GPIO_Init(SDA2_Port, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(SDA3_Bus,ENABLE);
  GPIO_InitStructure.GPIO_Pin = SDA3_Pin;
  GPIO_InitStructure.GPIO_Mode = SDA3_Mode;
  GPIO_InitStructure.GPIO_Speed = SDA3_Speed;
  GPIO_Init(SDA3_Port, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(SDA4_Bus,ENABLE);
  GPIO_InitStructure.GPIO_Pin = SDA4_Pin;
  GPIO_InitStructure.GPIO_Mode = SDA4_Mode;
  GPIO_InitStructure.GPIO_Speed = SDA4_Speed;
  GPIO_Init(SDA4_Port, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(ROW1_Bus,ENABLE);
  GPIO_InitStructure.GPIO_Pin = ROW1_Pin;
  GPIO_InitStructure.GPIO_Mode = ROW1_Mode;
  GPIO_InitStructure.GPIO_Speed = ROW1_Speed;
  GPIO_Init(ROW1_Port, &GPIO_InitStructure);
  /*
  PA13 and PA14 are used as SWIO and SWCLK for SWD debugging; PB3, PB4, PA13, PA14 and PA15 are used together for JTAG */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //Open the multiplexed clock in the clock configuration:
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //JTAG-DP Disabled and SW-DP Enabled
  RCC_APB2PeriphClockCmd(ROW2_Bus,ENABLE);
  GPIO_InitStructure.GPIO_Pin = ROW2_Pin;
  GPIO_InitStructure.GPIO_Mode = ROW2_Mode;
  GPIO_InitStructure.GPIO_Speed = ROW2_Speed;
  GPIO_Init(ROW2_Port, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(ROW3_Bus,ENABLE);
  GPIO_InitStructure.GPIO_Pin = ROW3_Pin;
  GPIO_InitStructure.GPIO_Mode = ROW3_Mode;
  GPIO_InitStructure.GPIO_Speed = ROW3_Speed;
  GPIO_Init(ROW3_Port, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(ROW4_Bus,ENABLE);
  GPIO_InitStructure.GPIO_Pin = ROW4_Pin;
  GPIO_InitStructure.GPIO_Mode = ROW4_Mode;
  GPIO_InitStructure.GPIO_Speed = ROW4_Speed;
  GPIO_Init(ROW4_Port, &GPIO_InitStructure);
  
  ROW1_IDLE;
  ROW2_IDLE;
  ROW3_IDLE;
  ROW4_IDLE;
  for(u8 pwm = 0; pwm < 3; pwm ++)
  {
    for(u16 i=0; i<368; i++)
    {
      matrixPWM[pwm][i] = 0x00;
    }
  }
  for(u8 i=0; i<60; i++)
    peak[i] = 0x00;
  for(u8 i=0; i<46; i++)
    matrix_temp[i] = 0x00;
}

void ShiftOut4Row(u8 data1, u8 data2, u8 data3, u8 data4)
{
  u8 refine = 0x01;
  for(u8 i=0; i<8; i++)
  {
    SDA1_Port ->ODR &= ~0x0300;
    SDA1_Port ->ODR |=((~data1)&refine)<<(9-i);
    SDA2_Port ->ODR |=((~data2)&refine)<<(8-i);
    SDA3_Port ->ODR &= ~0xC000;
    SDA3_Port ->ODR |=((~data3)&refine)<<(14-i);
    SDA4_Port ->ODR |=((~data4)&refine)<<(15-i);
    refine=refine<<1;
    SCLK_ACTIVE;
    SCLK_IDLE;
  }
}

void MatrixRGB_ScanPWM(void)
{
  TIM2->PSC = timerClock4S[bit_pwm];
  TIM2->EGR = 1;
  ROW1_IDLE; ROW2_IDLE; ROW3_IDLE; ROW4_IDLE;
  for(s8 i=22; i>=0; i--)
    ShiftOut4Row(matrixPWM[bit_pwm][23 * bMatrixByte + i], matrixPWM[bit_pwm][92 + 23 * bMatrixByte + i], matrixPWM[bit_pwm][184 + 23 * bMatrixByte + i], matrixPWM[bit_pwm][276 + 23 * bMatrixByte + i]);
  LAT_ACTIVE;
  LAT_IDLE;
  switch(bMatrixByte)
  {
    case 0:
      ROW1_ACTIVE;
      break;
    case 1:
      ROW2_ACTIVE;
      break;
    case 2:
      ROW3_ACTIVE;
      break;
    case 3:
      ROW4_ACTIVE;
      break;   
  }
  bit_pwm++;
  if(bit_pwm==2) 
  {
    bit_pwm = 0;
    bMatrixByte ++;
    if(bMatrixByte == 4) bMatrixByte = 0;
  }
}

void SetPixel(s8 row, u8 col, u8 blue, u8 red, u8 green)
{
  u8 color[3] = {blue, red, green};
  if(row>-1&&row<16)
    for(u8 i=0; i<3; i++)
    {
      matrixPWM[0][(col*3 + i)/8 + 23*row] &=~0x80>>((col*3 + i) % 8);
      matrixPWM[0][(col*3 + i)/8 + 23*row] |=(color[i] & 0x01)<<(7- (col*3 + i)%8);
      matrixPWM[1][(col*3 + i)/8 + 23*row] &=~0x80>>((col*3 + i) % 8);
      matrixPWM[1][(col*3 + i)/8 + 23*row] |=((color[i] & 0x02)>>1)<<(7- (col*3 + i)%8);
    }
  else
    for(u8 i=0; i<3; i++)
    {
      matrix_temp[(col*3 + i)/8] &=~0x80>>((col*3 + i) % 8);
      matrix_temp[(col*3 + i)/8] |=(color[i] & 0x01)<<(7- (col*3 + i)%8);
      matrix_temp[(col*3 + i)/8 + 23] &=~0x80>>((col*3 + i) % 8);
      matrix_temp[(col*3 + i)/8 + 23] |=((color[i] & 0x02)>>1)<<(7- (col*3 + i)%8);
    }
}

u8 ReadPixel(s8 row, u8 col, u8 color)
{
  if(row==-1)
    return (matrix_temp[(col*3 + 2 - (color>>1))/8] & (0x80>>((col*3 + 2 - (color>>1)) % 8)))>>(7-((col*3 + 2 - (color>>1)) % 8))\
      |(((matrix_temp[(col*3 + 2 - (color>>1))/8 + 23] & (0x80>>((col*3 + 2 - (color>>1)) % 8)))>>(7-((col*3 + 2 - (color>>1)) % 8)))<<1);
  else
    return (matrixPWM[0][(col*3 + 2 - (color>>1))/8 + 23*row] & (0x80>>((col*3 + 2 - (color>>1)) % 8)))>>(7-((col*3 + 2 - (color>>1)) % 8))\
      |(((matrixPWM[1][(col*3 + 2 - (color>>1))/8 + 23*row] & (0x80>>((col*3 + 2 - (color>>1)) % 8)))>>(7-((col*3 + 2 - (color>>1)) % 8)))<<1);
}

void SweepOut(u8 data[])
{
  for(u8 j=0; j<23; j++)
  {
    for(u8 i=0; i<15; i++)
    {
      matrixPWM[0][23*(15-i) + j] = matrixPWM[0][23*(14-i) + j];
      matrixPWM[1][23*(15-i) + j] = matrixPWM[1][23*(14-i) + j];
    }

    matrixPWM[0][j] = matrix_temp[j];
    matrixPWM[1][j] = matrix_temp[j + 23];
  }
}

void RollOut(void)
{
  for(u8 j=0; j<23; j++)
  {
    u8 temp[2]={0,0};
    temp[0] = matrixPWM[0][23*15 + j];
    temp[1] = matrixPWM[1][23*15 + j];
    for(u8 i=0; i<15; i++)
    {
      matrixPWM[0][23*(15-i) + j] = matrixPWM[0][23*(14-i) + j];
      matrixPWM[1][23*(15-i) + j] = matrixPWM[1][23*(14-i) + j];
    }

    matrixPWM[0][j] = temp[0];
    matrixPWM[1][j] = temp[1];
  }
}

void SweepIn(u8 data[])
{
  for(u8 j=0; j<23; j++)
  {
    for(u8 i=0; i<15; i++)
    {
      matrixPWM[0][23*i + j] = matrixPWM[0][23*(i+1) + j];
      matrixPWM[1][23*i + j] = matrixPWM[1][23*(i+1) + j];
    }

    matrixPWM[0][345 + j] = matrix_temp[j];
    matrixPWM[1][345 + j] = matrix_temp[j + 23];
  }
}

void RollIn(void)
{
  for(u8 j=0; j<23; j++)
  {
    u8 temp[2]={0};
    temp[0] = matrixPWM[0][j];
    temp[1] = matrixPWM[1][j];
    for(u8 i=0; i<15; i++)
    {
      matrixPWM[0][23*i + j] = matrixPWM[0][23*(i+1) + j];
      matrixPWM[1][23*i + j] = matrixPWM[1][23*(i+1) + j];
    }

    matrixPWM[0][345 + j] = temp[0];
    matrixPWM[1][345 + j] = temp[1];
  }
}


//9          10         11         21         22
//1001 0010, 0100 1001, 0010 0100, 1001 0010, 0100 0000
void RotateHalf(s8 row)
{
  if(row>-1&&row<16)
    for(u8 j=0; j<2; j++)
    {
      u8 temp = matrixPWM[j][11 + 23*row] & 0x07;
      for(u8 i=0; i<11; i++)
      {
        matrixPWM[j][11-i + 23*row] = (matrixPWM[j][11-i + 23*row]>>3) | ((matrixPWM[j][10-i + 23*row]&0x07)<<5);
      }
      matrixPWM[j][11 + 23*row] = (matrixPWM[j][11 + 23*row] & 0xF8)|temp;
      matrixPWM[j][23*row] = matrixPWM[j][23*row] >> 3;
    }
  else
    for(u8 j=0; j<2; j++)
    {
      u8 temp = matrix_temp[11 + 23*j] & 0x07;
      for(u8 i=0; i<11; i++)
      {
        matrix_temp[11-i + 23*j] = (matrix_temp[11-i + 23*j]>>3) | ((matrix_temp[10-i + 23*j]&0x07)<<5);
      }
      matrix_temp[11 + 23*j] = (matrix_temp[11 + 23*j] & 0xF8)|temp;
      matrix_temp[23*j] = matrix_temp[23*j] >> 3;
    }
}

void RotateReverseHalf(s8 row)
{
  if(row>-1&&row<16)
  {
    for(u8 j=0; j<2; j++)
    {
      u8 temp = matrixPWM[j][11 + 23*row] & 0x07;
      for(u8 i=0; i<11; i++)
      {
        matrixPWM[j][i + 23*row] = (matrixPWM[j][i + 23*row]<<3) | ((matrixPWM[j][i + 1 + 23*row]&0xE0)>>5);
      }
      matrixPWM[j][11 + 23*row] = matrixPWM[j][11 + 23*row] << 3;
      matrixPWM[j][11 + 23*row] = (matrixPWM[j][11 + 23*row] & 0xF8)|temp;
    }
  }
  else
  {
    for(u8 j=0; j<2; j++)
    {
      u8 temp = matrix_temp[11 + 23*j] & 0x07;
      for(u8 i=0; i<11; i++)
      {
        matrix_temp[i + 23*j] = (matrix_temp[i + 23*j]<<3) | ((matrix_temp[i + 1 + 23*j]&0xE0)>>5);
      }
      matrix_temp[11 + 23*j] = matrix_temp[11 + 23*j] << 3;
      matrix_temp[11 + 23*j] = (matrix_temp[11 + 23*j] & 0xF8)|temp;
    }
  }
}

void SetHalfRow(s8 row, u8 data[], u8 blue, u8 red, u8 green)
{
  for(u8 j=0; j<4; j++)
    for(u8 i=0; i<8; i++)
    {
      if(data[j] & (0x80>>i))
        SetPixel(row, 8*j+i, blue, red, green);
      else
        SetPixel(row, 8*j+i, 0, 0, 0);
    }
}

void SetFullRow(s8 row, u8 data[], u8 blue, u8 red, u8 green)
{
  for(u8 j=0; j<7; j++)
    for(u8 i=0; i<8; i++)
    {
      if(data[j] & (0x80>>i))
        SetPixel(row, 8*j+i, blue, red, green);
      else
        SetPixel(row, 8*j+i, 0, 0, 0);
    }
  for(u8 i=0; i<4; i++)
  {
    if(data[7] & (0x80>>i))
      SetPixel(row, 8*7+i, blue, red, green);
    else
      SetPixel(row, 8*7+i, 0, 0, 0);
  }
}

void RotateReverseMatrix(s8 row)
{
  if(row!=16 && row!=-1)
    for(u8 j=0; j<2; j++)
    {
      u8 temp = (matrixPWM[j][0 + 23* row] & 0xE0) >>1;
      for(u8 i=0; i<22; i++)
        matrixPWM[j][i + 23*row] = (matrixPWM[j][i + 23*row]<<3) | ((matrixPWM[j][i + 1 + 23*row] & 0xE0) >> 5);
      matrixPWM[j][22 + 23*row] = (matrixPWM[j][22 + 23*row]<<3) | temp; 
    }
  else if(row == -1)
    for(u8 j=0; j<2; j++)
    {
      u8 temp = (matrix_temp[0 + 23* j] & 0xE0) >>1;
      for(u8 i=0; i<22; i++)
        matrix_temp[i + 23*j] = (matrix_temp[i + 23*j]<<3) | ((matrix_temp[i + 1 + 23*j] & 0xE0) >> 5);
      matrix_temp[22 + 23*j] = (matrix_temp[22 + 23*j]<<3) | temp; 
    }
  else
    for(u8 k=0; k<2; k++)
      for(u8 j=0; j<16; j++)
      {
        u8 temp = (matrixPWM[k][0 + 23* j] & 0xE0) >>1;
        for(u8 i=0; i<22; i++)
          matrixPWM[k][i + 23*j] = (matrixPWM[k][i + 23*j]<<3) | ((matrixPWM[k][i + 1 + 23*j] & 0xE0) >> 5);
        matrixPWM[k][22 + 23*j] = (matrixPWM[k][22 + 23*j]<<3) | temp; 
      }
}

void RotateMatrix(s8 row)
{
  if(row!=16 && row!=-1)
  {
    for(u8 j=0; j<2; j++)
    {
      u8 temp = (matrixPWM[j][22 + 23*row] & 0x70) <<1;
      for(u8 i=0; i<22; i++)
        matrixPWM[j][22-i +23*row] = (matrixPWM[j][22-i+23*row] >>3) | ((matrixPWM[j][21-i+23*row] & 0x07)<<5);
      matrixPWM[j][23*row] = (matrixPWM[j][23*row]>>3) | temp;
    }
  }
  else if(row==-1)
  {
    for(u8 j=0; j<2; j++)
    {
      u8 temp = (matrix_temp[22 + 23*j] & 0x70) <<1;
      for(u8 i=0; i<22; i++)
        matrix_temp[22-i + 23*j] = (matrix_temp[22-i+23*j] >>3) | ((matrix_temp[21-i+23*j] & 0x07)<<5);
      matrix_temp[23*j] = (matrix_temp[23*j]>>3) | temp;
    }
  }
  else
  {
    for(u8 k=0; k<2; k++)
    {
      for(u8 j=0; j<16; j++)
      {
        u8 temp = (matrixPWM[k][22 + 23*j] & 0x70) <<1;
        for(u8 i=0; i<22; i++)
          matrixPWM[k][22-i +23*j] = (matrixPWM[k][22-i+23*j] >>3) | ((matrixPWM[k][21-i+23*j] & 0x07)<<5);
        matrixPWM[k][23*j] = (matrixPWM[k][23*j]>>3) | temp;
      }
    }
  }
}

void TransferColor(u8 startColor, u8 endColor, u8 step)
{
  u8 c[3];
  for(u8 i=0; i<3; i++)
  {
    if(((startColor >> i) & 0x01) == 1 && ((endColor >> i) & 0x01) == 1)
      c[i] = step < 3 ? step + 1 : 3;
    if(((startColor >> i) & 0x01) == 0 && ((endColor >> i) & 0x01) == 1)
      c[i] = step < 3 ? 0 : step - 2;
    if(((startColor >> i) & 0x01) == 0 && ((endColor >> i) & 0x01) == 0)
      c[i] = 0;
  }
  bluePWM = c[2], redPWM = c[1], greenPWM = c[0];
}

void Spectrum2RGB(u8 color)
{
  if(color<4)
  {
    redPWM = 3;    
    greenPWM = 0;        
    bluePWM = 3 - color; 
  }
  else if(color<8)
  {
    redPWM = 3;    
    greenPWM = color - 4;        
    bluePWM = 0; 
  }
  else if(color<12)
  {
    redPWM = 3 - (color-8);    
    greenPWM = 3;        
    bluePWM = 0; 
  }
  else if(color<16)
  {
    redPWM = 0;    
    greenPWM = 3;        
    bluePWM = color - 12; 
  }
  else if(color<20)
  {
    redPWM = 0;    
    greenPWM = 3 - (color - 16);        
    bluePWM = 3; 
  }
  else if(color<24)
  {
    redPWM = color - 20;    
    greenPWM = 0;        
    bluePWM = 3; 
  }
  else if(color<28)
  {
    redPWM = 3 - (color - 24);    
    greenPWM = color - 24;        
    bluePWM = 3 - (color - 24); 
  }
  else if(color<32)
  {
    redPWM = 0;    
    greenPWM = 3 - (color - 28);        
    bluePWM = color - 28;
  }
  else
  {
    redPWM = color - 32;    
    greenPWM = 0;        
    bluePWM = 3 - (color - 32);
  }
}

void TurnOnHalfRow(s8 row, u8 data[], u8 blue, u8 red, u8 green)
{
  for(u8 i=0; i<4; i++)
    for(u8 j=0; j<8; j++)
      if(data[i]&(0x80>>j))
        SetPixel(row, 8*i + j, blue, red, green);
}

void SetChuVan(u8 x, u8 y, u8 graph, u8 step, u8 color)
{
  u8 data[] = {0x05, 0x07, 0x08, 0x0A, 0x0C,0x0D,0x0F,0x10,
    0xE8,0x28,0xF8,0xA0,0xB8,        //5
    0xF2,0x12,0x12,0xFE,0x90,0x90,0x9E,           //7
    0xFB,0xFB,0x1B,0xFF,0xFF,0xD8,0xDF,0xDF,      //8
    0xFC,0xC0,0xFC,0xC0,0x0C,0xC0,0x0C,0xC0,0xFF,0xC0,0xFF,0xC0,0xCC,0x00,0xCC,0x00,
    0xCF,0xC0,0xCF,0xC0,                          //10
    0xFE,0x30,0xFE,0x30,0x06,0x30,0x06,0x30,0x06,0x30,0xFF,0xF0,0xFF,0xF0,0xC6,0x00,
    0xC6,0x00,0xC6,0x00,0xC7,0xF0,0xC7,0xF0,      //12
    0xFF,0x38,0xFF,0x38,0xFF,0x38,0x07,0x38,0x07,0x38,0xFF,0xF8,0xFF,0xF8,0xFF,0xF8,
    0xE7,0x00,0xE7,0x00,0xE7,0xF8,0xE7,0xF8,0xE7,0xF8,    //13
    0xFF,0x8E,0xFF,0x8E,0xFF,0x8E,0x03,0x8E,0x03,0x8E,0x03,0x8E,0xFF,0xFE,0xFF,0xFE,
    0xFF,0xFE,0xE3,0x80,0xE3,0x80,0xE3,0x80,0xE3,0xFE,0xE3,0xFE,0xE3,0xFE,        //15
    0xFF,0xCF,0xFF,0xCF,0xFF,0xCF,0xFF,0xCF,0x03,0xCF,0x03,0xCF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xF3,0xC0,0xF3,0xC0,0xF3,0xFF,0xF3,0xFF,0xF3,0xFF,0xF3,0xFF,      //16
  };
  //u8 graph = 0;
  u8 startGraph = 8;
  for(u8 i=0; i<graph; i++)
    startGraph = startGraph + ((data[i]-1)/8+1)*data[i];
  for(u8 j=(data[graph]-1)/2-step; j<=data[graph]/2 + step; j++)
  {
    if(data[((data[graph]-1)/8+1)*((data[graph]-1)/2 - step) + startGraph + j/8]&(0x80>>(j%8)))
      SetPixel(data[graph]/2 + step + x, (j + y)%60, (color&0x30)>>4,(color&0x0C)>>2,color&0x03);
    if(data[((data[graph]-1)/8+1)*(data[graph]/2 + step) + startGraph+j/8]&(0x80>>(j%8)))
      SetPixel((data[graph]-1)/2 - step + x, (j + y)%60, (color&0x30)>>4,(color&0x0C)>>2,color&0x03);
    if(data[((data[graph]-1)/8+1)*(data[graph]-1 - j) + ((data[graph]-1)/2-step)/8 + startGraph]&(0x80>>(((data[graph]-1)/2-step)%8)))
      SetPixel(j + x, ((data[graph]-1)/2 - step + y)%60, (color&0x30)>>4,(color&0x0C)>>2,color&0x03);
    if(data[((data[graph]-1)/8+1)*j + (data[graph]/2 + step)/8 + startGraph]&(0x80>>((data[graph]/2+step)%8)))
      SetPixel(data[graph]-1-j + x, (data[graph]/2 + step + y)%60, (color&0x30)>>4,(color&0x0C)>>2,color&0x03);
  }
}

void HieuUng37(void)
{

}

void HieuUng36(void)
{
  u8 data[] = {0x05, 0x07, 0x08, 0x0A, 0x0C,0x0D,
  0x0A, 0x0A, 0x0C, 0x0C, 0x0F, 0x0F};
  for(u8 m=0; m<6; m++)
  {
    u8 color = rand();
    for(u8 i=0; i<(data[m]+1)/2; i++)
    {
      for(u8 j=0; j<60/data[6+m]; j++)
        SetChuVan(16 - data[m],61 - (data[m]+1)/2 + j*data[6+m], m, i, color);
      Delay(100);
    }
    if(m==0||m==1)
      for(u8 i=0; i<(data[m]+1)/2; i++)
      {
        for(u8 j=0; j<60/data[6+m]; j++)
          SetChuVan(8 - data[m],66 - (data[m]+1)/2 + j*data[6+m], m, i, color>>2);
        Delay(100);
      }
    for(u8 i=0; i<60; i++)
    {
      RotateMatrix(16);
      Delay(50);
    }
    for(u8 i=0; i<60; i++)
    {
      RotateReverseMatrix(16);
      Delay(50);
    }
    for(u8 i=0; i<(data[m]+1)/2; i++)
    {
      for(u8 j=0; j<60/data[6+m]; j++)
        SetChuVan(16 - data[m],61 - (data[m]+1)/2 + j*data[6+m], m, i, 0x00);
      Delay(100);
    }
    if(m==0||m==1)
      for(u8 i=0; i<(data[m]+1)/2; i++)
      {
        for(u8 j=0; j<60/data[6+m]; j++)
          SetChuVan(8 - data[m],66 - (data[m]+1)/2 + j*data[6+m], m, i, 0x00);
        Delay(100);
      }
  }
}

void HieuUng35(void)
{
  for(u8 k=0; k<2; k++)
  {
    for(u8 j=0; j<4-k; j++)
    {
      u8 color1 = rand(), color2 = rand();
      for(u8 i=0; i<3; i++)
      {
        SetChuVan(8*k,58 + 10*j - 25*k,0,i,color1);
        SetChuVan(8*k,58 - 10*j - 35*k,0,i,color2);
        Delay(50);
      }
    }
  }
  for(u8 i=0; i<60; i++)
  {
    RotateMatrix(16);
    Delay(30);
  }
  for(u8 i=0; i<60; i++)
  {
    RotateReverseMatrix(16);
    Delay(30);
  }
  for(u8 k=0; k<2; k++)
  for(u8 i=0; i<3; i++)
  {
    for(u8 j=0; j<6; j++)
      SetChuVan(8*k,58+10*j+5*k,0,2-i,0);
    Delay(50);
  }
  for(u8 k=0; k<2; k++)
  {
    for(u8 j=0; j<4-k; j++)
    {
      u8 color1 = rand(), color2 = rand();
      for(u8 i=0; i<4-k; i++)
      {
        SetChuVan(9*k,57 + 10*j - 24*k,k==0?1:0,i,color1);
        SetChuVan(9*k,57 - 10*j - 34*k,k==0?1:0,i,color2);
        Delay(100);
      }
    }
  }
  for(u8 i=0; i<160; i++)
  {
    RollOut();
    Delay(50);
  }
  for(u8 i=0; i<160; i++)
  {
    RollIn();
    Delay(50);
  }
  for(u8 k=0; k<2; k++)
    for(u8 i=0; i<4-k; i++)
    {
      for(u8 j=0; j<6; j++)
        SetChuVan(9*k,57+10*j+6*k,1-k,3-i-k,0);
      Delay(100);
    }
}

void HieuUng34(u8 mode)
{
  u8 data[] = 
    {
      0x04,0x00,0x0A,0x00,0x11,0x00,0x20,0x80,0x40,0x40,0x80,0x20,0x80,0x20,0x60,0xC0,
      0x1B,0x00,0x04,0x00,
      0x04,0x00,0x0E,0x00,0x1F,0x00,0x3F,0x80,0x7F,0xC0,0xFF,0xE0,0xFF,0xE0,0x7F,0xC0,
      0x1F,0x00,0x04,0x00,
    };
  u8 c[15];
  for(u8 i=0; i<15; i++)
    c[i] = rand()%4;
  for(u8 i=0; i<5; i++)
  {
    if(c[3*i]==0&&c[3*i+1]==0&&c[3*i+2]==0)
      for(u8 j=0; j<3; j++)
        c[3*i+j] = rand()%4;
  }
  for(u8 l=0; l<2; l++)
  {
    for(u8 i=0; i<10; i++)
    {
      for(u8 j=0; j<46; j++)
        matrix_temp[j] = 0;
      for(u8 k=0; k<5; k++)
        for(u8 j=0; j<12; j++)
        {
          if(data[j/8+2*i+18*mode]&(0x80>>(j%8)))
          {
            if(l==0)
              SetPixel(-1,(55+j+12*k)%60,c[3*k],c[3*k+1],c[3*k+2]);
            else
              SetPixel(-1,(j+12*k+1)%60,c[3*k],c[3*k+1],c[3*k+2]);
          }
            
        }
      SweepOut(matrix_temp);
      Delay(50);
    }
  }
}

void HieuUng33(void)
{
  u8 data[] = 
    {
      0x80,0x08,0x00,0x80,0xC0,0x1C,0x01,0xC0,0xE0,0x3E,0x03,0xE0,0xF0,0x7F,0x07,0xF0,
      0xF8,0xFF,0x8F,0xF8,0xFD,0xFF,0xDF,0xFC,0xFF,0xFF,0xFF,0xFE,0xF8,0xFF,0x8F,0xF8,
      0xE0,0x3E,0x03,0xE0,0x80,0x08,0x00,0x80,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x08,0x00,0x80,0xC0,0x1C,0x01,0xC0,
      0xE0,0x3E,0x03,0xE0,0xF0,0x7F,0x07,0xF0,0xE0,0x3E,0x03,0xE0,0x80,0x08,0x00,0x80,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };
  u8 temp[4];
  u8 c1 = rand()%4, c2 = rand()%4, c3 = rand()%4;
  u8 c4 = rand()%4, c5 = rand()%4, c6 = rand()%4;
  for(u8 i=0; i<10; i++)
  {
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i];
    TurnOnHalfRow(-1, temp,c1,c2,c3);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+40+4*i];
    TurnOnHalfRow(-1, temp,c4,c5,c6);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng32(void)
{
  u8 data[] = 
    {
      0x80,0x08,0x00,0x80,0xC0,0x1C,0x01,0xC0,0xE0,0x3E,0x03,0xE0,0xF0,0x7F,0x07,0xF0,
      0xF8,0xFF,0x8F,0xF8,0xFD,0xFF,0xDF,0xFC,0xFF,0xFF,0xFF,0xFE,0xF8,0xFF,0x8F,0xF8,
      0xE0,0x3E,0x03,0xE0,0x80,0x08,0x00,0x80,
    };
  u8 temp[4];
  bluePWM = rand()%4, redPWM = rand()%4, greenPWM = rand()%4;
  for(u8 i=0; i<10; i++)
  {
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i];
    SetHalfRow(-1, temp,bluePWM,redPWM,greenPWM);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
}
void HieuUng31(void)
{
  u8 data[] = {
    0x80,0x08,0x00,0x80,0xC0,0x1C,0x01,0xC0,0xE0,0x3E,0x03,0xE0,0xF0,0x7F,0x07,0xF0,
    0xF8,0xFF,0x8F,0xF8,0xFD,0xFF,0xDF,0xFC,0x02,0x00,0x20,0x02,0x07,0x00,0x70,0x06,
    0x0F,0x80,0xF8,0x0E,0x1F,0xC1,0xFC,0x1E,0x3F,0xE3,0xFE,0x3E,0x7F,0xF7,0xFF,0x7E,
  };
  u8 temp[4];
  for(u8 k=0; k<2; k++)
  {
    bluePWM = rand()%4, redPWM = rand()%4, greenPWM = rand()%4;
    for(u8 i=0; i<6; i++)
    {
      for(u8 j=0; j<4; j++)
        temp[j] = data[j+4*i+24*k];
      SetHalfRow(-1, temp,bluePWM,redPWM,greenPWM);
      for(u8 j=0; j<30; j++)
        SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
      SweepOut(matrix_temp);
      Delay(50);
    }
  }
}

void HieuUng30(void)
{
  u8 data[] = {
    0x80,0x10,0x00,0x80,0xA0,0x54,0x02,0xA0,0xA9,0x55,0x0A,0xA8,0x2F,0x45,0x6A,0x2A,
    0x0F,0x01,0x68,0x0A,0x06,0x00,0x60,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  };
  u8 temp[4];
  static u8 c1,c2, c3, c4, c5, c6 = 0;
  for(u8 k=0; k<2; k++)
  for(u8 i=0; i<8; i++)
  {
    if(i==0)
      c1 = rand()%4, c2 = rand()%4, c3 = rand()%4;
    if(i==4)
      c4 = rand()%4, c5 = rand()%4, c6 = rand()%4;
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i];
    TurnOnHalfRow(-1, temp,c1,c2,c3);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*(i>3?i-4:i+4)];
    TurnOnHalfRow(-1, temp,c4,c5,c6);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 i=0; i<4; i++)
  {
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*(i+4)];
    TurnOnHalfRow(-1, temp,c4,c5,c6);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 i=0; i<8; i++)
  {
    SweepOut(matrix_temp);
    Delay(50);
  }
  c1 = c2 = c3 = c4 = c5 = c6 = 0;
}

void HieuUng29(void)
{
  u8 data[] = {
    0x80,0x10,0x00,0x80,0xA0,0x54,0x02,0xA0,0xA9,0x55,0x0A,0xA8,0x2F,0x45,0x6A,0x2A,
    0x0F,0x01,0x68,0x0A,0x06,0x00,0x60,0x02,
  };
  u8 temp[4];
  bluePWM = rand()%4, redPWM = rand()%4, greenPWM = rand()%4;
  for(u8 i=0; i<6; i++)
  {
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i];
    TurnOnHalfRow(-1, temp,bluePWM,redPWM,greenPWM);
    for(u8 j=0; j<30; j++)
    SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng28(void)
{
  u8 data[] = {
    0x80,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0xE1,0x00,0x00,0x00,0x71,0x80,0x00,0x00,
    0x39,0xC2,0x00,0x00,0x1D,0xE3,0x00,0x00,0x0F,0x73,0x84,0x00,0x07,0x3B,0xC6,0x00,
    0x03,0x1E,0xE7,0x00,0x00,0x0E,0x77,0x80,0x00,0x06,0x3D,0xC0,0x00,0x00,0x1C,0xE0,
    0x00,0x00,0x0C,0x70,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0x0E,
    0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x02,
  };
  u8 temp[4];
  static u8 c1,c2, c3, c4, c5, c6, c7, c8, c9 = 0;
  for(u8 i=0; i<18; i++)
  {
    if(i==0)
      c1 = rand()%4, c2 = rand()%4, c3 = rand()%4;
    if(i==6)
      c4 = rand()%4, c5 = rand()%4, c6 = rand()%4;
    if(i==12)
      c7 = rand()%4, c8 = rand()%4, c9 = rand()%4;
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*(i%18)];
    TurnOnHalfRow(-1, temp,c1,c2,c3);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*((i>5?i-6:i+12)%18)];
    TurnOnHalfRow(-1, temp,c4,c5,c6);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*((i>11?i-12:i+6)%18)];
    TurnOnHalfRow(-1, temp,c7,c8,c9);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng27(void)
{
  u8 data[] = {
    0x80,0x00,0x00,0x00,0xC1,0x00,0x00,0x00,0x61,0x80,0x00,0x00,0x31,0xC1,0x00,0x00,
    0x19,0x61,0x80,0x00,0x0D,0x31,0xC0,0x00,0x07,0x19,0x60,0x00,0x03,0x0D,0x31,0x00,
    0x00,0x07,0x19,0x80,0x00,0x03,0x0D,0xC0,0x00,0x00,0x07,0x60,0x00,0x00,0x03,0x30,
    0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x02,
  };
  u8 temp[4];
  static u8 c1,c2, c3, c4, c5, c6, c7, c8, c9 = 0;
  for(u8 i=0; i<16; i++)
  {
    if(i==0||i==16||i==32)
      c1 = rand()%4, c2 = rand()%4, c3 = rand()%4;
    if(i==6||i==22||i==38)
      c4 = rand()%4, c5 = rand()%4, c6 = rand()%4;
    if(i==12||i==28||i==44)
      c7 = rand()%4, c8 = rand()%4, c9 = rand()%4;
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*(i%16)];
    TurnOnHalfRow(-1, temp,c1,c2,c3);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*((i>5?i-6:i+10)%16)];
    TurnOnHalfRow(-1, temp,c4,c5,c6);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*((i>11?i-12:i+4)%16)];
    TurnOnHalfRow(-1, temp,c7,c8,c9);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng26(void)
{
  u8 data[] = {
    0x80,0x00,0x00,0x00,0xA0,0x00,0x00,0x00,0xA8,0x00,0x00,0x00,0x2A,0x00,0x00,0x00,
    0x0A,0x88,0x00,0x00,0x02,0xAA,0x00,0x00,0x00,0xAA,0x80,0x00,0x00,0x2A,0xA2,0x00,
    0x00,0x08,0xAA,0x00,0x00,0x00,0x2A,0x80,0x00,0x00,0x0A,0xA0,0x00,0x00,0x02,0xA8,
    0x00,0x00,0x00,0x2A,0x00,0x00,0x00,0x0A,0x00,0x00,0x00,0x02,
  };
  u8 temp[4];
  static u8 c1,c2, c3, c4, c5, c6, c7, c8, c9 = 0;
  c1 = rand()%4, c2 = rand()%4, c3 = rand()%4;
  for(u8 i=0; i<5; i++)
  {
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i];
    TurnOnHalfRow(-1, temp,c1,c2,c3);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i + 40];
    TurnOnHalfRow(-1, temp,c4,c5,c6);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i+20];
    TurnOnHalfRow(-1, temp,c7,c8,c9);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
  c4 = rand()%4, c5 = rand()%4, c6 = rand()%4;
  for(u8 i=0; i<5; i++)
  {
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i+20];
    TurnOnHalfRow(-1, temp,c1,c2,c3);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i];
    TurnOnHalfRow(-1, temp,c4,c5,c6);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i+40];
    TurnOnHalfRow(-1, temp,c7,c8,c9);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
  c7 = rand()%4, c8 = rand()%4, c9 = rand()%4;
  for(u8 i=0; i<5; i++)
  {
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i+40];
    TurnOnHalfRow(-1, temp,c1,c2,c3);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i + 20];
    TurnOnHalfRow(-1, temp,c4,c5,c6);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i];
    TurnOnHalfRow(-1, temp,c7,c8,c9);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng25(void)    //Hoa sen - Zoom Out - Change Color RGB
{
  u8 data[] = {
    0x80,0x00,0x00,0x00,0xC1,0x00,0x00,0x00,0xE1,0x82,0x00,0x00,0x71,0xC3,0x04,0x00,
    0x39,0xE3,0x86,0x00,0x1D,0x73,0xC7,0x00,0x0F,0x3A,0xE7,0x80,0x07,0x1E,0x77,0xC0,
    0x03,0x0E,0x3D,0xE0,0x01,0x06,0x1C,0xF0,0x00,0x02,0x0C,0x78,0x00,0x00,0x04,0x3C,
    0x00,0x00,0x00,0x1E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x02,
  };
  u8 temp[4];
  static u8 c1,c2, c3, c4, c5, c6 = 0;
  c1 = rand()%4, c2 = rand()%4, c3 = rand()%4;
  for(u8 i=0; i<8; i++)
  {
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i];
    TurnOnHalfRow(-1, temp,c1,c2,c3);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i+32];
    TurnOnHalfRow(-1, temp,c4,c5,c6);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
  c4 = rand()%4, c5 = rand()%4, c6 = rand()%4;
  for(u8 i=0; i<8; i++)
  {
    for(u8 j=0; j<46; j++)
      matrix_temp[j] = 0;
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i+32];
    TurnOnHalfRow(-1, temp,c1,c2,c3);
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i];
    TurnOnHalfRow(-1, temp,c4,c5,c6);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
}
void HieuUng24(void)    //Chu van - Spectrum Out - Rotate - Spectrum In - Rotate Reverse
{
  u8 data[] = {0xE3, 0xFF, 0xC7, 0xFF, 0x8F, 0xFF, 0x1F, 0xF0,
  0xE0, 0x07, 0xC0, 0x0F, 0x80, 0x1F, 0x00, 0x30};
  u8 temp[8];
  for(u8 k=0; k<16; k++)
  {
    for(u8 i=0; i<8; i++)
      if(k<5)
        temp[i] = data[i];
      else
        temp[i] = data[i + 8];
    Spectrum2RGB(k);
    SetFullRow(-1, temp, bluePWM, redPWM, greenPWM);
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 j=0; j<180; j++)
  {
    for(u8 k=0; k<16; k++)
    {
      for(u8 i=0; i<8; i++)
      if(k<5)
        temp[i] = data[i];
      else 
        temp[i] = data[i + 8];
      Spectrum2RGB((k+j)%36);
      SetFullRow(15-k, temp, bluePWM, redPWM, greenPWM);
    }
    Delay(50);
  }
  for(u8 i=0; i<240; i++)
  {
    RotateMatrix(16);
    Delay(50);
  }  
  for(u8 j=0; j<180; j++)
  {
    for(u8 k=0; k<16; k++)
    {
      for(u8 i=0; i<8; i++)
      if(k<11)
        temp[i] = data[i + 8];
      else
        temp[i] = data[i];
      Spectrum2RGB((k+j)%36);
      SetFullRow(k, temp, bluePWM, redPWM, greenPWM);
    }
    Delay(50);
  }
  for(u8 i=0; i<240; i++)
  {
    RotateReverseMatrix(16);
    Delay(50);
  }  
}
void HieuUng23(u8 mode)    //Hoasen - SpectrumIn - SpectrumOut
{
  u8 data[] = {
    0x80,0x20,0x41,0x00,0x00,0x00,0x00,0x00,0x80,0x20,0x41,0x00,0xC0,0x20,0x41,0x00,
    0xE0,0x30,0x61,0x80,0xF0,0x30,0x61,0x80,0xF8,0x38,0x71,0xC0,0xFC,0x38,0x71,0xC0,
    0xFE,0x3C,0x79,0xE0,0xFF,0x3C,0x79,0xE0,0xFF,0xBE,0x7D,0xF0,0xFF,0xFE,0x7D,0xF0,
    0xFF,0xFF,0x7F,0xFA,0xFF,0xFF,0x7F,0xFA,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFE,
    0x81,0x02,0x08,0x02,0x80,0x00,0x00,0x00,0x80,0x02,0xAA,0xAA,0x81,0x00,0x00,0x00,
    0xC1,0x01,0x55,0x54,0xC1,0x82,0x00,0x00,0xE1,0x82,0x08,0xAA,0xE1,0xC3,0x0C,0x00,
    0xF1,0xC3,0x0E,0x54,0xF1,0xE3,0x8F,0x00,0xF9,0xE3,0x8F,0x80,0xF9,0xF3,0xCF,0xC2,
    0xFD,0xF3,0xCF,0xE2,0xFD,0xFB,0xEF,0xF2,0xFF,0xFB,0xEF,0xFA,0xFF,0xFF,0xFF,0xFE,
  };
  u8 temp[4];
  for(u8 i=0; i<16; i++)
  {
    for(u8 j=0; j<4; j++)
      temp[j] = data[j+4*i + mode*64];
    Spectrum2RGB(i);
    SetHalfRow(-1, temp, bluePWM,redPWM,greenPWM);
    for(u8 j=0; j<30; j++)
      SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 j=0; j<180; j++)
  {
    for(u8 k=0; k<15; k++)
    {
      for(u8 i=0; i<4; i++)
        temp[i] = data[i + 4*(k+1) + mode*64];
      Spectrum2RGB((k+j)%36);
      SetHalfRow(14-k, temp, bluePWM, redPWM, greenPWM);
      for(u8 i=0; i<30; i++)
        SetPixel(14-k, (60-i)%60, ReadPixel(14-k,i, BLUE), ReadPixel(14-k,i, RED), ReadPixel(14-k,i, GREEN));
    }
    Delay(50);
  }
  for(u8 j=0; j<180; j++)
  {
    for(u8 k=0; k<15; k++)
    {
      for(u8 i=0; i<4; i++)
        temp[i] = data[i + 4*(15-k) + mode*64];
      Spectrum2RGB((k+j)%36);
      SetHalfRow(k, temp, bluePWM, redPWM, greenPWM);
      for(u8 i=0; i<30; i++)
        SetPixel(k, (60-i)%60, ReadPixel(k,i, BLUE), ReadPixel(k,i, RED), ReadPixel(k,i, GREEN));
    }
    Delay(50);
  }
}

void HieuUng22(void)    //SpectrumIn - SpectrumOut
{
  for(u8 i=0; i<36; i++)
  {
    Spectrum2RGB(i);
    for(u8 j=0; j<60; j++)
      SetPixel(-1,j,bluePWM, redPWM, greenPWM);
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 i=0; i<36; i++)
  {
    Spectrum2RGB(i);
    for(u8 j=0; j<60; j++)
      SetPixel(-1,j,bluePWM, redPWM, greenPWM);
    SweepIn(matrix_temp);
    Delay(50);
  }
}
void HieuUng21(void)
{
  for(u8 j=1; j<10; j++)
  {
    for(u8 i=0; i<60; i++)
    { 
      SetPixel(-1,i,j<3?j:3, j<6?0:j-6, j<3?0:j<6?j-3:3);
    }
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 j=9; j>0; j--)
  {
    for(u8 i=0; i<60; i++)
    { 
      SetPixel(-1,i,j<3?j:3, j<6?0:j-6, j<3?0:j<6?j-3:3);
    }
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 j=1; j<10; j++)
  {
    for(u8 i=0; i<60; i++)
    { 
      SetPixel(-1,i,j<6?0:j-6, j<3?j:3, j<3?0:j<6?j-3:3);
    }
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 j=9; j>0; j--)
  {
    for(u8 i=0; i<60; i++)
    { 
      SetPixel(-1,i,j<6?0:j-6, j<3?j:3, j<3?0:j<6?j-3:3);
    }
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 j=1; j<10; j++)
  {
    for(u8 i=0; i<60; i++)
    { 
      SetPixel(-1,i,j<3?j:3, j<3?0:j<6?j-3:3, j<6?0:j-6 );
    }
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 j=9; j>0; j--)
  {
    for(u8 i=0; i<60; i++)
    { 
      SetPixel(-1,i,j<3?j:3, j<3?0:j<6?j-3:3, j<6?0:j-6);
    }
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 j=1; j<10; j++)
  {
    for(u8 i=0; i<60; i++)
    { 
      SetPixel(-1,i,j<3?0:j<6?j-3:3, j<6?0:j-6, j<3?j:3 );
    }
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 j=9; j>0; j--)
  {
    for(u8 i=0; i<60; i++)
    { 
      SetPixel(-1,i,j<3?0:j<6?j-3:3, j<6?0:j-6, j<3?j:3);
    }
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng20(void)    //Chu van - Zoom In - Change Color RGB
{
  u8 data[] = {0xE3, 0xFF, 0xC7, 0xFF, 0x8F, 0xFF, 0x1F, 0xF0,
  0xE0, 0x07, 0xC0, 0x0F, 0x80, 0x1F, 0x00, 0x30};
  u8 temp[8];
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 i=0; i<8; i++)
    temp[i] = 0xFF;
  SetFullRow(-1,temp,bluePWM,redPWM,greenPWM);
  SweepIn(matrix_temp);
  Delay(25);
  for(u8 i=0; i<8; i++)
    temp[i] = data[i + 8];
  SetFullRow(-1,temp,bluePWM,redPWM,greenPWM);
  for(u8 i=0; i<8; i++)
  {
    SweepIn(matrix_temp);
    Delay(25);
  }
  for(u8 i=0; i<8; i++)
    temp[i] = data[i];
  SetFullRow(-1,temp,bluePWM,redPWM,greenPWM);
  for(u8 i=0; i<5; i++)
  {
    SweepIn(matrix_temp);
    Delay(25);
  }
  
  for(u8 i=0; i<8; i++)
    temp[i] = 0x00;
  SetFullRow(-1,temp,bluePWM,redPWM,greenPWM);
  for(u8 i=0; i<16; i++)
  {
    SweepIn(matrix_temp);
    Delay(25);
  }
}
void HieuUng19(void)    //Chu van - Zoom Out - Change Color RGB
{
  u8 data[] = {0xE3, 0xFF, 0xC7, 0xFF, 0x8F, 0xFF, 0x1F, 0xF0,
  0xE0, 0x07, 0xC0, 0x0F, 0x80, 0x1F, 0x00, 0x30};
  u8 temp[8];
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 i=0; i<8; i++)
    temp[i] = data[i];
  SetFullRow(-1,temp,bluePWM,redPWM,greenPWM);
  for(u8 i=0; i<5; i++)
  {
    SweepOut(matrix_temp);
    Delay(25);
  }
  for(u8 i=0; i<8; i++)
    temp[i] = data[i+8];
  SetFullRow(-1,temp,bluePWM,redPWM,greenPWM);
  for(u8 i=0; i<8; i++)
  {
    SweepOut(matrix_temp);
    Delay(25);
  }
  for(u8 i=0; i<8; i++)
    temp[i] = 0xFF;
  SetFullRow(-1,temp,bluePWM,redPWM,greenPWM);
  SweepOut(matrix_temp);
  Delay(25);
  for(u8 i=0; i<8; i++)
    temp[i] = 0x00;
  SetFullRow(-1,temp,bluePWM,redPWM,greenPWM);
  for(u8 i=0; i<16; i++)
  {
    SweepOut(matrix_temp);
    Delay(25);
  }
}

void HieuUng18(void)
{
  for(u8 k=0; k<6; k++)
  {
    for(u8 j=0; j<3; j++)
    {
      for(u8 i=0; i<9; i++)
      {
        RotateHalf(-1);
        if((j==0&&k==0) ||(j==1&&k==1) || (j==2&&k==2))
        {
          if(i<3)     SetPixel(-1,0,0,0,i);
          else if(i>2&&i<6) SetPixel(-1,0,i-3,0,3);
          else if(i>5) SetPixel(-1,0,3,i-6,3);
         
        }
        else if((j==1&&k==0) || (j==2&&k==1)||(j==0&&k==2))
        {
          if(i<3)     SetPixel(-1,0,i,0,0);
          else if(i>2&&i<6) SetPixel(-1,0,3,0,i-3);
          else if(i>5) SetPixel(-1,0,3,i-6,3);
        }
        else if((j==2&&k==0) || (j==0&&k==1)||(j==1&&k==2))
        {
          if(i<3)     SetPixel(-1,0,0,i,0);
          else if(i>2&&i<6) SetPixel(-1,0,i-3,3,0);
          else if(i>5) SetPixel(-1,0,3,3,i-6);
        }
        else if((j==0&&k==3) || (j==1&&k==4) || (j==2&&k==5))
        {
          if(i<6)     SetPixel(-1,0,i/2,0,i/2);
          else if(i>5) SetPixel(-1,0,3,i-6,3);
        }
        else if((j==1&&k==3) || (j==2&&k==4) || (j==0&&k==5))
        {
          if(i<6)     SetPixel(-1,0,0,i/2,i/2);
          else if(i>5) SetPixel(-1,0,i-6,3,3);
        }
        else if((j==2&&k==3) || (j==0&&k==4) || (j==1&&k==5))
        {
          if(i<6)     SetPixel(-1,0,i/2,i/2,0);
          else if(i>5) SetPixel(-1,0,3,3,i-6);
        }
        for(u8 j=0; j<30; j++)
          SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
        SweepOut(matrix_temp);
        Delay(25);
      }
    }
    for(u8 i=0; i<16; i++)
    {
      RotateHalf(-1);
      for(u8 j=0; j<30; j++)
        SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
      SweepOut(matrix_temp);
      Delay(25);
    }
  }
}

void HieuUng17(void)
{
  bluePWM = rand() % 2, redPWM = rand() % 2, greenPWM = rand() % 2;
  if(bluePWM==redPWM==greenPWM==0)
    bluePWM=redPWM=greenPWM=1;
  for(u8 i=0; i<31; i++)
  {
    SetPixel(-1,i,bluePWM,redPWM,greenPWM);
    SetPixel(-1,(60 - i)%60,bluePWM,redPWM,greenPWM);
    SweepOut(matrix_temp);
    Delay(25);
  }
  for(u8 i=0; i<31; i++)
  {
    SetPixel(-1,30 - i,bluePWM==1?3:0,redPWM==1?3:0,greenPWM==1?3:0);
    SetPixel(-1,(30 + i)%60,bluePWM==1?3:0,redPWM==1?3:0,greenPWM==1?3:0);
    SweepOut(matrix_temp);
    Delay(25);
  }
}

void HieuUng16(void)
{
  for(u8 i=0; i<4; i++)
  {
    bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
    for(u8 j=0; j<3; j++)
      SetPixel(-1, 4*i+j, bluePWM,redPWM,greenPWM);
  }
  
  for(u8 k=0; k<240; k++)
  {
    bluePWM = rand() % 2, redPWM = rand() % 2, greenPWM = rand() % 2;
    if(k%8==0 && !(bluePWM==0 && redPWM==0 && greenPWM==0))
    for(u8 i=12; i<60; i++)
    {
      SetPixel(-1, (i + 2*k)%60, bluePWM,redPWM,greenPWM);
    }
    SweepOut(matrix_temp);
    RotateMatrix(-1);
    RotateMatrix(-1);
    Delay(25);
  }
}

void HieuUng15(void)
{
  for(u8 i=0; i<4; i++)
  {
    bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
    if(!(bluePWM==0&&redPWM==0&&greenPWM==0))
      for(u8 j=0; j<12; j++)
        SetPixel(-1, 15*i+j, bluePWM,redPWM,greenPWM);
  }
  for(u8 i=0; i<240; i++)
  {
    SweepOut(matrix_temp);
    RotateMatrix(-1);
    RotateMatrix(-1);
    Delay(DELAY/2);
  }
  for(u8 i=0; i<240; i++)
  {
    SweepOut(matrix_temp);
    RotateReverseMatrix(-1);
    RotateReverseMatrix(-1);
    Delay(DELAY/2);
  }
}

void HieuUng14(void)
{
  u8 data[] = {
  0x80, 0x03, 0x00, 0x06,
  0xC0, 0x07, 0x80, 0x0E,
  0xE0, 0x0F, 0xC0, 0x1E,
  0xF0, 0x1F, 0xE0, 0x3E,
  0xF8, 0x3F, 0xF0, 0x7E,
  0xFC, 0x7F, 0xF8, 0xFE,
  0xFE, 0xFF, 0xFD, 0xFE,
  0x7E, 0xFC, 0xFD, 0xF8,
  0x3E, 0xF8, 0x7D, 0xF0,
  0x1E, 0xF0, 0x3D, 0xE0,
  0x0E, 0xE0, 0x1D, 0xC0,
  0x0E, 0xE0, 0x1D, 0xC0,
  0x0E, 0xE0, 0x1D, 0xC0,
  0x0E, 0xE0, 0x1D, 0xC0,
  0x0E, 0xE0, 0x1D, 0xC0,
  0xFE, 0xFF, 0xFD, 0xFE
  };
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 i=0; i<16; i++)
  {
    u8 temp[4];
    for(u8 j=0; j<4; j++)
      temp[j] = data[4*i + j];
    SetHalfRow(-1,temp,bluePWM,redPWM,greenPWM);
    if(i==9 ||i==10)
    {
      SetPixel(-1,0,redPWM,greenPWM,bluePWM);
      SetPixel(-1,14,redPWM,greenPWM,bluePWM);
      SetPixel(-1,15,redPWM,greenPWM,bluePWM);
      SetPixel(-1,29,redPWM,greenPWM,bluePWM);
    }
    if(i==10||i==11||i==12||i==13)
    {
      SetPixel(-1,1,redPWM,greenPWM,bluePWM);
      SetPixel(-1,13,redPWM,greenPWM,bluePWM);
      SetPixel(-1,16,redPWM,greenPWM,bluePWM);
      SetPixel(-1,28,redPWM,greenPWM,bluePWM);
    }
    for(u8 j=0; j<30; j++)
      SetPixel(-1, 59-j, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
    SweepOut(matrix_temp);
    Delay(DELAY/2);
  }
}

void HieuUng13(void)
{
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 j=0; j<16; j++)
  {
    u8 c4 = rand() % 4, c5 = rand() % 4, c6 = rand() % 4;
    for(u8 i=0; i<60; i++)
    {
      if(i==0||i==15||i==30||i==45||i==7||i==22||i==37||i==52)
      {
        SetPixel(-1,i,bluePWM,redPWM,greenPWM);
      }
      else
      {
        if(j==0||j==6||j==7||j==8||j==15)
          SetPixel(-1,i,c4,c5,c6);
        else
          SetPixel(-1,i,0,0,0);
      }
        
    }
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng12(void)
{
  u8 data[] = {0xFF, 0xFF, 0xFF, 0xFE, 0x7B, 0xDE, 0xF7, 0xBC, 0x7B, 0xDE, 0xF7, 0xBC, 0x7B, 0xDE, 0xF7, 0xBC,       
  0x7B, 0xDE, 0xF7, 0xBC, 0x31, 0x8C, 0x63, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x21, 0x08, 0x42,       
  0xCE, 0x73, 0x9C, 0xE6, 0xCE, 0x73, 0x9C, 0xE6, 0xCE, 0x73, 0x9C, 0xE6, 0xCE, 0x73, 0x9C, 0xE6, 0xCE, 0x73, 0x9C, 0xE6,       
  0xCE, 0x73, 0x9C, 0xE6, 0xCE, 0x73, 0x9C, 0xE6, 0x7E, 0x7E, 0xFC, 0xFC, 0x7E, 0x7E, 0xFC, 0xFC, 0x7E, 0x7E, 0xFC, 0xFC, 
  0x7E, 0x7E, 0xFC, 0xFC, 0x7E, 0x7E, 0xFC, 0xFC, 0x3C, 0x3C, 0x78, 0x78, 0x18, 0x18, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x81, 0x81, 0x03, 0x02, 0xC3, 0xC3, 0x87, 0x86, 0xE7, 0xE7, 0xCF, 0xCE, 0xE7, 0xE7, 0xCF, 0xCE, 0xE7, 0xE7, 0xCF, 0xCE, 
  0xE7, 0xE7, 0xCF, 0xCE, 0xE7, 0xE7, 0xCF, 0xCE, 0xE7, 0xE7, 0xCF, 0xCE};
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 m=0; m<4; m++)
  {
    for(u8 k=0; k<5; k++)
    {
      for(u8 i=0; i<16; i++)
      {
        u8 temp[4];
        for(u8 j=0; j<4; j++)
          temp[j] = data[4*i + j + 64*(m/2)];
        if(i%8==0)
          bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
        SetHalfRow(-1,temp,bluePWM,redPWM,greenPWM);
        for(u8 j=0; j<30; j++)
          SetPixel(-1, (60-j)%60, ReadPixel(-1,j, BLUE), ReadPixel(-1,j, RED), ReadPixel(-1,j, GREEN));
        SweepOut(matrix_temp);
        Delay(DELAY/2);
      }
    }
    if(m%2==0)
      for(u8 i=0; i<240; i++)
      {
        RotateMatrix(16);
        Delay(DELAY/2);  
      }
    else
      for(u8 i=0; i<240; i++)
      {
        RotateReverseMatrix(16);
        Delay(DELAY/2);  
      }
  }
}

void HieuUng11(void)
{
  u8 data[] = {0x01, 0x03, 0x03, 0x02, 0x01, 0x03, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 j=0; j<16; j++)
  {
    for(u8 i=0; i<15; i++)
    {
      data[j]&0x01 ? SetPixel(-1,4*i,bluePWM,redPWM,greenPWM) : SetPixel(-1,4*i,0,0,0);
      data[j]&0x02 ? SetPixel(-1,4*i + 2,bluePWM,redPWM,greenPWM) : SetPixel(-1,4*i + 2,0,0,0);  
    }
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng10(u8 mode)
{
  u8 data_temp_2[2*23];
  u8 data_temp_3[2*23];
  for(u8 i=0; i<46; i++)
    matrix_temp[i] = 0x00;
  for(u8 j=0; j<2 + 2*mode; j++)
  {
    bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
    if(bluePWM==0&&redPWM==0&&greenPWM==0)
      j--;
    else
      for(u8 i=0; i<9 - 2*mode; i++)
        if(mode==0)
          SetPixel(-1,i + 30*j, bluePWM,redPWM,greenPWM);
        else if(mode==1)
          SetPixel(-1,i + 15*j, bluePWM,redPWM,greenPWM);
        else
          SetPixel(-1,i + 10*j, bluePWM,redPWM,greenPWM);
  }
  for(u8 i=0; i<4 - mode; i++)
    RotateReverseMatrix(-1);
  for(u8 i=0; i<46; i++)
    data_temp_2[i] = matrix_temp[i];
  SweepOut(data_temp_2);
  for(u8 k=0; k<240; k++)
  {
    RotateReverseMatrix(-1);
    for(u8 j=0; j<2; j++)
    {
      u8 temp = (data_temp_2[22 + 23*j] & 0x70) <<1;
      for(u8 i=0; i<22; i++)
        data_temp_2[22-i + 23*j] = (data_temp_2[22-i+23*j] >>3) | ((data_temp_2[21-i+23*j] & 0x07)<<5);
      data_temp_2[23*j] = (data_temp_2[23*j]>>3) | temp;
    }
    for(u8 i=0; i<46; i++)
      data_temp_3[i] = matrix_temp[i] | data_temp_2[i];
    SweepOut(data_temp_3);
    Delay(25);
  }
}

void HieuUng9(void)
{
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 i=0; i<30; i++)
    SetPixel(-1,i,0,0,0);
  for(u8 i=0; i<5; i++)
  {
    SetPixel(-1,2*(i - 1),0,0,0);
    SetPixel(-1,17 - 2*i,0,0,0);
    SetPixel(-1,13 + 2*i,0,0,0);
    SetPixel(-1,32 - 2*i,0,0,0);
    SetPixel(-1,2*i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,15 - 2*i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,15 + 2*i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,30 - 2*i, bluePWM,redPWM,greenPWM);
    for(u8 j=0; j<30; j++)
      SetPixel(-1,(60-j)%60, ReadPixel(-1, j, BLUE), ReadPixel(-1, j, RED), ReadPixel(-1, j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 i=0; i<4; i++)
  {
    SetPixel(-1,6-2*i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,7+2*i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,23 - 2*i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,22 + 2*i, bluePWM,redPWM,greenPWM);
    for(u8 j=0; j<30; j++)
      SetPixel(-1,(60-j)%60, ReadPixel(-1, j, BLUE), ReadPixel(-1, j, RED), ReadPixel(-1, j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng8(void)
{
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 i=0; i<30; i++)
    SetPixel(-1,i,0,0,0);
  for(u8 i=0; i<8; i++)
  {
    SetPixel(-1,i - 1,0,0,0);
    SetPixel(-1,16 - i,0,0,0);
    SetPixel(-1,14 + i,0,0,0);
    SetPixel(-1,31 - i,0,0,0);
    SetPixel(-1,i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,15 - i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,15 + i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,30 - i, bluePWM,redPWM,greenPWM);
    for(u8 j=0; j<30; j++)
      SetPixel(-1,(60-j)%60, ReadPixel(-1, j, BLUE), ReadPixel(-1, j, RED), ReadPixel(-1, j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
  for(u8 i=0; i<8; i++)
  {
    SetPixel(-1,7 - i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,8 + i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,22 - i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,23 + i, bluePWM,redPWM,greenPWM);
    for(u8 j=0; j<30; j++)
      SetPixel(-1,(60-j)%60, ReadPixel(-1, j, BLUE), ReadPixel(-1, j, RED), ReadPixel(-1, j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng7(void)
{
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 i=0; i<16; i++)
  {
    if(i==15)
      for(u8 j=0; j<16; j++)
        SetPixel(-1,2*j,bluePWM % 2, redPWM % 2, greenPWM % 2);
    else
      SetPixel(-1,2*i,bluePWM,redPWM,greenPWM);
    for(u8 j=0; j<30; j++)
      SetPixel(-1,(60-j)%60, ReadPixel(-1, j, BLUE), ReadPixel(-1, j, RED), ReadPixel(-1, j, GREEN));
    SweepOut(matrix_temp);
    Delay(50);
  }
}

void HieuUng6(void)
{
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 i=0; i<10; i++)
  { 
    if(i<5)
      SetPixel(-1,0, bluePWM,redPWM,greenPWM);
    else
      SetPixel(-1,0, 0, 0, 0);
    for(u8 j=0; j<30; j++)
      SetPixel(-1,(60-j)%60, ReadPixel(-1, j, BLUE), ReadPixel(-1, j, RED), ReadPixel(-1, j, GREEN));
    SweepOut(matrix_temp);
    Delay(DELAY/2);
    RotateHalf(-1);
  }
}

void HieuUng5(void)
{
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 i=0; i<16; i++)
  {
    if(i<15)
    {
      SetPixel(-1,i+16, ReadPixel(-1,i+15, BLUE), ReadPixel(-1,i+15, RED), ReadPixel(-1,i+15, GREEN));
      SetPixel(-1,60 - (i+16), ReadPixel(-1,i+15, BLUE), ReadPixel(-1,i+15, RED), ReadPixel(-1,i+15, GREEN));
    }
    SetPixel(-1,i,bluePWM,redPWM,greenPWM);
    SetPixel(-1,(60-i)%60,bluePWM,redPWM,greenPWM);
    SetPixel(-1,i+15, 0, 0, 0);  
    SetPixel(-1,61 - (i+16), 0, 0, 0);
    if(i>0)
    {
      SetPixel(-1,i - 1 ,0, 0, 0);
      SetPixel(-1,(61-i)%60 ,0, 0, 0);
    }
    SweepOut(matrix_temp);
    Delay(DELAY/2);
  }
}

void HieuUng4(void)
{
  bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
  for(u8 i=0; i<16; i++)
  {
    SetPixel(-1,i+16, ReadPixel(-1,i, BLUE), ReadPixel(-1,i, RED), ReadPixel(-1,i, GREEN));
    SetPixel(-1,60-(i+16), ReadPixel(-1,i, BLUE), ReadPixel(-1,i, RED), ReadPixel(-1,i, GREEN));
    SetPixel(-1,i, bluePWM,redPWM,greenPWM);
    SetPixel(-1,(60-i) % 60, bluePWM,redPWM,greenPWM);
    SweepOut(matrix_temp);
    Delay(DELAY/2);
  }
}

u8 Mirror(u8 point)
{
  if(point == 0) return 30;
  else if(point >0 && point<30) return 30 + point;
  else if(point == 30) return 0;
  else return point - 30;
}

void HieuUng3(u8 mode)
{
  for(u8 i=0; i<60; i++)
  {
    if(peak[i] != 0 && peak[(i+5) % 60]!=0 && Check(i))
    {
      for(u8 j=0; j<6; j++)
      {
        if(chuvan[peak[(i+j)%60] - 1] & (0x40>>j))
          SetPixel(-1, (j+i)%60, color[i]>>4, color[i]>>2,color[i] & 0x03);
        else
          SetPixel(-1, (j+i)%60, 0, 0, 0);
        peak[(i+j)%60]++;
        if(peak[(i+j)%60] == 9) 
        {
          peak[(i+j)%60] = 0;
          color[(i+j)%60] = 0x00;
        }
      }
      i+=6;
    }
    else if(peak[i] == 0 && peak[(i+5) % 60]==0 && Check(i))
    {
      bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
      if((i%4==0 &&rand()%16==0 && mode == 0)||(0==0 && mode == 1))
      {
        for(u8 j=0; j<6; j++)
        {
          color[(i+j)%60] = (bluePWM<<4)|(redPWM<<2)|greenPWM;
          peak[(i+j)%60]++;
          if(peak[(i+j)%60] == 9) peak[(i+j)%60] = 0;
        }
        i+=6;
      }
    }
  }
  SweepOut(matrix_temp);
  Delay(DELAY);
}

ErrorStatus Check(u8 point)
{
  ErrorStatus result = SUCCESS;
  for(u8 i=0; i<5; i++)
  {
    if((peak[(point + i)%60] != peak[(point+i+1)%60]) || (color[(point + i)%60] != color[(point+i+1)%60])) return ERROR;
  }
  return result;
}

void HieuUng2(void)
{
  for(u8 i=0; i<60; i++)
  {
    if(ReadPixel(-1,i, BLUE)!=0||ReadPixel(-1,i, RED)!=0||ReadPixel(-1,i, GREEN)!=0)
    {
      s8 temp[3];
      temp[0] = ReadPixel(-1,i, BLUE) - 1;
      temp[1] = ReadPixel(-1,i, RED) - 1;
      temp[2] = ReadPixel(-1,i, GREEN) - 1;
      for(u8 j=0; j<3; j++)
        if(temp[j]<0) temp[j] = 0;
      SetPixel(-1, i, temp[0], temp[1], temp[2]);
    }
    else
    {
      u8 c = rand() % 8;
      if(rand()%32==0)
        SetPixel(-1,i,(c&0x01)*3, ((c&0x02)>>1)*3, ((c&0x04)>>2)*3);
    }     
  }
  SweepOut(matrix_temp);
  Delay(DELAY);
}

void HieuUng1(void)
{
  for(u8 i=0; i<60; i++)
  {
    bluePWM = rand() % 4, redPWM = rand() % 4, greenPWM = rand() % 4;
    if(rand()%16==0)
      SetPixel(-1, i, bluePWM,redPWM,greenPWM);
    else
      SetPixel(-1, i, 0, 0, 0);
  }
  SweepOut(matrix_temp);
  Delay(DELAY);
}




