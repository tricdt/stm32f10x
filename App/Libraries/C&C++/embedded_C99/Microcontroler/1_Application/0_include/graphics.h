#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

typedef struct
{
  unsigned short Red : 5;
  unsigned short Green : 6;
  unsigned short Blue : 5;
} Color_TypeDef;

typedef struct
{
  signed short X;
  signed short Y;
} Point_TypeDef;

typedef struct
{
  unsigned short Width;
  unsigned short Height;
} Size_TypeDef;

#endif