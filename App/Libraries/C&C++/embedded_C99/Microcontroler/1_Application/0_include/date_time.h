#ifndef _DATE_TIME_H_
#define _DATE_TIME_H_

typedef union
{
  unsigned char Day;
  unsigned char Month;
  unsigned char Year;
} Date_TypeDef;
typedef struct
{
  unsigned char Second;
  unsigned char Minute;
  unsigned char Hour;
} Time_TypeDef;
typedef struct
{
  Time_TypeDef Time;
  unsigned char WeekDay;
  Date_TypeDef Date;
} DateTime_TypeDef;

#endif