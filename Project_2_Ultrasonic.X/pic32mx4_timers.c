#include <xc.h>
#include <stdio.h>
#include "pic32mx4_timers.h"
///////////////////////////////////////////////////////////////////////////////
/*
 *                         Timer 1 16bit Functions
 */
///////////////////////////////////////////////////////////////////////////////
void Timer1_16bit_Syn_Init(){
    // Timer 1 Configuration for 16-bit Synchronous Clock Counter Mode
    /* Note
       When using 1:1 PBCLK divisor, the user?s software should 
       not read/write the peripheral SFRs in the SYSCLK cycle immediately 
       following the instruction that clears the module?s ON bit */
    
    //Internal Timer is incremented based on Internal Peripheral Bus Clock. 
    
    //this register is causing an error when I try to use it. Not sure why.
    //The PB clock should run as fast as the SYSCLK with this setting
    //DEVCFG1bits.FPBDIV = 0b00; //PBCLK is SYSCLK divided by 1
    
    
    T1CON = 0x0; //disable and clear the Timer 1 control register.
    T1CONbits.TCS = 0;      // Internal peripheral clock
    T1CONbits.TSYNC = 0;    // This bit is ignored when TCS = 0.
    T1CONbits.TCKPS = 0b00; // Prescale 1:1
    T1CONbits.TGATE = 0;    // Gated time accumulation is disabled.
    T1CONbits.TWIP = 0;     // Only used in external clock mode.
    T1CONbits.TWDIS = 1;    // Writes to TMR1 are ignored until pending write operation completes
    T1CONbits.SIDL = 0;     // Continue operation when device enters Idle mode  
    TMR1 = 0x0;             // Clear the timer register.
    PR1 = 0xFFFF;           // Load the period register.
}

void Start_Timer1(void){
    T1CONbits.ON = 1;  // Enable Timer 1
}

void Reset_Timer1(void){
    T1CONbits.ON = 0;  // Disable timer 1
    TMR1 = 0x0;        // Clear timer 1 value
}

uint32_t Read_Timer1(void){
    return TMR1;       // Return timer 1 value
}
///////////////////////////////////////////////////////////////////////////////
/*
 *                         Timer 4/5 32bit Functions
 */
///////////////////////////////////////////////////////////////////////////////
void Timer4_32bit_Syn_Init(){
    // Timer 4/5 Configuration for 32-bit Synchronous Clock Counter Mode
      
    T4CON = 0x0; //disable and clear the Timer 4 control register.
    T5CON = 0x0; //disable and clear the Timer 5 control register.
    T4CONbits.T32 = 1; // 32bit Mode.
    T4CONbits.TCS = 0; // Internal Clock Mode.
    T4CONbits.TCKPS=0b000; // Set to PBLCK 1:1 with SYSCLK
    TMR4 = 0x00000000;          // Clear the timer register.
    PR4 = 0xFFFFFFFF;           // Load the period register.
}

void Start_Timer4(void){
    T4CONbits.ON = 1;  // Enable Timer 4
}

void Reset_Timer4(void){
    T4CONbits.ON = 0;  // Disable timer 4
    TMR4 = 0x0;        // Clear timer 4 value
    TMR5 = 0x0;        // Clear timer 5 value
}

uint32_t Read_Timer4(void){
    return TMR4;       // Return timer 4 value
}

void Timer4_Delay_ms(uint32_t DelayTime_ms){
    Timer4_32bit_Syn_Init(); //Init Timer 4
    Start_Timer4();          //Start Timer 4
 
    //Error Detection 
    if (DelayTime_ms > 107374){
        DelayTime_ms = 107374;
    }
    
    uint32_t Stop_Counts = DelayTime_ms * 40000000 / 1000;
    while (Read_Timer4() <= Stop_Counts){}  
}