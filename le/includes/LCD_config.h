/************************************************/
/********* Author: Mikhail Medhat *****************/
/********* Date  : 30/07/2026   *****************/
/********* File: Configuration File  *****************/
/************************************************/
#ifndef   LCD_CONFIG_H
#define   LCD_CONFIG_H

#define   LCD_RS    DIO_PORTB,DIO_PIN5
#define   LCD_EN	DIO_PORTB,DIO_PIN6
#define   LCD_RW	DIO_PORTB,DIO_PIN7
#define LCD_CLEAR			0x01

#define LCD_D0		DIO_PORTA,DIO_PIN3
#define LCD_D1		DIO_PORTA,DIO_PIN4
#define LCD_D2		DIO_PORTA,DIO_PIN5
#define LCD_D3		DIO_PORTA,DIO_PIN6
#define LCD_D4		DIO_PORTA,DIO_PIN7
#define LCD_D5		DIO_PORTD,DIO_PIN4
#define LCD_D6		DIO_PORTD,DIO_PIN5
#define LCD_D7		DIO_PORTB,DIO_PIN4

#endif
