/************************************************/
/********* File  : WASH_prog.c    ***************/
/************************************************/

#include "D:\C_PROJECTS\embedead_projects\le\includes\Std_Types.h"
#include "D:\C_PROJECTS\embedead_projects\le\includes\Bit_Math.h"
#include <util/delay.h>

/* Include the hardware drivers the washing machine needs */
#include "D:\C_PROJECTS\embedead_projects\le\includes\DIO_int.h"
//#include "includes/DIO_config.h"
//#include "includes/LCD_config.h"
#include "D:\C_PROJECTS\embedead_projects\le\includes\LCD_int.h"
#include "D:\C_PROJECTS\embedead_projects\le\includes\KEYBAD_int.h"
//#include "includes/KEYBAD_config.h"

#include "WASH_int.h"

void WASH_voidGetPreferences(u8 *ModeVariable, u8 *SpeedVariable)
{
    u8 key_pressed = 0;

    /* 1. Initial Prompt */
    LCD_voidSendCommand(0x01); /* Clear LCD */
    LCD_voidWriteString(" Please select");
    LCD_GotoXY(0, 1);
    LCD_voidWriteString("  Washing mode...");

    _delay_ms(2000);

    /* 2. Display Mode Options */
    LCD_voidSendCommand(0x01); /* Clear LCD */
    LCD_voidWriteString(" 1-White 2-Color");
    LCD_GotoXY(0, 1);
    LCD_voidWriteString("    3-Drying");

    /* Loop until the user presses 1, 2, or 3 */
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

    /* 3. Display Speed Options */
    LCD_voidSendCommand(0x01); /* Clear LCD */
    LCD_voidWriteString(" 1-Fast (1 hour)");
    LCD_GotoXY(0, 1);
    LCD_voidWriteString(" 2-Normal(2 hrs)");

    /* Loop until the user presses 1 or 2 */
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
}

void WASH_voidRunCycle(u8 SelectedSpeed)
{
    u8 hours = SelectedSpeed;
    u8 minutes = 0;
    u8 seconds = 0;
    u8 anim_frame = 0;

    LCD_voidSendCommand(0x01); /* Clear LCD */

    while(hours > 0 || minutes > 0 || seconds > 0)
    {
        LCD_GotoXY(0, 0);

        if(anim_frame == 0)      LCD_voidWriteString(" Washing .   ");
        else if(anim_frame == 1) LCD_voidWriteString(" Washing ..  ");
        else if(anim_frame == 2) LCD_voidWriteString(" Washing ... ");
        else if(anim_frame == 3) LCD_voidWriteString(" Washing ....");

        anim_frame++;
        if(anim_frame > 5) anim_frame = 0;

        LCD_GotoXY(4, 1);

        LCD_voidWriteNumber(hours);
        LCD_voidSendData(':');

        if(minutes < 10) LCD_voidSendData('0');
        LCD_voidWriteNumber(minutes);
        LCD_voidSendData(':');

        if(seconds < 10) LCD_voidSendData('0');
        LCD_voidWriteNumber(seconds);

        _delay_ms(1000);

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

    LCD_voidSendCommand(0x01);
    LCD_GotoXY(1, 0);
    LCD_voidWriteString("WASHING DONE!");
    _delay_ms(3000);
}
