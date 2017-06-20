/*
 * Developer: Brian Wisniewski
 * Date: 7/05/16
 * Revision: 2
 * 
 * PURPOSE:
 * pic32mx4_timers.c contains 16bit & 32bit internal timer configurations and 
 * necessary functions for the PIC32MX4 microprocessor. 
 * 
 * RESOURCES:
 *  STARTERKIT: http://store.digilentinc.com/cerebot-32mx4-limited-time-see-chipkit-pro-mx4/ 
 *  PROCESSOR (PIC32MX460F512L): http://www.microchip.com/wwwproducts/en/PIC32MX460F512L
 *  COMPILER (XC32): http://ww1.microchip.com/downloads/en/DeviceDoc/50001686J.pdf 
 */

/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#include <xc.h>
#include <stdio.h>
#include "pic32mx4_timers.h"
/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

///////////////////////////////////////////////////////////////////////////////
/*
 *                         Timer 1 16bit Functions
 */
///////////////////////////////////////////////////////////////////////////////
void Timer1_16bit_Syn_Init(){
/* FUNCTION: Timer1_16bit_Syn_Init
 * PURPOSE: Timer 1 Configuration for 16-bit Synchronous Clock Counter Mode.
 * Timer frequency  = 40Mhz.
 * Max Timer Value ~ 0xFFFF (@40Mhz = 1.6384 ms) 
 */ 
    T1CON = 0x0; //disable and clear the Timer 1 control register.
    T1CONbits.TCS = 0;      // Internal peripheral clock
    T1CONbits.TSYNC = 0;    // This bit is ignored when TCS = 0.
    T1CONbits.TCKPS = 0b00; // Prescale 1:1
    T1CONbits.TGATE = 0;    // Gated time accumulation is disabled.
    T1CONbits.TWIP = 0;     // Only used in external clock mode.
    T1CONbits.TWDIS = 1;    // Writes to TMR1 are ignored until pending write operation completes
    T1CONbits.SIDL = 0;     // Continue operation when device enters Idle mode  
    TMR1 = 0x0;             // Clear the timer register.
// Load the period register. Timer TMR1 will reset once TMR1 = PR1.
    PR1 = 0xFFFF;           // Load the period register.
}

void Start_Timer1(void){
/* FUNCTION: Start_Timer1
 * PURPOSE: Enable timer 1 to begin counting.
 */ 
    T1CONbits.ON = 1;  // Enable Timer 1
}

void Reset_Timer1(void){
/* FUNCTION: Reset_Timer1
 * PURPOSE: Disable timer 1 and clear counter value.
 */ 
    T1CONbits.ON = 0;  // Disable timer 1
    TMR1 = 0x0;        // Clear timer 1 value
}

uint32_t Read_Timer1(void){
/* FUNCTION: Read_Timer1
 * PURPOSE: Return timer 1 counter value.
 * 
 * OUTPUTS:
 *      - Returns the value of timer 1, TMR1 [uint 32]
 */ 
    return TMR1;       // Return timer 1 value
}
///////////////////////////////////////////////////////////////////////////////
/*
 *                         Timer 4/5 32bit Functions
 */
///////////////////////////////////////////////////////////////////////////////
void Timer4_32bit_Syn_Init(){
 /* FUNCTION: Timer4_32bit_Syn_Init
 * PURPOSE: Timer 4/5 Configuration for 32-bit Synchronous Clock Counter Mode.
 * Timer frequency  = 40Mhz.
 * Max Timer Value = 0xFFFFFFFF (@40Mhz ~ 107 seconds)
 */  
    T4CON = 0x0; //disable and clear the Timer 4 control register.
    T5CON = 0x0; //disable and clear the Timer 5 control register.
    T4CONbits.T32 = 1; // 32bit Mode.
    T4CONbits.TCS = 0; // Internal Clock Mode.
    T4CONbits.TCKPS=0b000; // Set to PBLCK 1:1 with SYSCLK
    TMR4 = 0x00000000;          // Clear the timer register.
// Load the period register. Timer TMR4 will reset once TMR4 = PR4.
    PR4 = 0xFFFFFFFF;           
}

void Start_Timer4(void){
/* FUNCTION: Start_Timer4
 * PURPOSE: Enable timer 4 to begin counting.
 */ 
    T4CONbits.ON = 1;  // Enable Timer 4
}

void Reset_Timer4(void){
/* FUNCTION: Reset_Timer1
 * PURPOSE: Disable timer 4 and clear counter value.
 */ 
    T4CONbits.ON = 0;  // Disable timer 4
    TMR4 = 0x0;        // Clear timer 4 value
}

uint32_t Read_Timer4(void){
 /* FUNCTION: Read_Timer4
 * PURPOSE: Return timer 4/5 counter value.
 * 
 * OUTPUTS:
 *      - Returns the value of timer 4, TMR4 [uint 32]
 */ 
    return TMR4;       // Return timer 4 value
}

void Timer4_Delay_ms(uint32_t DelayTime_ms){
 /* FUNCTION: Timer4_Delay_ms
 * PURPOSE: Software delay function. The function will run until the user 
 * specified time has elapased.
 * 
 * INPUTS: 
 *      - DelayTime_ms [unint32] (Max: 100,000 ms): Delay time in milliseconds.
 * 
 * LOCALS: 
 *     - Stop_Counts [int]: Delay counts required to break the while loop and
 *       exit and return to main.
 */
    
    Timer4_32bit_Syn_Init(); //Init Timer 4
 
    /* Max timer value is 0xFFFFFFFF (@40Mhz ~ 107 seconds) before the timer
     * resets. This check ensures the user does not enter a value greater then
     * what the timer can reach.
     */
    if (DelayTime_ms > 100000){
        DelayTime_ms = 100000;
    }
     
    
    // Converstion between delay time in ms to timer counts.
    //uint32_t Stop_Counts = DelayTime_ms * 40000000 / 1000;
    // Start timer 4 and wait until Stop_Counts is reached.
    int Count_Limit;
    Count_Limit = (DelayTime_ms * 40000);
    
    Reset_Timer4();
    Start_Timer4();          //Start Timer 4
    while (TMR4 <= Count_Limit ){
    }
    T4CONbits.ON = 0;
    int x = 2;
    Reset_Timer4();
}