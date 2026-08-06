/************************************************/
/********* Author: Mikhail Medhat *****************/
/********* Date  : 29/07/2026   *****************/
/********* File  : DIO_program.c ****************/
/************************************************/
#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_int.h"
#include "DIO_private.h"
#include "DIO_config.h"

void DIO_voidInitialization(void)
{
	DDRA = DIO_PORTA_DIRECTIONS;
	DDRB = DIO_PORTB_DIRECTIONS;
	DDRC = DIO_PORTC_DIRECTIONS;
	DDRD = DIO_PORTD_DIRECTIONS;
}

void DIO_voidSetPinDirection(u8 PortID, u8 PinID, u8 Direction)
{
	if(PortID < 4 && PinID < 8)
	{
		if(Direction == OUTPUT)
		{
			switch(PortID)
			{
				case DIO_PORTA: SET_BIT(DDRA, PinID); break;
				case DIO_PORTB: SET_BIT(DDRB, PinID); break;
				case DIO_PORTC: SET_BIT(DDRC, PinID); break;
				case DIO_PORTD: SET_BIT(DDRD, PinID); break;
			}
		}
		else if(Direction == INPUT)
		{
			switch(PortID)
			{
				case DIO_PORTA: CLR_BIT(DDRA, PinID); break;
				case DIO_PORTB: CLR_BIT(DDRB, PinID); break;
				case DIO_PORTC: CLR_BIT(DDRC, PinID); break;
				case DIO_PORTD: CLR_BIT(DDRD, PinID); break;
			}
		}
	}
}

/** Output Mode */
void DIO_voidSetpinValue(u8 PortID, u8 PinID, u8 Value)
{
	if(PortID < 4 && PinID < 8)
	{
		if(Value == HIGH)
		{
			switch(PortID)
			{
				case DIO_PORTA: SET_BIT(PORTA, PinID); break;
				case DIO_PORTB: SET_BIT(PORTB, PinID); break;
				case DIO_PORTC: SET_BIT(PORTC, PinID); break;
				case DIO_PORTD: SET_BIT(PORTD, PinID); break;
			}
		}
		else if(Value == LOW)
		{
			switch(PortID)
			{
				case DIO_PORTA: CLR_BIT(PORTA, PinID); break;
				case DIO_PORTB: CLR_BIT(PORTB, PinID); break;
				case DIO_PORTC: CLR_BIT(PORTC, PinID); break;
				case DIO_PORTD: CLR_BIT(PORTD, PinID); break;
			}
		}
	}
}

/** Input Mode */
u8 DIO_u8GetPinValue(u8 PortID, u8 PinID)
{
	u8 Local_u8PinValue = 0;

	if(PortID < 4 && PinID < 8)
	{
		switch(PortID)
		{
			case DIO_PORTA: Local_u8PinValue = GET_BIT(PINA, PinID); break;
			case DIO_PORTB: Local_u8PinValue = GET_BIT(PINB, PinID); break;
			case DIO_PORTC: Local_u8PinValue = GET_BIT(PINC, PinID); break;
			case DIO_PORTD: Local_u8PinValue = GET_BIT(PIND, PinID); break;
		}
	}

	return Local_u8PinValue;
}

/** Toggle Pin */
void DIO_voidTogglePin(u8 PortID, u8 PinID)
{
	if(PortID < 4 && PinID < 8)
	{
		switch(PortID)
		{
			case DIO_PORTA: TOG_BIT(PORTA, PinID); break;
			case DIO_PORTB: TOG_BIT(PORTB, PinID); break;
			case DIO_PORTC: TOG_BIT(PORTC, PinID); break;
			case DIO_PORTD: TOG_BIT(PORTD, PinID); break;
		}
	}
}

/** Set Port Direction */
void DIO_voidSetPortDirection(u8 PortID, u8 Direction)
{
	if(PortID < 4)
	{
		switch(PortID)
		{
			case DIO_PORTA: DDRA = Direction; break;
			case DIO_PORTB: DDRB = Direction; break;
			case DIO_PORTC: DDRC = Direction; break;
			case DIO_PORTD: DDRD = Direction; break;
		}
	}
}

/** Set Port Value */
void DIO_voidSetPortValue(u8 PortID, u8 Value)
{
	if(PortID < 4)
	{
		switch(PortID)
		{
			case DIO_PORTA: PORTA = Value; break;
			case DIO_PORTB: PORTB = Value; break;
			case DIO_PORTC: PORTC = Value; break;
			case DIO_PORTD: PORTD = Value; break;
		}
	}
}



