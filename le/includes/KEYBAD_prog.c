/************************************************/
/********* Author: Mikhail Medhat *****************/
/********* Date  : 30/07/2026   *****************/
/********* File: program file *****************/
/************************************************/


#include "Std_Types.h"
#include "Bit_Math.h"
#include <util/delay.h>

#include "DIO_int.h"


#include"KEYBAD_config.h"
#include"KEYBAD_private.h"
#include"KEYBAD_int.h"

void KEY_PADINTI(void)
{
    DIO_voidSetPinDirection(KEYPAD_ROW0);
    DIO_voidSetPinDirection(KEYPAD_ROW1);
    DIO_voidSetPinDirection(KEYPAD_ROW2);
    DIO_voidSetPinDirection(KEYPAD_ROW3);

    DIO_voidSetPinDirection(KEYPAD_COL0);
    DIO_voidSetPinDirection(KEYPAD_COL1);
    DIO_voidSetPinDirection(KEYPAD_COL2);
    DIO_voidSetPinDirection(KEYPAD_COL3);

    DIO_voidSetpinValue(KEYPAD_ROW0_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_ROW1_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_ROW2_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_ROW3_H,HIGH);

    DIO_voidSetpinValue(KEYPAD_COL0_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL1_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL2_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL3_H,HIGH);
}

u8 GET_u8PRESSEDKEY(void)
{
    u8 key_pressed;
    u8 key_value=0;
    DIO_voidSetpinValue(KEYPAD_COL0_H,LOW);
    DIO_voidSetpinValue(KEYPAD_COL1_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL2_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL3_H,HIGH);

    key_pressed  = DIO_u8GetPinValue(KEYPAD_ROW0_H);
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW1_H) << 1;
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW2_H) << 2;
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW3_H) << 3;

   switch(key_pressed)
   {
    case 0b00001110: key_value = '7'; break;
    case 0b00001101: key_value = '4'; break;
    case 0b00001011: key_value = '1'; break;
    case 0b00000111: key_value = '#'; break;
   }

    DIO_voidSetpinValue(KEYPAD_COL0_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL1_H,LOW);
    DIO_voidSetpinValue(KEYPAD_COL2_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL3_H,HIGH);

    key_pressed  = DIO_u8GetPinValue(KEYPAD_ROW0_H);
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW1_H) << 1;
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW2_H) << 2;
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW3_H) << 3;

   switch(key_pressed)
   {
    case 0b00001110: key_value = '8'; break;
    case 0b00001101: key_value = '5'; break;
    case 0b00001011: key_value = '2'; break;
    case 0b00000111: key_value = '0'; break;
   }

    DIO_voidSetpinValue(KEYPAD_COL0_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL1_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL2_H,LOW);
    DIO_voidSetpinValue(KEYPAD_COL3_H,HIGH);

    key_pressed  = DIO_u8GetPinValue(KEYPAD_ROW0_H);
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW1_H) << 1;
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW2_H) << 2;
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW3_H) << 3;

   switch(key_pressed)
   {
    case 0b00001110: key_value = '9'; break;
    case 0b00001101: key_value = '6'; break;
    case 0b00001011: key_value = '3'; break;
    case 0b00000111: key_value = '='; break;
   }

    DIO_voidSetpinValue(KEYPAD_COL0_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL1_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL2_H,HIGH);
    DIO_voidSetpinValue(KEYPAD_COL3_H,LOW);

    key_pressed  = DIO_u8GetPinValue(KEYPAD_ROW0_H);
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW1_H) << 1;
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW2_H) << 2;
    key_pressed |= DIO_u8GetPinValue(KEYPAD_ROW3_H) << 3;

   switch(key_pressed)
   {
    case 0b00001110: key_value = '/'; break;
    case 0b00001101: key_value = '*'; break;
    case 0b00001011: key_value = '-'; break;
    case 0b00000111: key_value = '+'; break;
   }


 return key_value;

}













