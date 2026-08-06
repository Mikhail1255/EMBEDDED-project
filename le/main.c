/*
 * main.c
 *
 *  Created on: Jul 27, 2026
 *      Author: LOQ
 */

#define F_CPU 8000000UL

#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "includes/Std_Types.h"
#include "includes/Bit_Math.h"
#include "includes/DIO_int.h"
#include "includes/DIO_config.h"
#include "includes/LCD_config.h"
#include "includes/LCD_int.h"
#include "includes/KEYBAD_int.h"
#include "includes/KEYBAD_config.h"
#include "includes/EXTI_int.h"
#include "includes/EXTI_config.h"
#include "includes/GIE_int.h"
#include "includes/GIE_config.h"
#include "includes/ADC_int.h"
#include "includes/ADC_config.h"
#include "includes/TIM0_int.h"
#include "includes/TIM0_config.h"

#include "project/WASH_int.h"


int main(void)
{
    u8 SelectedMode = 0;
    u8 SelectedSpeed = 0;

    /* 1. Initialize Hardware */
    LCD_voidLCDInit();
    KEY_PADINTI();

    /* 2. System Startup Safety Check */
    WASH_voidCheckDoorsAndArmSafety();

    /* 3. Normal Washing Machine Operation */
    while(1)
    {
        /* Ask the user for their settings */
        WASH_voidGetPreferences(&SelectedMode, &SelectedSpeed);

        /* Run the countdown based on their speed choice */
        WASH_voidRunCycle(SelectedSpeed);
    }

    return 0;
}
