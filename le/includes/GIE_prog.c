/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 04/08/2026     ***************/
/********* File  : GIE_prog.c     ***************/
/************************************************/

#include "Std_Types.h"
#include "Bit_Math.h"

#include "GIE_int.h"
#include "GIE_private.h"
#include "GIE_config.h"

void GIE_voidEnable(void)
{
    /* Enable the GLOBAL Interrupt Enable Bit --> SREG */ /*[cite: 17] */
    SET_BIT(SREG, 7);
}

void GIE_voidDisable(void)
{
    /* Disable the GLOBAL Interrupt Enable Bit --> SREG */ /*[cite: 17] */
    CLR_BIT(SREG, 7);
}
