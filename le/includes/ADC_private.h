/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 04/08/2026     ***************/
/********* File  : ADC_private.h  ***************/
/************************************************/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/* ADC Registers */
#define ADMUX    *((volatile u8 *)0x27)
#define ADCSRA   *((volatile u8 *)0x26)
#define ADCH     *((volatile u8 *)0x25)
#define ADCL     *((volatile u8 *)0x24)
#define SFIOR    *((volatile u8 *)0x50)

#endif
