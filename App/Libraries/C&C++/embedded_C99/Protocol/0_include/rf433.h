#ifndef _RF433_H_
#define _RF433_H_

#include <common.h>

typedef struct
{
  unsigned char Data[3];
} RF433_TypeDef;
extern __no_init RF433_TypeDef __data RF433;

void RF433_Begin_0();
void RF433_Capture_0();         //20us trigger
reg8 RF433_Process_0();

#endif