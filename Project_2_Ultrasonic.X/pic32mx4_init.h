/* 
 * File:   pic32mx4_init.h
 * Author: Brian
 *
 * Created on June 5, 2017, 10:27 PM
 */
#include <xc.h> 
 /******************************************************************************/
 /* Processor Settings From Lee.                                               */
 /******************************************************************************/
// Clock Configuration - Taken from the other board's notes
// Oscillator Settings
#pragma config FNOSC        = PRIPLL // Primary Oscillator with PLL module
#pragma config POSCMOD      = EC     // Primary Oscillator External Clock Mode
#pragma config FSOSCEN      = OFF    // Secondary Oscillator Off


/*BW Added This 
 * Explanation Here: http://ww1.microchip.com/downloads/en/DeviceDoc/Running_PIC32_at_80MHz.pdf
*/
//Oscillator Setup. 80Mhz = 8Mhz Crystal * 20 / 2 / 1
#pragma config FPLLODIV     = DIV_1
#pragma config FPLLIDIV     = DIV_2 
#pragma config FPLLMUL      = MUL_20

// Program time configuration for PBCLK. PBCLK is divided from SYSCLK
// by the defined prescaler. DIV_2 = PBCLK 1:2 with SYSCLK. [40Mhz]
#pragma config FPBDIV       = DIV_2


//  Clock Control
#pragma config IESO         = OFF
#pragma config FCKSM        = CSDCMD
#pragma config OSCIOFNC     = OFF
// Lee made this one change.
        
        


