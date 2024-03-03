#ifndef _RTOS_H_
#define _RTOS_H_

#include <config.h>

typedef enum
{
  TASK_STATUS_STOP      = 0,
  TASK_STATUS_RUNNING   = 1,
  TASK_STATUS_SLEEP     = 2,
  TASK_STATUS_PAUSE     = 4,
} TASK_STATUS;
typedef struct
{
  unsigned int Status;
  unsigned int Stack[RTOS_STACK_SIZE];
  CPU_TypeDef CPU;
  void (*MainFunction)();
} Task_TypeDef;
extern Task_TypeDef Tasks[RTOS_MAX_TASK];
typedef struct
{
  unsigned int Index;
  unsigned int Total;
  unsigned int Running;
} TaskManager_TypeDef;
extern TaskManager_TypeDef TaskManager;

void RTOS_Begin(CPU_TypeDef* MainCPU);

extern void RTOS_InitTask(Task_TypeDef* Task, void (*MainFunction)(), void (*EndFunction)());
void RTOS_CreateTask(void (*MainFunction)());

void RTOS_Delay(unsigned int Time);
void RTOS_DeleteTaskByIndex(unsigned int Index);
void RTOS_DeleteTask(void (*MainFunction)());

#endif