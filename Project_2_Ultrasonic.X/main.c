/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/

#include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#include <stdio.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include "ping_ultrasonic.h"
#include "pic32mx4_init.h"
#include "pic32mx4_timers.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
double test;
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    while (1){
     Timer4_Delay_ms(1000); // 1 second delay
     MeasureDistance(Ultra_Dist); //Measure object distance and update Ultra_Dist struc
     int x = 1; // This is only hear for a break point for debugging.
    }
}
