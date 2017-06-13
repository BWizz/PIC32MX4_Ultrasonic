
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
#define TIMER_FREQ (double) 40000000 // Timer Freq in hz
#define C (double) 340.29
#define CF 39.3701

void Ultrasonic_Init(void){
        TRISB = 0x0000;
        PORTB = 0x0000;
}

void TriggerMeasurement(void){
    TRISBCLR = 1; //configures RB0 as output.
    LATBSET = 1; //Drive Pin RB0.
    SimpleCounterDelay(1000); // Simple Delay.
    LATBCLR = 1; //Turn Off Pin RB0.  
}

double GetDistance(void){
        TRISBSET = 1;    //configure RB0 as input.
        AD1PCFGSET = 1; //configure RB0 as digital pin.
        while (PORTBbits.RB0 == 0) {} // Wait Until Ultrasonic Sensor Pulse Is Generated
        while (PORTBbits.RB0 == 1){ //Wait until pulse bounces back.
            count++;  //Counts that pin is held high.
        }
        Count_Value = count * C_M + C_B; //First round calibration. Output Units Inchs.
        return Count_Value;
        //Currently calibration does not consider Ambient impacts to accuracy.
}

double GetDistance_v2(void){
        TRISBSET = 1;    //configure RB0 as input.
        AD1PCFGSET = 1; //configure RB0 as digital pin.
        Reset_Timer4(); // Reset Timer 4
        while (PORTBbits.RB0 == 0) {} // Wait Until Ultrasonic Sensor Pulse Is Generated
        Start_Timer4(); //Start Timer 4
        while (PORTBbits.RB0 == 1){ //Wait until pulse bounces back.
        }
        dt = Read_Timer4() / TIMER_FREQ ; //Round Trip Ultrasonic Pulse Time
        return dt * C * CF / 2; //Object Distance
        //Currently calibration does not consider Ambient impacts to accuracy.
}

double MeasureDistance(void){
    count = 0;
    TriggerMeasurement();
    return GetDistance();
    SimpleCounterDelay(800000); // Delay until next measurement is taken.
}

double MeasureDistance_v2(void){
    count = 0;
    TriggerMeasurement();
    return GetDistance_v2();
    SimpleCounterDelay(800000); // Delay until next measurement is taken.
}