/* 
 * File:   pic32mx4_init.h
 * Author: Brian
 *
 * Created on June 5, 2017, 10:27 PM
 */
#include <xc.h> 
 /******************************************************************************/
/* Clock Setup From Lee                                                        */
/******************************************************************************/
// Clock Configuration - Taken from the other board's notes
// Oscillator Settings
#pragma config FNOSC        = PRIPLL
#pragma config POSCMOD      = EC
#pragma config FPLLIDIV     = DIV_2
#pragma config FPLLMUL      = MUL_20
#pragma config FPLLODIV     = DIV_2
// Program time configuration for PBCLK. PBCLK is divided from SYSCLK
// by the defined prescaler. DIV_2 = PBCLK 1:2 with SYSCLK. [40Mhz]
#pragma config FPBDIV       = DIV_1

#pragma config FSOSCEN      = OFF

//  Clock Control
#pragma config IESO         = OFF
#pragma config FCKSM        = CSDCMD
#pragma config OSCIOFNC     = OFF
// Lee made this one change.

// /******************************************************************************/
///* Clock Setup From Microchip                                                  */
///* http://microchipdeveloper.com/32bit:mz-osc-sysclk                           */
///******************************************************************************/
//// default system clock = FRCDIV
//#pragma config FNOSC = FRCDIV
//// default system clock = SPLL
//#pragma config FNOSC = SPLL
//    
//// run-time config SYSCLK = FRCDIV
//PLIB_OSC_SysClockSelect(OSC_ID_0, OSC_FRC_BY_FRCDIV);
//// run-time config SYSCLK = POSC with SPLL
//PLIB_OSC_SysClockSelect(OSC_ID_0, OSC_PRIMARY_WITH_PLL);
        
        


