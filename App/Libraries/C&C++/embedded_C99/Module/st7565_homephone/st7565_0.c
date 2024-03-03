#include <st7565_homephone.h>
#include <config.h>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
static unsigned char _reverse_screen = 0;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ST7565_Reset_0()
{
  ST7565_CONFIG_DC_0(0);
  ST7565_CONFIG_CS_0(0);
  ST7565_SPI_WRITE_0(0xE2);             //reset
  ST7565_SPI_WAIT_0();
  ST7565_CONFIG_CS_0(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ST7565_Init_0(reg8 ReverseScreen)
{
  _reverse_screen = ReverseScreen << 2;
  ST7565_CONFIG_DC_0(0);
  ST7565_CONFIG_CS_0(0);
  if (ReverseScreen)
  {
    ST7565_SPI_WRITE_0(0xA0 | 1);       //SEG output reverse
    ST7565_SPI_WRITE_0(0xC0 | 8);       //COM output reverse
  }
  else
  {
    ST7565_SPI_WRITE_0(0xA0 | 0);       //SEG output no-reverse
    ST7565_SPI_WRITE_0(0xC0 | 0);       //COM output no-reverse
  }
  ST7565_SPI_WRITE_0(0x40 | 0);         //Display start line set = 0
  ST7565_SPI_WRITE_0(0xA6 | 0);         //inverse
  ST7565_SPI_WRITE_0(0xA2 | 1);         //1/7 bias
  ST7565_SPI_WRITE_0(0x28 | 7);         //Power control set = 7
  ST7565_SPI_WRITE_0(0x20 | 3);         //Select internal resistor ratio(Rb/Ra) mode = 3
  //ST7565_SPI_WRITE_0(0x81);             //Electronic volume mode = 0x18
  //ST7565_SPI_WRITE_0(0x18);
  //ST7565_SPI_WRITE_0(0xAC);             //Static indicator off, flashing mode = off
  //ST7565_SPI_WRITE_0(0x00);
  ST7565_SPI_WRITE_0(0xE0);             //write auto increment
  ST7565_SPI_WRITE_0(0xA4 | 0);         //Display all points = off
  ST7565_SPI_WAIT_0();
  ST7565_CONFIG_CS_0(1);
  //clear  
  ST7565_Clear_0();
  //show
  ST7565_CONFIG_CS_0(0);
  ST7565_CONFIG_DC_0(0);
  ST7565_SPI_WRITE_0(0xAE | 1);         //LCD display = ON
  ST7565_SPI_WAIT_0();
  ST7565_CONFIG_CS_0(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ST7565_Clear_0()
{
  reg8 i;
  ST7565_CONFIG_CS_0(0);
  for (i = 0; i < 8; i++)
  {
    reg8 j;
    ST7565_CONFIG_DC_0(0);
    ST7565_SPI_WRITE_0(0x10 | 0);     //column = _reverse_screen
    ST7565_SPI_WRITE_0(_reverse_screen);
    ST7565_SPI_WRITE_0(0xB0 | i);     //row = i
    ST7565_SPI_WAIT_0();
    ST7565_CONFIG_DC_0(1);
    for (j = 0; j < 128; j++)
      ST7565_SPI_WRITE_0(0x00);
    ST7565_SPI_WAIT_0();
  }
  ST7565_CONFIG_CS_0(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ST7565_Fill_0(const unsigned char __gptr* Data)
{
  reg8 i;
  ST7565_CONFIG_CS_0(0);
  for (i = 0; i < 8; i++)
  {
    reg8 j;
    ST7565_CONFIG_DC_0(0);
    ST7565_SPI_WRITE_0(0x10 | 0);     //column = _reverse_screen
    ST7565_SPI_WRITE_0(_reverse_screen);
    ST7565_SPI_WRITE_0(0xB0 | i);     //row = i
    ST7565_SPI_WAIT_0();
    ST7565_CONFIG_DC_0(1);
    for (j = 0; j < 128; j++)
      ST7565_SPI_WRITE_0(Data[j]);
    Data += 128;
    ST7565_SPI_WAIT_0();
  }
  ST7565_CONFIG_CS_0(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ST7565_FillPart_0(const unsigned char __gptr* Data, reg8 X0, reg8 Y0, reg8 X1, reg8 Y1)
{
  reg8 x_length = X1 - X0 + 1;
  X0 += _reverse_screen;
  ST7565_CONFIG_CS_0(0);
  while (Y0 <= Y1)
  {
    reg8 j;
    ST7565_CONFIG_DC_0(0);
    ST7565_SPI_WRITE_0(0x10 | (X0 >> 4));
    ST7565_SPI_WRITE_0(X0 & 0x0F);
    ST7565_SPI_WRITE_0(0xB0 | Y0);
    ST7565_SPI_WAIT_0();
    ST7565_CONFIG_DC_0(1);
    for (j = 0; j < x_length; j++)
      ST7565_SPI_WRITE_0(Data[j]);
    Data += x_length;
    Y0++;
    ST7565_SPI_WAIT_0();
  }
  ST7565_CONFIG_CS_0(0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ST7565_On_0()
{
  ST7565_CONFIG_DC_0(0);
  ST7565_CONFIG_CS_0(0);
  ST7565_SPI_WRITE_0(0xAE | 1);
  ST7565_SPI_WAIT_0();
  ST7565_CONFIG_CS_0(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ST7565_Off_0()
{
  ST7565_CONFIG_DC_0(0);
  ST7565_CONFIG_CS_0(0);
  ST7565_SPI_WRITE_0(0xAE | 0);
  ST7565_SPI_WAIT_0();
  ST7565_CONFIG_CS_0(1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ST7565_LowPower_0()
{
  ST7565_CONFIG_DC_0(0);
  ST7565_CONFIG_CS_0(0);
  ST7565_SPI_WRITE_0(0xAE | 0);
  ST7565_SPI_WRITE_0(0xA4 | 1);
  ST7565_SPI_WAIT_0();
  ST7565_CONFIG_CS_0(1);
}