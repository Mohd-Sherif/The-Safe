/*
 * EEPROM.c
 *
 * Created: 29/09/2021 03:56:56 PM
 *  Author: Mohamed Sherif
 */ 
#include <avr/io.h>
#include "../LIB/std_macros.h"

void EEPROM_vwrite(unsigned short address,unsigned char data){
	EEAR=address; //Set up address register
	//Another method:-
	//EEARL=(char)address;
	//EEARH=(char)(address>>8);
	EEDR=data; //Set up data register
	SET_BIT(EECR,EEMWE); //Write logical one to EEMWE
	SET_BIT(EECR,EEWE); //Start EEPROM write by setting EEWE
	while(READ_BIT(EECR,EEWE)); //Wait for completion of  write operation
}

unsigned char EEPROM_u8read(unsigned short address){
	EEAR=address; //Set up address register
	//Another method:-
	//EEARL=(char)address;
	//EEARH=(char)(address>>8);
	SET_BIT(EECR,EERE); //Start EEPROM read by setting EERE
	return EEDR; //Return data from data register
}