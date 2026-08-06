/************************************************/
/********* File  : WASH_int.h     ***************/
/************************************************/

#ifndef WASH_INT_H
#define WASH_INT_H

/* Function Prototypes */
void WASH_voidCheckDoorsAndArmSafety(void);
void WASH_voidGetPreferences(u8 *ModeVariable, u8 *SpeedVariable);
void WASH_voidRunCycle(u8 SelectedSpeed);

#endif
