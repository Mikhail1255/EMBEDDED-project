/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 04/08/2026     ***************/
/********* File  : ADC_prog.c     ***************/
/************************************************/

#include "Std_Types.h"
#include "Bit_Math.h"

#include "ADC_int.h"
#include "ADC_private.h"
#include "ADC_config.h"

/* Global pointer to hold the callback function address */
pf ADC_CallBack = 0;

void ADC_voidInit(void)
{
    /* --- NEW ADDITION: Select AVCC (5V) as the ADC Reference Voltage --- */
    SET_BIT(ADMUX, 6);  /* Set REFS0 */
    CLR_BIT(ADMUX, 7);  /* Clear REFS1 */
    /* ------------------------------------------------------------------- */

    /* Select ADC Channel */
    ADMUX &= 0xE0; /* Clear channel bits */
    ADMUX |= ADC_CHANNEL;

    /* Select Left or Right Adjustment */
    #if REG_ADJ == LEFT_ADJUSTMEN
        SET_BIT(ADMUX, 5);  /* Set ADLAR bit for Left Adjustment */
    #elif REG_ADJ == RIGHT_ADJUSTMEN
        CLR_BIT(ADMUX, 5);  /* Clear ADLAR bit for Right Adjustment */
    #endif

    /* Disable ADC */
    CLR_BIT(ADCSRA, 7);

    /* Disable Start Conversion */
    CLR_BIT(ADCSRA, 6);

    /* Disable Auto Trigger */
    CLR_BIT(ADCSRA, 5);

    /* Clear Interrupt Flag (Write 1 to clear) */
    SET_BIT(ADCSRA, 4);

    /* Disable ADC Interrupt */
    CLR_BIT(ADCSRA, 3);

    /* Select Clock Prescaler (Setting to /64 as a safe default for 8MHz) */
    SET_BIT(ADCSRA, 1);
    SET_BIT(ADCSRA, 2);
}

void ADC_voidADCEnable(void)
{
    SET_BIT(ADCSRA, 7);
}

void ADC_voidADCDisable(void)
{
    CLR_BIT(ADCSRA, 7);
}

u16 ADC_u16Read(void)
{
    u16 Local_u16ReturnValue = 0;

    #if REG_ADJ == LEFT_ADJUSTMEN
        /* Read ADCH (8-bit resolution when left adjusted) */
        Local_u16ReturnValue = ADCH;
    #elif REG_ADJ == RIGHT_ADJUSTMEN
        /* Read ADCL first, then ADCH for 10-bit resolution */
        Local_u16ReturnValue = ADCL;
        Local_u16ReturnValue |= (ADCH << 8);
    #endif

    return Local_u16ReturnValue;
}
/* ------------------------------------------------------------------ */
/* Synchronous function to read any channel dynamically               */
/* ------------------------------------------------------------------ */
u16 ADC_u16GetChannelReading(u8 Copy_u8Channel)
{
    /* 1. Clear the MUX bits in ADMUX without altering ADLAR or Reference bits */
    ADMUX &= 0xE0;

    /* 2. Insert the required channel (e.g., 0 for PA0, 1 for PA1) */
    ADMUX |= Copy_u8Channel;

    /* 3. Start Conversion by setting ADSC bit */
    SET_BIT(ADCSRA, 6);

    /* 4. Polling: Wait until the hardware finishes converting (ADIF becomes 1) */
    while(GET_BIT(ADCSRA, 4) == 0)
    {
        /* Wait here */
    }

    /* 5. Clear the ADIF flag so it is ready for the next reading (write 1 to clear) */
    SET_BIT(ADCSRA, 4);

    /* 6. Call your existing read function to handle Left/Right adjustment */
    return ADC_u16Read();
}
void ADC_voidStartConverstion(void)
{
    SET_BIT(ADCSRA, 6);
}

void ADC_voidAutoTrigger(void)
{
    /* Set Auto Trigger Enable */
    SET_BIT(ADCSRA, 5);

    /* Set the source of Auto Trigger */
    #if TRIGGER_SELECt == FREE_RUNNING
        SFIOR &= 0x1F; /* Clear ADTS bits to select Free Running mode */
    #endif
}

void ADC_voidInterruptEnable(void)
{
    SET_BIT(ADCSRA, 3);
}

void ADC_voidSetCallBack(pf FunctionAddress)
{
    ADC_CallBack = FunctionAddress;
}

/* ADC ISR Vector for ATmega32 */
void __vector_16(void) __attribute__((signal, used));
void __vector_16(void)
{
    if (ADC_CallBack != 0)
    {
        ADC_CallBack();
    }
}
