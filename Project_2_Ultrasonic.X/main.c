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
double Distance[256];
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    int i = 0;
    while (1){
     Timer4_Delay_ms(1000); // 1 second delay
     Distance[i] = MeasureDistance();
     int x = 1; // This is only hear for a break point for debugging.
     i = i + 1;
     if (i == 256){
         i = 0;
     }
    }
}
