/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <stdio.h>
#include <stdlib.h>
//#include <proc/p32mx460f512l.h>
#include <sys/attribs.h>

/******************************************************************************/
/* Clock Setup                                                                */
/******************************************************************************/
// Clock Configuration - Taken from the other board's notes
// Oscillator Settings
#pragma config FNOSC        = PRIPLL
#pragma config POSCMOD      = EC
#pragma config FPLLIDIV     = DIV_2
#pragma config FPLLMUL      = MUL_20
#pragma config FPLLODIV     = DIV_1
#pragma config FPBDIV       = DIV_8
#pragma config FSOSCEN      = OFF

//  Clock Control
#pragma config IESO         = OFF
#pragma config FCKSM        = CSDCMD
#pragma config OSCIOFNC     = OFF

// Lee made this one change.


/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
int i;
int32_t count = 0;
int32_t count0 = 0;
double Count_Value = 0;
int32_t Buff[300];
// Calibrations found experimentally. 
#define C_M (double) 0.0055 
#define C_B (double) 0.4091

/******************************************************************************/
/* Function Definition                                                        */
/******************************************************************************/
void SimpleCounterDelay(int CountLimit){
    int x;
    for (x = 0; x < CountLimit; x++){
    }  
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int32_t main(void)
{

    TRISB = 0x0000;
    PORTB = 0x0000;
    while (1){
        count = 0;
        TRISBCLR = 1; //configures RB0 as output.
        LATBSET = 1; //Drive Pin RB0.
        SimpleCounterDelay(1000); // Simple Delay.
        LATBCLR = 1; //Turn Off Pin RB0.
        TRISBSET = 1;    //configure RB0 as input.
        AD1PCFGSET = 1; //configure RB0 as digital pin.
        while (PORTBbits.RB0 == 0) {} // Wait Until Ultrasonic Sensor Pulse Is Generated
        while (PORTBbits.RB0 == 1){ //Wait until pulse bounces back.
            count++;  //Counts that pin is held high.
        }
        Count_Value = count * C_M + C_B; //First round calibration. Output Units Inchs.
        //Currently calibration does not consider Ambient impacts to accuracy.
        SimpleCounterDelay(800000); // Delay until next measurement is taken.
    }
}
