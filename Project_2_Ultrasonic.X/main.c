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
double Distance;
double Distance_v2;
#define CONV_FAC (1/(8000000) * 340.29) / 39.3701

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    Ultrasonic_Init();
    Timer4_32bit_Syn_Init();
    while (1){
     Distance = MeasureDistance();
     SimpleCounterDelay(1000000);
     Distance_v2 = MeasureDistance_v2();
     int x = 1; // This is only hear for a break point for debugging.
    }
}
