/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 03/08/2026     ***************/
/********* File  : EXTI_private.h ***************/
/************************************************/

#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

/* EXTI Registers */
#define MCUCR    *((volatile u8 *)0x55)
#define MCUCSR   *((volatile u8 *)0x54)
#define GICR     *((volatile u8 *)0x5B)
#define GIFR     *((volatile u8 *)0x5A)

/* Sense Control States */
#define LOW_LEVEL      1
#define ON_CHANGE      2
#define FALLING_EDGE   3
#define RISING_EDGE    4

#endif
