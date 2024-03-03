#include	"SYSCFG.h"

void NV_Init(unsigned char IsFlash, unsigned char WriteEnable)
{
    CFGS = 0;
    EEPGD = IsFlash;
    WREN = WriteEnable;
}
unsigned char EEPROM_Read(unsigned char Address)
{
    EEADRL = Address;
   	RD = 1;
    NOP();
    NOP();
    NOP();
    NOP();
    return EEDATL;
}
void NV_WriteTrigger()
{
#asm
	MOVLB 	3H						//make sure bank is 3 -> _EECON2
    MOVLW	0x55
    MOVWF	_EECON2 & 0x7F
    MOVLW	0xAA
    MOVWF	_EECON2 & 0x7F
    BSF		_EECON1 & 0x7F,1  		//WR = 1
    NOP
    NOP
#endasm
}
unsigned char EEPROM_Write(unsigned char Address, unsigned char Data)
{
    EEADRL = Address;
	EEDATL = Data;
	EEIF = 0;
	NV_WriteTrigger();
	while(WR);
    return WRERR;
}
unsigned char Flash_Write(unsigned short Address, unsigned short Data)
{
    EEADRH = Address >> 8;
    EEADRL = Address & 0xFF;    
    EEDATH = Data >> 8;
	EEDATL = Data & 0xFF;
    EEIF = 0;
	NV_WriteTrigger();
	while(WR);
    return WRERR;
}
void Flash_Erase(unsigned short Address)
{
    FREE = 1;
    EEADRH = Address >> 8;
    EEADRL = Address & 0xFF;    
    EEIF = 0;
	NV_WriteTrigger();
    while(WR);
    FREE = 0;
    return WRERR;
}