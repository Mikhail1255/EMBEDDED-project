/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 05/08/2026     ***************/
/********* File  : TIM0_int.h     ***************/
/************************************************/

#ifndef TIM0_INT_H
#define TIM0_INT_H

/* Pointer to Function Type for the Callbacks (Renamed to prevent conflicts) */
typedef void (*TIM0_pf)(void);

/* Mode Constants */
#define NORMAL_MODE          1
#define PWM_PHASE_CORRECT    2
#define CTC_MODE             3
#define FAST_PWM             4

/* Prescaler Constants */
#define NO_CLOCK         0
#define NO_PRESCALER     1
#define DIV_8            2
#define DIV_64           3
#define DIV_256          4
#define DIV_1024         5
#define EXT_FALLING      6
#define EXT_RISING       7

/* Initialization */
void TIM0_voidinit(void);

/* Dynamic Configuration Functions */
void TIM0_voidSetMode(u8 u8Mode);
void TIM0_voidSetPrescaler(u8 u8Prescaler);

/* ---------------- Normal Mode ---------------- */
void TIM0_voidEnableOVInterrupt(void);       /*[cite: 19]*/
void TIM0_voidDisableOVInterrupt(void);      /*[cite: 19]*/
void TIM0_voidSetOVReg(u8 u8OVRegValue);     /*[cite: 19]*/
u8   TIM0_u8ReadOVReg(void);                 /*[cite: 19]*/
void TIM0_voidOVSetCallBack(TIM0_pf OVFunctionAddress); /*[cite: 19]*/

/* ----------------- CTC Mode ------------------ */
void TIM0_voidEnableCTCInterrupt(void);      /*[cite: 19]*/
void TIM0_voidDisableCTCInterrupt(void);     /*[cite: 19]*/
void TIM0_voidSetCTCReg(u8 u8CTCRegValue);   /*[cite: 19]*/
u8   TIM0_u8ReadCTCReg(void);                /*[cite: 19]*/
void TIM0_voidCTCSetCallBack(TIM0_pf CTCFunctionAddress); /*[cite: 19]*/

#endif
