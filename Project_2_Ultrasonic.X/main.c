/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include "ping_ultrasonic.h"
#include "pic32mx4_init.h"

void clock_init(void);
/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
double Distance;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int32_t main(void)
{
    Ultrasonic_Init();
    while (1){
        Distance = MeasureDistance();
        int x = 1; // This is only hear for a break point for debugging.
    }
}
