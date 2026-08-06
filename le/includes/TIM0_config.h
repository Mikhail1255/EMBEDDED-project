
/************************************************/
/********* Author: Mikhail Medhat ***************/
/********* Date  : 05/08/2026     ***************/
/********* File  : TIM0_config.h  ***************/
/************************************************/


#ifndef TIM0_CONFIG_H
#define TIM0_CONFIG_H

/*
 * Prescaler Options:
 * NO_CLOCK, NO_PRESCALER, DIV_8, DIV_64, DIV_256, DIV_1024, EXT_FALLING, EXT_RISING
 */
#define PRESCALLER    DIV_64   /*[cite: 20] */

/*
 * Mode Options:
 * NORMAL_MODE, PWM_PHASE_CORRECT, CTC_MODE, FAST_PWM
 */
#define TIM0_MODE     NORMAL_MODE  /*[cite: 20] */

#endif
