#include "mystm32f10x_gpio.h"

const  u16 mPin[16]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7, GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11,GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15};


void MyGPIO_Deinit(void){}

void MyGPIO_Init(GPIO_TypeDef *port, uint16_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, uint32_t bus){
   GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(bus, ENABLE);
   GPIO_InitStructure.GPIO_Mode = mode;
   GPIO_InitStructure.GPIO_Speed = speed;
   GPIO_InitStructure.GPIO_Pin = pin;
   GPIO_Init(port, &GPIO_InitStructure);
}

void MyGPIO_DisableSWJTAG(BitAction disableSW , BitAction disableJtag){
  u8 temp = 0;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  if(disableSW && disableJtag) temp = 4;
  else if(!disableSW && disableJtag) temp = 2;
  else  temp = 4;
  GPIO_PinRemapConfig(0x00300000|(temp<<8),ENABLE);
}

void MyGPIO_SetLevel(GPIO_TypeDef *port, u16 pin, BitAction level){
  if(level) GPIO_SetBits(port, mPin[pin]);
  else GPIO_ResetBits(port, mPin[pin]);
}
FlagStatus MyGPIO_GetLevel(GPIO_TypeDef *port, u16 pin){
   if(GPIO_ReadInputDataBit(port, mPin[pin])) return RESET;
   else return SET;
}

void MyGPIO_Toggle(GPIO_TypeDef *port, u16 pin){
   if(GPIO_ReadInputDataBit(port, mPin[pin])) GPIO_ResetBits(port, mPin[pin]);
   else GPIO_SetBits(port, mPin[pin]);
}

void MyGPIO_ChangeMode(GPIO_TypeDef *port, uint16_t pin, GPIOMode_TypeDef mode){
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Mode = mode;
   GPIO_InitStructure.GPIO_Pin = mPin[pin];
   GPIO_Init(port, &GPIO_InitStructure);
}