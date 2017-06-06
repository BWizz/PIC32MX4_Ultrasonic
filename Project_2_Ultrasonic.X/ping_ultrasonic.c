
#include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#include <stdio.h>
#include "ping_ultrasonic.h"
#include "cerebot_utils.h"

// Calibrations found experimentally. 
#define C_M (double) 0.0055 
#define C_B (double) 0.4091
double Count_Value = 0;
int32_t count = 0;

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
        //Currently calibration does not consider Ambient impacts to accuracy.
}

double MeasureDistance(void){
    count = 0;
    TriggerMeasurement();
    return GetDistance();
    SimpleCounterDelay(800000); // Delay until next measurement is taken.
}

