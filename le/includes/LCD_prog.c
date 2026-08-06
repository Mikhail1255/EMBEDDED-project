
/************************************************/
/********* Author: Mikhail Medhat *****************/
/********* Date  : 30/07/2026   *****************/
/********* File: Program File  *****************/
/************************************************/
#include "Std_Types.h"
#include "Bit_Math.h"
#include <util/delay.h>

#include "DIO_int.h"

/***/
#include "LCD_config.h"
#include "LCD_private.h"
#include "LCD_int.h"

void LCD_voidLCDInit(void)
{
	/**
	 1- Wait 30ms
	 2- Send Home Command, wait 1 ms
	 3- send Function set8 bit Command wait 1 ms
	 4- send Display on/off Command wait 1ms
	 5- Send Display Clear Command wait 1ms
	 6- Send Enty Mode Command, wait 1ms
	*/

	/* Configure Control Pins (RS, RW, EN) as Output */
	DIO_voidSetPinDirection(LCD_RS, OUTPUT);
	DIO_voidSetPinDirection(LCD_RW, OUTPUT);
	DIO_voidSetPinDirection(LCD_EN, OUTPUT);

	/* Configure Data Bus Pins (D0-D7) as Output */
	DIO_voidSetPinDirection(LCD_D0, OUTPUT);
	DIO_voidSetPinDirection(LCD_D1, OUTPUT);
	DIO_voidSetPinDirection(LCD_D2, OUTPUT);
	DIO_voidSetPinDirection(LCD_D3, OUTPUT);
	DIO_voidSetPinDirection(LCD_D4, OUTPUT);
	DIO_voidSetPinDirection(LCD_D5, OUTPUT);
	DIO_voidSetPinDirection(LCD_D6, OUTPUT);
	DIO_voidSetPinDirection(LCD_D7, OUTPUT);

	/* 1- Wait 30ms for LCD Power-Up */
	_delay_ms(30);

	/* 2- Send Home Command, wait 1ms */
	LCD_voidSendCommand(LCD_HOME);
	_delay_ms(1);

	/* 3- Send Function Set 8-bit Command, wait 1ms */
	LCD_voidSendCommand(LCD_FUNCTIONSET_8BIT);
	_delay_ms(1);

	/* 4- Send Display On/Off Command, wait 1ms */
	LCD_voidSendCommand(LCD_DISPLAYON);
	_delay_ms(1);

	/* 5- Send Display Clear Command, wait 1ms */
	LCD_voidSendCommand(LCD_CLEAR);
	_delay_ms(1);

	/* 6- Send Entry Mode Command, wait 1ms */
	LCD_voidSendCommand(LCD_ENTRY_MODE);
	_delay_ms(1);
}

void LCD_voidSendCommand(u8 u8CMD)
{
	DIO_voidSetpinValue(LCD_RS, LOW);   /* RS = 0 -> Command Register  */
	DIO_voidSetpinValue(LCD_RW, LOW);   /* RW = 0 -> Write Mode        */

	LCD_voidPutonBus(u8CMD);

	DIO_voidSetpinValue(LCD_EN, HIGH);  /* Pulse Enable to latch data  */
	_delay_us(1);
	DIO_voidSetpinValue(LCD_EN, LOW);
}

void LCD_voidSendData(u8 u8Data)
{
	DIO_voidSetpinValue(LCD_RS, HIGH);  /* RS = 1 -> Data Register     */
	DIO_voidSetpinValue(LCD_RW, LOW);   /* RW = 0 -> Write Mode        */

	LCD_voidPutonBus(u8Data);

	DIO_voidSetpinValue(LCD_EN, HIGH);  /* Pulse Enable to latch data  */
	_delay_us(1);
	DIO_voidSetpinValue(LCD_EN, LOW);
}


static void LCD_voidPutonBus(u8 u8Char)
{
	DIO_voidSetpinValue(LCD_D0, GET_BIT(u8Char, 0));
	DIO_voidSetpinValue(LCD_D1, GET_BIT(u8Char, 1));
	DIO_voidSetpinValue(LCD_D2, GET_BIT(u8Char, 2));
	DIO_voidSetpinValue(LCD_D3, GET_BIT(u8Char, 3));
	DIO_voidSetpinValue(LCD_D4, GET_BIT(u8Char, 4));
	DIO_voidSetpinValue(LCD_D5, GET_BIT(u8Char, 5));
	DIO_voidSetpinValue(LCD_D6, GET_BIT(u8Char, 6));
	DIO_voidSetpinValue(LCD_D7, GET_BIT(u8Char, 7));
}


void LCD_GotoXY(u8 x, u8 y)
{
	u8 Local_u8Address = 0;

	switch(y)
	{
		case 0: Local_u8Address = x + 0x00; break;
		case 1: Local_u8Address = x + 0x40; break;
		case 2: Local_u8Address = x + 0x10; break;
		case 3: Local_u8Address = x + 0x50; break;
	}

	LCD_voidSendCommand(LCD_SETCURSOR | Local_u8Address);
}

void LCD_voidWriteString(char * u8string)
{
	u8 Local_u8Iterator = 0;

	while(u8string[Local_u8Iterator] != '\0')
	{
		LCD_voidSendData(u8string[Local_u8Iterator]);
		Local_u8Iterator++;
	}
}

void LCD_voidWriteNumber(u8 u8Number)
{
	u8 u8Buffer[4];
	u8 u8Index = 0;

	if(u8Number == 0)
	{
		LCD_voidSendData('0');
		return;
	}

	while(u8Number != 0)
	{
		u8Buffer[u8Index] = (u8Number % 10) + '0';
		u8Number /= 10;
		u8Index++;
	}

	while(u8Index != 0)
	{
		u8Index--;
		LCD_voidSendData(u8Buffer[u8Index]);
	}
}
