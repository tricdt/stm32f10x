#ifndef _FONT_H_
#define _FONT_H_

#include <common.h>

typedef struct {
  const unsigned char __code* Data;
  unsigned char Width;
  unsigned char Height;
  signed char YOffset;
} Font_TypeDef;

extern const Font_TypeDef Text[];
extern const Font_TypeDef Number[];

#endif