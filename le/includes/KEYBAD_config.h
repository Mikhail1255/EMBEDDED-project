/************************************************/
/********* Author: Mikhail Medhat *****************/
/********* Date  : 30/07/2026   *****************/
/********* File: Config.file  *****************/
/************************************************/
#ifndef   KEYBAD_CONFIG_H
#define   KEYBAD_CONFIG_H




#define KEYPAD_ROW0    DIO_PORTC,DIO_PIN0,INPUT
#define KEYPAD_ROW1    DIO_PORTC,DIO_PIN1,INPUT
#define KEYPAD_ROW2    DIO_PORTC,DIO_PIN2,INPUT
#define KEYPAD_ROW3    DIO_PORTC,DIO_PIN3,INPUT




#define KEYPAD_COL0   DIO_PORTC,DIO_PIN4,OUTPUT
#define KEYPAD_COL1   DIO_PORTC,DIO_PIN5,OUTPUT
#define KEYPAD_COL2   DIO_PORTC,DIO_PIN6,OUTPUT
#define KEYPAD_COL3   DIO_PORTC,DIO_PIN7,OUTPUT

#define KEYPAD_ROW0_H    DIO_PORTC,DIO_PIN0
#define KEYPAD_ROW1_H    DIO_PORTC,DIO_PIN1
#define KEYPAD_ROW2_H    DIO_PORTC,DIO_PIN2
#define KEYPAD_ROW3_H    DIO_PORTC,DIO_PIN3




#define KEYPAD_COL0_H   DIO_PORTC,DIO_PIN4
#define KEYPAD_COL1_H   DIO_PORTC,DIO_PIN5
#define KEYPAD_COL2_H   DIO_PORTC,DIO_PIN6
#define KEYPAD_COL3_H   DIO_PORTC,DIO_PIN7




#endif









