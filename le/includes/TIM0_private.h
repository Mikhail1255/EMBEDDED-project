/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 05/08/2026     ***************/
/********* File  : TIM0_config.h  ***************/
/************************************************/


#ifndef TIM0_PRIVATE_H
#define TIM0_PRIVATE_H

/* Define Registers */
#define TCCR0    *((volatile u8 *)0x53)
#define TCNT0    *((volatile u8 *)0x52)
#define OCR0     *((volatile u8 *)0x5C)
#define TIMSK    *((volatile u8 *)0x59)
#define TIFR     *((volatile u8 *)0x58)

/* Mode and Prescaler definitions were moved to TIM0_int.h */

#endif
