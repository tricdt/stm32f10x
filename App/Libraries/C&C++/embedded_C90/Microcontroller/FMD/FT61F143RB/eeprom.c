unsigned char EEPROM_Read(unsigned char Address)
{
    EEADRL = Address;
    CFGS = 0;
    EEPGD = 0;
   	RD = 1;
    while (RD);
    return EEDATL;
}
void EEPROM_WriteTrigger()
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
void 

