/************************************************/
/********* File  : WASH_prog.c    ***************/
/************************************************/

#include "D:\C_PROJECTS\embedead_projects\le\includes\Std_Types.h"
#include "D:\C_PROJECTS\embedead_projects\le\includes\Bit_Math.h"
#include <util/delay.h>

#include "D:\C_PROJECTS\embedead_projects\le\includes\DIO_int.h"
#include "D:\C_PROJECTS\embedead_projects\le\includes\LCD_int.h"
#include "D:\C_PROJECTS\embedead_projects\le\includes\KEYBAD_int.h"
#include "D:\C_PROJECTS\embedead_projects\le\includes\EXTI_int.h"
#include "D:\C_PROJECTS\embedead_projects\le\includes\TIM0_int.h"

#include "WASH_int.h"

#define MCUCR *((volatile u8 *)0x55)
#define GICR  *((volatile u8 *)0x5B)
#define SREG  *((volatile u8 *)0x5F)
#define TCCR0 *((volatile u8 *)0x53)


volatile u8 WASH_u8ActiveScreen = 0;
volatile u8 current_motor_speed = 0;

/* ------------------------------------------------------------------ */
/* Function to ensure doors are closed and sensors are ready          */
/* ------------------------------------------------------------------ */
void WASH_voidCheckDoorsAndArmSafety(void)
{
    u8 door1_state = 1;
    u8 door2_state = 1;

    u8 water_flow_state = 1;
    u8 soap_weight_state = 1;

    /* --- DOOR HARDWARE SETUP --- */
    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN1, INPUT);
    DIO_voidSetpinValue(DIO_PORTD, DIO_PIN1, HIGH);

    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN2, INPUT);
    DIO_voidSetpinValue(DIO_PORTD, DIO_PIN2, HIGH);

    /* --- SENSOR HARDWARE SETUP --- */
    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, INPUT);
    DIO_voidSetpinValue(DIO_PORTA, DIO_PIN0, HIGH);

    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN1, INPUT);
    DIO_voidSetpinValue(DIO_PORTA, DIO_PIN1, HIGH);


    while(1)
    {

        door1_state = DIO_u8GetPinValue(DIO_PORTD, DIO_PIN2);
        door2_state = DIO_u8GetPinValue(DIO_PORTD, DIO_PIN1);


        water_flow_state = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN0);
        soap_weight_state = DIO_u8GetPinValue(DIO_PORTA, DIO_PIN1);


        if(door1_state == 0 && door2_state == 0 &&
           water_flow_state == 0 && soap_weight_state == 0)
        {
            break;
        }


        LCD_voidSendCommand(0x01);
        if (door1_state == 1 || door2_state == 1)
        {
            LCD_voidWriteString(" SYSTEM HALTED:");
            LCD_GotoXY(0, 1);
            LCD_voidWriteString(" CLOSE DOORS");
        }
        else if (water_flow_state == 1)
        {
            LCD_voidWriteString(" SYSTEM HALTED:");
            LCD_GotoXY(0, 1);
            LCD_voidWriteString(" CHECK WATER");
        }
        else if (soap_weight_state == 1)
        {
            LCD_voidWriteString(" SYSTEM HALTED:");
            LCD_GotoXY(0, 1);
            LCD_voidWriteString(" ADD SOAP");
        }

        _delay_ms(500);
    }

    EXTI_voidSetSenseControl(EXTI_INT0, RISING_EDGE);
    EXTI_voidEnable(EXTI_INT0);
    SET_BIT(SREG, 7);
}

/* ------------------------------------------------------------------ */
/* Function to get user preferences                                   */
/* ------------------------------------------------------------------ */
void WASH_voidGetPreferences(u8 *ModeVariable, u8 *SpeedVariable)
{
    u8 key_pressed = 0;

    LCD_voidSendCommand(0x01);
    LCD_voidWriteString(" Please select");
    LCD_GotoXY(0, 1);
    LCD_voidWriteString("  Washing mode...");
    _delay_ms(2000);

    /* --- SCREEN 1: MODE SELECTION --- */
    WASH_u8ActiveScreen = 1;

    LCD_voidSendCommand(0x01);
    LCD_voidWriteString(" 1-White 2-Color");
    LCD_GotoXY(0, 1);
    LCD_voidWriteString("    3-Drying");

    while(1)
    {
        key_pressed = GET_u8PRESSEDKEY();
        if(key_pressed == '1' || key_pressed == '2' || key_pressed == '3')
        {
            *ModeVariable = key_pressed - '0';
            while(GET_u8PRESSEDKEY() != 0);
            break;
        }
    }

    /* --- SCREEN 2: SPEED SELECTION --- */
    WASH_u8ActiveScreen = 2;

    LCD_voidSendCommand(0x01);
    LCD_voidWriteString(" 1-Fast (1 hour)");
    LCD_GotoXY(0, 1);
    LCD_voidWriteString(" 2-Normal(2 hrs)");

    while(1)
    {
        key_pressed = GET_u8PRESSEDKEY();
        if(key_pressed == '1' || key_pressed == '2')
        {
            *SpeedVariable = key_pressed - '0';
            while(GET_u8PRESSEDKEY() != 0);
            break;
        }
    }

    WASH_u8ActiveScreen = 0;
}

