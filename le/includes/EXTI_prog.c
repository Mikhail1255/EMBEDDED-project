/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 03/08/2026     ***************/
/********* File  : EXTI_prog.c    ***************/
/************************************************/

#include "Std_Types.h"
#include "Bit_Math.h"

#include "EXTI_int.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

void EXTI_voidInit(void)
{
    /* ---------- INT0 Configuration ---------- */
    if (EXTI_INT0_SENSE == LOW_LEVEL)
    {
        CLR_BIT(MCUCR, 0);
        CLR_BIT(MCUCR, 1);
    }
    else if (EXTI_INT0_SENSE == ON_CHANGE)
    {
        SET_BIT(MCUCR, 0);
        CLR_BIT(MCUCR, 1);
    }
    else if (EXTI_INT0_SENSE == FALLING_EDGE)
    {
        CLR_BIT(MCUCR, 0);
        SET_BIT(MCUCR, 1);
    }
    else if (EXTI_INT0_SENSE == RISING_EDGE)
    {
        SET_BIT(MCUCR, 0);
        SET_BIT(MCUCR, 1);
    }

    /* ---------- INT1 Configuration ---------- */
    if (EXTI_INT1_SENSE == LOW_LEVEL)
    {
        CLR_BIT(MCUCR, 2);
        CLR_BIT(MCUCR, 3);
    }
    else if (EXTI_INT1_SENSE == ON_CHANGE)
    {
        SET_BIT(MCUCR, 2);
        CLR_BIT(MCUCR, 3);
    }
    else if (EXTI_INT1_SENSE == FALLING_EDGE)
    {
        CLR_BIT(MCUCR, 2);
        SET_BIT(MCUCR, 3);
    }
    else if (EXTI_INT1_SENSE == RISING_EDGE)
    {
        SET_BIT(MCUCR, 2);
        SET_BIT(MCUCR, 3);
    }

    /* ---------- INT2 Configuration ---------- */
    if (EXTI_INT2_SENSE == FALLING_EDGE)
    {
        CLR_BIT(MCUCSR, 6);
    }
    else if (EXTI_INT2_SENSE == RISING_EDGE)
    {
        SET_BIT(MCUCSR, 6);
    }
}
void EXTI_voidSetSenseControl(u8 Int_ID, u8 Sense_Control)
{
    switch(Int_ID)
    {
        case EXTI_INT0:
            switch(Sense_Control)
            {
                case LOW_LEVEL:    CLR_BIT(MCUCR, 0); CLR_BIT(MCUCR, 1); break;
                case ON_CHANGE:    SET_BIT(MCUCR, 0); CLR_BIT(MCUCR, 1); break;
                case FALLING_EDGE: CLR_BIT(MCUCR, 0); SET_BIT(MCUCR, 1); break;
                case RISING_EDGE:  SET_BIT(MCUCR, 0); SET_BIT(MCUCR, 1); break;
            }
            break;

        case EXTI_INT1:
            switch(Sense_Control)
            {
                case LOW_LEVEL:    CLR_BIT(MCUCR, 2); CLR_BIT(MCUCR, 3); break;
                case ON_CHANGE:    SET_BIT(MCUCR, 2); CLR_BIT(MCUCR, 3); break;
                case FALLING_EDGE: CLR_BIT(MCUCR, 2); SET_BIT(MCUCR, 3); break;
                case RISING_EDGE:  SET_BIT(MCUCR, 2); SET_BIT(MCUCR, 3); break;
            }
            break;

        case EXTI_INT2:
            /* Note: INT2 on ATmega32 only supports Edge triggers, not Levels */
            switch(Sense_Control)
            {
                case FALLING_EDGE: CLR_BIT(MCUCSR, 6); break;
                case RISING_EDGE:  SET_BIT(MCUCSR, 6); break;
            }
            break;
    }
}

void EXTI_voidEnable(u8 Int_ID)
{
    switch(Int_ID)
    {
        case EXTI_INT0: SET_BIT(GICR, 6); break;
        case EXTI_INT1: SET_BIT(GICR, 7); break;
        case EXTI_INT2: SET_BIT(GICR, 5); break;
    }
}

void EXTI_voidDisable(u8 Int_ID)
{
    switch(Int_ID)
    {
        case EXTI_INT0: CLR_BIT(GICR, 6); break;
        case EXTI_INT1: CLR_BIT(GICR, 7); break;
        case EXTI_INT2: CLR_BIT(GICR, 5); break;
    }
}
