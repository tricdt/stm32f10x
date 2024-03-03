#define R0      0x00
#define R1      0x01
#define TH0     0x8C
#define TL0     0x8A

  DATA
  EXTERN Tick
  
  CODE
//event
  ORG           000Bh
  POP           R0      //000B-000C
  POP           R1      //000D-000E
  LJMP          SWITCH  //000F-0010
//rtos switch function
  ORG           0093h
SWITCH:
  MOV           TH0, #0xFA
  MOV           TL0, #0xCA
  MOV           Tick, #1
  RETI
  
  END