/* ------------------------------------------------------------------ */
/* Function to run the animation and clock                            */
/* ------------------------------------------------------------------ */
void WASH_voidRunCycle(u8 SelectedSpeed)
{
    u8 hours = 1;
    u8 minutes = 0;
    u8 seconds = 0;
    u8 anim_frame = 0;

    /* --- CONFIGURE SPEED & TIME --- */
    if (SelectedSpeed == 1)
    {
        hours = 1;
        current_motor_speed = 255; /* 100% Duty Cycle (Full Speed) */
    }
    else if (SelectedSpeed == 2)
    {
        hours = 2;
        current_motor_speed = 128; /* 50% Duty Cycle (Half Speed) */
    }

    /* --- HARDWARE PWM SETUP --- */
    /* 1. Set PB3 (OC0) to Output */
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN3, OUTPUT);

    /* 2. Initialize Timer0 */
    TIM0_voidinit();

    /* 3. Set to Fast PWM using your exact header macro! */
    TIM0_voidSetMode(FAST_PWM);

    /* 4. Manually connect the physical OC0 pin (COM01 = 1)
          since TIM0_voidinit() clears bits 4 and 5. */
    SET_BIT(TCCR0, 5);

    /* 5. Start the motor at the selected speed */
    TIM0_voidSetCTCReg(current_motor_speed);

    LCD_voidSendCommand(0x01);

    while(hours > 0 || minutes > 0 || seconds > 0)
    {
        /* Render Top Line Animation */
        LCD_GotoXY(0, 0);

        if(anim_frame == 0)      LCD_voidWriteString(" Washing .      ");
        else if(anim_frame == 1) LCD_voidWriteString(" Washing ..     ");
        else if(anim_frame == 2) LCD_voidWriteString(" Washing ...    ");
        else if(anim_frame == 3) LCD_voidWriteString(" Washing ....   ");

        anim_frame++;
        if(anim_frame > 3) anim_frame = 0;

        /* Render Bottom Line Clock */
        LCD_GotoXY(4, 1);

        LCD_voidWriteNumber(hours);
        LCD_voidSendData(':');

        if(minutes < 10) LCD_voidSendData('0');
        LCD_voidWriteNumber(minutes);
        LCD_voidSendData(':');

        if(seconds < 10) LCD_voidSendData('0');
        LCD_voidWriteNumber(seconds);

        LCD_voidWriteString("   ");

        /* Hardware PWM handles the motor independently, so we just delay 1 second */
        _delay_ms(1000);

        /* Clock Math */
        if(seconds == 0)
        {
            if(minutes == 0)
            {
                if(hours > 0)
                {
                    hours--;
                    minutes = 59;
                    seconds = 59;
                }
            }
            else
            {
                minutes--;
                seconds = 59;
            }
        }
        else
        {
            seconds--;
        }
    }

    /* --- CYCLE COMPLETE: STOP THE MOTOR --- */
    TIM0_voidSetCTCReg(0);

    LCD_voidSendCommand(0x01);
    LCD_GotoXY(1, 0);
    LCD_voidWriteString("WASHING DONE!");
    _delay_ms(3000);
}

/* ------------------------------------------------------------------ */
/* Emergency Door Interrupt (INT0)                                    */
/* ------------------------------------------------------------------ */
void __vector_1(void) __attribute__((signal,used));
void __vector_1(void)
{
    /* Instantly halt the hardware PWM using your driver function */
    TIM0_voidSetCTCReg(0);

    LCD_voidSendCommand(0x01);
    LCD_voidWriteString(" PLEASE CLOSE");
    LCD_GotoXY(0, 1);
    LCD_voidWriteString("   THE DOOR");

    while(DIO_u8GetPinValue(DIO_PORTD, DIO_PIN2) == 1 || DIO_u8GetPinValue(DIO_PORTD, DIO_PIN1) == 1)
    {
        /* Block execution here until the user closes the doors */
    }

    LCD_voidSendCommand(0x01);

    /* Redraw menus if halted during preferences, or resume motor if in cycle */
    if(WASH_u8ActiveScreen == 1)
    {
        LCD_voidWriteString(" 1-White 2-Color");
        LCD_GotoXY(0, 1);
        LCD_voidWriteString("    3-Drying");
    }
    else if(WASH_u8ActiveScreen == 2)
    {
        LCD_voidWriteString(" 1-Fast (1 hour)");
        LCD_GotoXY(0, 1);
        LCD_voidWriteString(" 2-Normal(2 hrs)");
    }
    else
    {
        /* Resume the saved motor speed using your driver */
        TIM0_voidSetCTCReg(current_motor_speed);
    }
}
