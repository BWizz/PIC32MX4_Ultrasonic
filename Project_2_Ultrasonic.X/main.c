/*
 * Developer: Brian Wisniewski
 * Date: 7/05/16
 * Revision: 9
 * 
 * PURPOSE:
 * main.c is the main program to run and test PING Ultrasonic senor device driver
 * running on the PIC32MX4 cerebot starterkit.
 * 
 * RESOURCES:
 *  STARTERKIT: http://store.digilentinc.com/cerebot-32mx4-limited-time-see-chipkit-pro-mx4/ 
 *  PROCESSOR (PIC32MX460F512L): http://www.microchip.com/wwwproducts/en/PIC32MX460F512L
 *  COMPILER (XC32): http://ww1.microchip.com/downloads/en/DeviceDoc/50001686J.pdf 
 *  SENSOR: https://www.parallax.com/sites/default/files/downloads/28015-PING-Sensor-Product-Guide-v2.0.pdf
 */
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
