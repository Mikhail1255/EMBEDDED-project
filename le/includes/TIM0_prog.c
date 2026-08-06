/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 05/08/2026     ***************/
/********* File  : TIM0_prog.c    ***************/
/************************************************/
#include "Std_Types.h"
#include "Bit_Math.h"

#include "TIM0_int.h"
#include "TIM0_private.h"
#include "TIM0_config.h"

/* Global pointers to hold the callback function addresses
   Initialized to 0 instead of NULL to prevent undeclared errors */
TIM0_pf FunctionAddress1 = 0;
TIM0_pf FunctionAddress2 = 0;

void TIM0_voidinit(void)
{
    /* Select Initial Mode from Config */
    #if TIM0_MODE == NORMAL_MODE
        CLR_BIT(TCCR0, 3);
        CLR_BIT(TCCR0, 6);
    #elif TIM0_MODE == PWM_PHASE_CORRECT
        CLR_BIT(TCCR0, 3);
        SET_BIT(TCCR0, 6);
    #elif TIM0_MODE == CTC_MODE
        SET_BIT(TCCR0, 3);
        CLR_BIT(TCCR0, 6);
    #elif TIM0_MODE == FAST_PWM
        SET_BIT(TCCR0, 3);
        SET_BIT(TCCR0, 6);
    #endif

    /* Select Prescaler */
    TCCR0 &= 0xF8;
    TCCR0 |= PRESCALLER;

    /* Clear Bit 4-5 (Disconnect OC0 pin operation) */
    CLR_BIT(TCCR0, 4);
    CLR_BIT(TCCR0, 5);

    /* Disable overflow interrupt */
    CLR_BIT(TIMSK, 0);

    /* Disable on Compare match interrupt */
    CLR_BIT(TIMSK, 1);

    /* Clear overflow flag (Write 1 to clear in AVR) */
    SET_BIT(TIFR, 0);

    /* Clear on Compare match flag (Write 1 to clear) */
    SET_BIT(TIFR, 1);

    /* Clear TCNT0 */
    TCNT0 = 0;

    /* Clear OCR */
    OCR0 = 0;
}

/* -------------------------------------------------------- */
/* Dynamic Configuration Functions                          */
/* -------------------------------------------------------- */
void TIM0_voidSetMode(u8 u8Mode)
{
    switch(u8Mode)
    {
        case NORMAL_MODE:
            CLR_BIT(TCCR0, 3);
            CLR_BIT(TCCR0, 6);
            break;

        case PWM_PHASE_CORRECT:
            CLR_BIT(TCCR0, 3);
            SET_BIT(TCCR0, 6);
            break;

        case CTC_MODE:
            SET_BIT(TCCR0, 3);
            CLR_BIT(TCCR0, 6);
            break;

        case FAST_PWM:
            SET_BIT(TCCR0, 3);
            SET_BIT(TCCR0, 6);
            break;
    }
}

void TIM0_voidSetPrescaler(u8 u8Prescaler)
{
    /* 1. Clear the first 3 bits (CS02, CS01, CS00) by masking with 0xF8 */
    TCCR0 &= 0xF8;

    /* 2. Insert the new prescaler value into the register */
    TCCR0 |= u8Prescaler;
}

/********************************************************************/
/* Normal Mode Functions */

void TIM0_voidEnableOVInterrupt(void)
{
    /* to Enable the interrupt of Over flow */
    SET_BIT(TIMSK, 0);
}

void TIM0_voidDisableOVInterrupt(void)
{
    /* to Disable the interrupt of Over flow */
    CLR_BIT(TIMSK, 0);
}

void TIM0_voidSetOVReg(u8 u8OVRegValue)
{
    /* to Set the overflow Register(TCNT0) with specific Value */
    TCNT0 = u8OVRegValue;
}

u8 TIM0_u8ReadOVReg(void)
{
    /* to read the overflow Register(TCNT0) */
    return TCNT0;
}

void TIM0_voidOVSetCallBack(TIM0_pf OVFunctionAddress)
{
    /* to Set the Call Back Function of Overflow */
    FunctionAddress1 = OVFunctionAddress;
}

/* For Overflow ISR */
void __vector_11(void) __attribute__((signal, used));
void __vector_11(void)
{
    /* Check if the pointer is not 0 before calling */
    if (FunctionAddress1 != 0)
    {
        FunctionAddress1();
    }
}

/********************************************************************************/
/* CTC Mode Functions */

void TIM0_voidEnableCTCInterrupt(void)
{
    /* to Enable the interrupt of CTC */
    SET_BIT(TIMSK, 1);
}

void TIM0_voidDisableCTCInterrupt(void)
{
    /* to Disable the interrupt of CTC */
    CLR_BIT(TIMSK, 1);
}

void TIM0_voidSetCTCReg(u8 u8CTCRegValue)
{
    /* to Set the CTC Register(OCR0) with specific Value */
    OCR0 = u8CTCRegValue;
}

u8 TIM0_u8ReadCTCReg(void)
{
    /* to read the CTC Register(OCR0) */
    return OCR0;
}

void TIM0_voidCTCSetCallBack(TIM0_pf CTCFunctionAddress)
{
    /* to Set the Call Back Function of On Compare Match */
    FunctionAddress2 = CTCFunctionAddress;
}

/* for On Compare Match ISR */
void __vector_10(void) __attribute__((signal, used));
void __vector_10(void)
{
    /* Check if the pointer is not 0 before calling */
    if (FunctionAddress2 != 0)
    {
        FunctionAddress2();
    }
}
