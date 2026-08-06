/************************************************/
/********* Author: Mikhail Medhat *****************/
/********* Date  : 30/07/2026   *****************/
/********* File: interface File  *****************/
/************************************************/
#ifndef   LCD_INTERFACE_H
#define   LCD_INTERFACE_H

void LCD_voidLCDInit(void);
void LCD_voidSendCommand(u8 u8CMD);
void LCD_voidSendData(u8 u8Data);
void LCD_GotoXY(u8 x, u8 y);
void LCD_voidWriteString(char * u8string);
void LCD_voidWriteNumber(u8 u8Number);

#endif
