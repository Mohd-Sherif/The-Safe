/*
 * The Safe project.c
 *
 * Created: 08/10/2021 02:58:42 PM
 * Author : Mohamed Sherif
 */ 

#include "HAL/LCD.h"
#include "HAL/Keypad.h"
#include "MCAL/EEPROM.h"
#define EEPROM_STATUS 0x20
#define EEPROM_PASS_LOC1 0x21
#define EEPROM_PASS_LOC2 0x22
#define EEPROM_PASS_LOC3 0x23
#define EEPROM_PASS_LOC4 0x24
#define MAX_TRIES 3

int main(void)
{
    unsigned char value=NOT_PRESSED,i,tries=MAX_TRIES,pass[4]={NOT_PRESSED,NOT_PRESSED,NOT_PRESSED,NOT_PRESSED};
	LCD_vinit();
	LCD_vsend_cmd(CURSOR_OFF_DISPLAY_ON);
	Keypad_vinit();
	if(EEPROM_u8read(EEPROM_STATUS)==NOT_PRESSED){
		LCD_vsend_string("Set Pass:");
		for(i=0;i<=3;i++){
			do{
				value=Keypad_u8read();
			}while(value==NOT_PRESSED);
			LCD_vsend_char(value);
			_delay_ms(500);
			LCD_vmove_cursor(1,10+i);
			LCD_vsend_char('*');
			EEPROM_vwrite(EEPROM_PASS_LOC1+i,value);
		}
		EEPROM_vwrite(EEPROM_STATUS,0x00);
		LCD_vCLR_screen();
		LCD_vsend_string("Password was set");
		LCD_vmove_cursor(2,1);
		LCD_vsend_string("successfully");
		_delay_ms(2000);
		LCD_vCLR_screen();
	}
    while (1) 
    {
		if(tries>0){
			LCD_vsend_string("Enter Pass:");
			for(i=0;i<=3;i++){
				do{
					value=Keypad_u8read();
				}while(value==NOT_PRESSED);
				LCD_vsend_char(value);
				_delay_ms(500);
				LCD_vmove_cursor(1,12+i);
				LCD_vsend_char('*');
				pass[i]=value;
			}
			LCD_vCLR_screen();
			if(EEPROM_u8read(EEPROM_PASS_LOC1)==pass[0] && EEPROM_u8read(EEPROM_PASS_LOC2)==pass[1] && EEPROM_u8read(EEPROM_PASS_LOC3)==pass[2] && EEPROM_u8read(EEPROM_PASS_LOC4)==pass[3]){
				LCD_vsend_string("Correct Password");
				LCD_vmove_cursor(2,1);
				LCD_vsend_string("Safe is opened");
				break;
			}
			else{
				tries--;
				LCD_vsend_string("Wrong Password!");
				LCD_vmove_cursor(2,1);
				LCD_vsend_string("Please try again");
				_delay_ms(1500);
				LCD_vCLR_screen();
				LCD_vsend_string("Tries left=");
				LCD_vsend_char(tries+48);
				_delay_ms(1500);
			}
			LCD_vCLR_screen();
		}
		else{
			LCD_vsend_string("Safe is closed");
			break;
		}
    }
}

