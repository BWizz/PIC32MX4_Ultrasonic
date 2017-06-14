
#include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#include <stdio.h>
#include "ping_ultrasonic.h"
#include "cerebot_utils.h"
#include "pic32mx4_timers.h"

// Calibrations found experimentally. 
#define C_M (double) 0.0055 
#define C_B (double) 0.4091
double Count_Value = 0;
int32_t count = 0;
double dt = 0;
#define PBCLK_FREQ (double) 40000000 // Timer Freq in hz
#define C (double) 340.29
#define CF 39.3701

//Sensor Documentation: https://www.parallax.com/sites/default/files/downloads/28015-PING-Sensor-Product-Guide-v2.0.pdf

void Ultrasonic_Init(void){
        TRISB = 0x0000;          // clear register
        PORTB = 0x0000;          // clear register
        Timer4_32bit_Syn_Init();  //Initialize Timer 4
}

void TriggerMeasurement(void){
    TRISBCLR = 1; //configures RB0 as output.
    LATBSET = 1; //Drive Pin RB0.
    Timer4_Delay_ms(0.005); // 5 micro second delay
    LATBCLR = 1; //Turn Off Pin RB0.  
}

double GetDistance(void){
        TRISBSET = 1;    //configure RB0 as input.
        AD1PCFGSET = 1; //configure RB0 as digital pin.
        Reset_Timer4(); // Reset Timer 4
        while (PORTBbits.RB0 == 0) {} // Wait Until Ultrasonic Sensor Pulse Is Generated
        Start_Timer4(); //Start Timer 4
        while (PORTBbits.RB0 == 1){ //Wait until pulse bounces back.
        }
        dt = Read_Timer4() / PBCLK_FREQ ; //Round Trip Ultrasonic Pulse Time
        return dt * C * CF / 2; //Object Distance
}


double MeasureDistance(void){
    Ultrasonic_Init();
    TriggerMeasurement();
    return GetDistance();
}