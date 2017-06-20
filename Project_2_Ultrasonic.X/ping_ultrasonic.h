/*
 * Developer: Brian Wisniewski
 * Date: 7/05/16
 * Revision: 5
 * 
 * PURPOSE:
 * Ping_Ultrasonic.c contains the necessary device drivers for the Parallax PING 
 * Ultrasonic sensor for the cerebot PIC32MX4 developer kit. Current implementation
 * requires sensor signal pin to be wired to PORTB RB0. 
 * 
 * RESOURCES:
 *  STARTERKIT: http://store.digilentinc.com/cerebot-32mx4-limited-time-see-chipkit-pro-mx4/ 
 *  PROCESSOR (PIC32MX460F512L): http://www.microchip.com/wwwproducts/en/PIC32MX460F512L
 *  COMPILER (XC32): http://ww1.microchip.com/downloads/en/DeviceDoc/50001686J.pdf 
 *  SENSOR: https://www.parallax.com/sites/default/files/downloads/28015-PING-Sensor-Product-Guide-v2.0.pdf
 */

#ifndef PING_ULTRASONIC_H
#define	PING_ULTRASONIC_H

#define PBCLK_FREQ (double) 40000000 // Timer Freq in hz
#define C (double) 340.29 // Speed of sound m/s
#define CF (double) 39.3701 // Conversion factor from meters to inches.

typedef enum {OKAY, STUCK_HI, STUCK_LO, OOR} status_t;
typedef struct {
    status_t status;    // Sensor Status
    double in;          // Object distance inches.
    double ft;          // Object distance feet.
    double m;           // Object distance meters.
    double cm;          // Object distance in cm
} ultrasonic_t;

ultrasonic_t Dist;
ultrasonic_t *Ultra_Dist = &Dist;  // Ultrasonic Sensor Global Variable Pointer.



void Ultrasonic_Init(void);
void TriggerMeasurement(void);
double GetDistance(void);
double MeasureDistance(ultrasonic_t*);

#endif	/* PING_ULTRASONIC_H */

