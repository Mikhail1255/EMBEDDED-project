/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 03/08/2026     ***************/
/********* File  : EXTI_int.h     ***************/
/************************************************/

#ifndef EXTI_INT_H
#define EXTI_INT_H

/* External Interrupt IDs */
#define EXTI_INT0   0
#define EXTI_INT1   1
#define EXTI_INT2   2

/* Sense Control States (Moved here so main.c can use them) */
#define LOW_LEVEL        1
#define ON_CHANGE        2
#define FALLING_EDGE     3
#define RISING_EDGE      4

/* Function Prototypes */
void EXTI_voidInit(void);
void EXTI_voidEnable(u8 Int_ID);
void EXTI_voidDisable(u8 Int_ID);

/* NEW: Dynamic Sense Control Function */
void EXTI_voidSetSenseControl(u8 Int_ID, u8 Sense_Control);

#endif
