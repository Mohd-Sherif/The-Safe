/*
 * EEPROM.h
 *
 * Created: 29/09/2021 03:57:12 PM
 *  Author: Mohamed Sherif
 */ 

#ifndef EEPROM_H_
#define EEPROM_H_

/*
Function Name        : EEPROM_vwrite
Function Returns     : void
Function Arguments   : unsigned short address,unsigned char data
Function Description : write one byte to the given address.
*/
void EEPROM_vwrite(unsigned short address,unsigned char data);

/*
Function Name        : EEPROM_u8read
Function Returns     : unsigned char
Function Arguments   : unsigned short address
Function Description : read one byte from the given address.
*/
unsigned char EEPROM_u8read(unsigned short address);

#endif /* EEPROM_H_ */