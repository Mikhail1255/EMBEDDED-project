/************************************************/
/********* Author: Mikhail Medhat *****************/
/********* Date  : 29/07/2026   *****************/
/********* File  : Interface File ***************/
/************************************************/

#ifndef DIO_INT_H
#define DIO_INT_H

/* Port Defines */
#define DIO_PORTA    0
#define DIO_PORTB    1
#define DIO_PORTC    2
#define DIO_PORTD    3

/* Pin Defines */
#define DIO_PIN0     0
#define DIO_PIN1     1
#define DIO_PIN2     2
#define DIO_PIN3     3
#define DIO_PIN4     4
#define DIO_PIN5     5
#define DIO_PIN6     6
#define DIO_PIN7     7

/* Direction Defines */
#define OUTPUT       1
#define INPUT        0

/* Value Defines */
#define LOW          0
#define HIGH         1

/* Function Prototypes */
void DIO_voidInitialization(void);
void DIO_voidSetPinDirection(u8 PortID, u8 PinID, u8 Direction);
void DIO_voidSetpinValue(u8 PortID, u8 PinID, u8 Value);
u8   DIO_u8GetPinValue(u8 PortID, u8 PinID);
void DIO_voidTogglePin(u8 PortID, u8 PinID);
void DIO_voidSetPortDirection(u8 PortID, u8 Direction);
void DIO_voidSetPortValue(u8 PortID, u8 Value);

#endif


