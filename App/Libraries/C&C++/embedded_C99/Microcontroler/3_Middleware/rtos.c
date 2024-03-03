#include <rtos.h>

Task_TypeDef Tasks[RTOS_MAX_TASK];
TaskManager_TypeDef TaskManager;

static void _RTOS_TaskEnd()
{
  RTOS_DISABLE_IRQ();
  TaskManager.Running--;
  Tasks[TaskManager.Index].Status = TASK_STATUS_STOP;
  TaskManager.Total--;
  if (TaskManager.Total)
  {
    RTOS_ENABLE_IRQ();
    RTOS_SWITCH_TRIGGER();
  }
  else
    while (1);
}

CPU_TypeDef* RTOS_GetCurrentCPU()
{
  return &(Tasks[TaskManager.Index].CPU);
}
CPU_TypeDef* RTOS_GetNextCPU()
{
  unsigned int j = (TaskManager.Index + 1) % RTOS_MAX_TASK;
  for (unsigned int i = 0; i < (RTOS_MAX_TASK - 1); i++, j = (j + 1) % RTOS_MAX_TASK)
  {    
    if (Tasks[j].Status & (TASK_STATUS_RUNNING | TASK_STATUS_SLEEP))
    {
      TaskManager.Index = j;
      return &Tasks[j].CPU;
    }
  }
  return NULL;
}

void RTOS_Begin(CPU_TypeDef* MainCPU)
{
  extern void RTOS_ASM_Begin(CPU_TypeDef* CPU);
  RTOS_ASM_Begin(&Tasks[0].CPU);
  Tasks[0].Status = TASK_STATUS_RUNNING;
  TaskManager.Running = 1;
  TaskManager.Total = 1;
}

void RTOS_CreateTask(void (*MainFunction)())
{
  RTOS_DISABLE_IRQ();
  for (unsigned int i = 0; i < RTOS_MAX_TASK; i++)
  {
    if (i != TaskManager.Index && Tasks[i].Status == TASK_STATUS_STOP)
    {      
      TaskManager.Running++;
      TaskManager.Total++;
      Tasks[i].MainFunction = MainFunction;
      RTOS_InitTask(&Tasks[i], MainFunction, _RTOS_TaskEnd);
      Tasks[i].Status = TASK_STATUS_RUNNING;  
      break;
    }    
  }
  RTOS_ENABLE_IRQ();
}

void RTOS_Delay(unsigned int Time)
{
  unsigned int now = RTOS_GETTIME();
  TaskManager.Running--;
  Tasks[TaskManager.Index].Status = TASK_STATUS_SLEEP;
  while ((RTOS_GETTIME() - now) < Time)
    RTOS_SWITCH_TRIGGER();
  TaskManager.Running++;
  Tasks[TaskManager.Index].Status = TASK_STATUS_RUNNING;
}

void RTOS_DeleteTaskByIndex(unsigned int Index)
{
  RTOS_DISABLE_IRQ();
  if (Tasks[Index].Status == TASK_STATUS_RUNNING)
    TaskManager.Running--;
  Tasks[Index].Status = TASK_STATUS_STOP;
  TaskManager.Total--;
  if (Index == TaskManager.Index)
  {
    if (TaskManager.Total)
    {
      RTOS_ENABLE_IRQ();
      RTOS_SWITCH_TRIGGER();
    }
    else
      while (1);
  }
  else
    RTOS_ENABLE_IRQ();
}

void RTOS_DeleteTask(void (*MainFunction)())
{
  RTOS_DISABLE_IRQ();
  unsigned int current = 0;
  for (unsigned int i = 0; i < RTOS_MAX_TASK; i++)
  {
    if (Tasks[i].MainFunction == MainFunction)
    {
      if (i == TaskManager.Index)
        current = 1;
      if (Tasks[i].Status == TASK_STATUS_RUNNING)
        TaskManager.Running--;
      Tasks[i].Status = TASK_STATUS_STOP;      
      TaskManager.Total--;
    }
  }
  if (current)
  {
    if (TaskManager.Total)
    {
      RTOS_ENABLE_IRQ();
      RTOS_SWITCH_TRIGGER();
    }
    else
      while (1);
  }
  else
    RTOS_ENABLE_IRQ();
}