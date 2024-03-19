#include "mystm32f10x.h"

u32 mPsc; // Giá trị đặt trước
u32 mArr; //Giá trị ban đầu của bộ đếm
u8 ErrorMessage;
void TIM2_Config(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_Initstructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_TimeBaseInitStructure.TIM_Prescaler = 256;
  TIM_TimeBaseInitStructure.TIM_Period = 1500;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
  NVIC_Initstructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_Initstructure);  
}

void TIM1_Config(void){
   #ifdef USE_TIMER
      TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
      NVIC_InitTypeDef NVIC_Initstructure;
   #endif

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
   TIM_TimeBaseInitStructure.TIM_Prescaler = 0x0465-1;
   TIM_TimeBaseInitStructure.TIM_Period = 0xFA00-1;
   TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
   TIM_ClearFlag(TIM1, TIM_FLAG_Update);
   TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
   TIM_Cmd(TIM1, ENABLE);
   NVIC_Initstructure.NVIC_IRQChannel = TIM1_UP_IRQn;
   NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_Initstructure);  
}
void MyTimer_Init(TIM_TypeDef *timer,u16 second,u16 millisecond,u16 microsecond,u8 Prioritygroup,u8 preemprionPriority,u8 subPriority){
   #ifdef USE_TIMER
      uint8_t timerIrqChannel;
	   TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	   NVIC_InitTypeDef NVIC_InitStructure;
      if(!MyTimer_Conversion(second, millisecond, microsecond)){
         ErrorMessage = 1; return;
      }
	#ifndef USE_TIMER1
	#ifndef USE_TIMER2
	#ifndef USE_TIMER3
	#ifndef USE_TIMER4
		return ;
	#endif
	#endif
	#endif
	#endif

      
   if(timer==TIM1){
      #ifdef USE_TIMER1
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		timerIrqChannel=TIM1_UP_IRQn;
		#endif
   }
   else if(timer==TIM2)
	{
		#ifdef USE_TIMER2
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		timerIrqChannel=TIM2_IRQn;
		#endif
	}
	else if(timer==TIM3)
	{
		#ifdef USE_TIMER3
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		timerIrqChannel=TIM3_IRQn;
		#endif
	}
	else if(timer==TIM4)
	{
		#ifdef USE_TIMER4
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		timerIrqChannel=TIM4_IRQn;
		#endif
	}
   else{}
   TIM_BaseInitStructure.TIM_Period = mArr - 1;
   TIM_BaseInitStructure.TIM_Prescaler = mPsc - 1;
   TIM_BaseInitStructure.TIM_ClockDivision = 0;
   TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
   TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(timer, &TIM_BaseInitStructure);
   TIM_ClearFlag(timer, TIM_FLAG_Update);
   TIM_ITConfig(timer, TIM_IT_Update, ENABLE);
   TIM_Cmd(timer, ENABLE);
   switch (Prioritygroup)
   {
      case 0:
         NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
         break;
      case 1:
         NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
         break;
      case 2:
         NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
         break;
      case 4:
         NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
         break;
      default:
         NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
         break;
   }
   NVIC_InitStructure.NVIC_IRQChannel = timerIrqChannel;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemprionPriority;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPriority;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   ErrorMessage = 0;
   #endif

}

FlagStatus MyTimer_Conversion(u16 s, u16 ms, u16 us){
   u32 time;
   u16 tempPsc;
   u32 tempArr=0xfffff;
   #ifdef SYSCLK_HSE
   u32 clock= 8;
   #elif defined SYSCLK_FREQ_24MHz
   u32 clock = 24;
   #elif defined SYSCLK_FREQ_36MHz
   u32 clock = 36;
   #elif defined SYSCLK_FREQ_48MHz
   u32 clock = 48;
   #elif defined SYSCLK_FREQ_56MHz
   u32 clock = 56;
   #elif defined SYSCLK_FREQ_72MHz
   u32 clock = 72;
   #endif
   time=s*1000000+ms*1000+us; 
   
	if(time >INPUTMAX)
		return RESET; 
	if(time<COEFFICIENT) 
		mPsc=1;
	else
		mPsc=time/COEFFICIENT; 
	tempPsc=mPsc;
   while( ((time*clock)% mPsc!=0  ||  tempArr>0xffff ) && mPsc<=65535)
	{
		mPsc++;	
		tempArr=(time*clock)/mPsc; 
	}
	
   if(mPsc>=65535) 
	{
		mPsc=tempPsc;
		tempArr=(time*clock)/mPsc;
	}
   else
		mArr=tempArr;
	
	return SET;
}

void MyTimer_OnOrOffIrq(TIM_TypeDef *timer, FlagStatus Switch){
   if(Switch==SET)
      timer->DIER |=1<<0;
   else
      timer->DIER &=0<<0;
}

void MyTimer_ClearCNT(TIM_TypeDef *timer)
{
   timer->CNT &=0;
}

void MyTimer_Start(TIM_TypeDef *timer){
   TIM_Cmd(timer, ENABLE);
}

void MyTimer_Stop(TIM_TypeDef *timer){
   TIM_Cmd(timer, DISABLE);
}