/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 04/08/2026     ***************/
/********* File  : ADC_int.h      ***************/
/************************************************/

#ifndef ADC_INT_H
#define ADC_INT_H

/* Adjustment Options */
#define LEFT_ADJUSTMEN   1
#define RIGHT_ADJUSTMEN  2

/* Auto Trigger Source Options */
#define FREE_RUNNING     0

/* Channel Options */
#define ADC0             0
#define ADC1             1
#define ADC2             2
#define ADC3             3
#define ADC4             4
#define ADC5             5
#define ADC6             6
#define ADC7             7

/* Pointer to Function Type for the Callback */
typedef void (*pf)(void);

/* Function Prototypes */
void ADC_voidInit(void);
void ADC_voidADCEnable(void);
void ADC_voidADCDisable(void);
u16  ADC_u16Read(void);
void ADC_voidStartConverstion(void);
void ADC_voidAutoTrigger(void);
void ADC_voidInterruptEnable(void);
void ADC_voidSetCallBack(pf FunctionAddress);
u16 ADC_u16GetChannelReading(u8 Copy_u8Channel);

#endif
