/* 
 * File:   ping_ultrasonic.h
 * Author: Brian
 *
 * Created on June 5, 2017, 11:26 PM
 */

#ifndef PING_ULTRASONIC_H
#define	PING_ULTRASONIC_H

#define PBCLK_FREQ (double) 40000000 // Timer Freq in hz
#define C (double) 340.29 // Speed of sound m/s
#define CF 39.3701 // Conversion factor from meters to inches.

typedef enum {OKAY, STUCK_HI, STUCK_LO, OOR} status_t;
typedef struct {
    status_t status;    // Sensor Status
    double in;     // Object distance inches.
    double ft;     // Object distance feet.
    double m;      // Object distance meters.
    double cm;     // Object distance in cm
} ultrasonic_t;

ultrasonic_t val;
ultrasonic_t *Ultra_Dist = &val;  // Ultrasonic Sensor Global Variable Pointer.



void Ultrasonic_Init(void);
void TriggerMeasurement(void);
double GetDistance(void);
double MeasureDistance(ultrasonic_t*);

#endif	/* PING_ULTRASONIC_H */

