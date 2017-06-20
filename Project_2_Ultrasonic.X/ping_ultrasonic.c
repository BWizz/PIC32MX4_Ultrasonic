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

/******************************************************************************/
/* Files to Include                                                          */
/******************************************************************************/
#include <xc.h>
#include <stdio.h>
#include "ping_ultrasonic.h"
#include "cerebot_utils.h"
#include "pic32mx4_timers.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
#define TIMEOUT_HI 40000000
#define TIMEOUT_LO 40000000
double distance;

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/
void Ultrasonic_Init(void){
/* FUNCTION: Ultrasonic_Init
 * PURPOSE: Initialize port B and timer 4.
 */ 
        TRISB = 0x0000;          // clear register
        PORTB = 0x0000;          // clear register
        Timer4_32bit_Syn_Init();  //Initialize Timer 4
}

void TriggerMeasurement(void){
/* FUNCTION: TriggerMeasurement
 * PURPOSE: Configure port RBO to digital output & send a command pulse to 
 * ping ultrasonic sensor to initiate a measurement.
 */ 
    TRISBCLR = 1; //configures RB0 as output.
    LATBSET = 1; //Drive Pin RB0.
    Timer4_Delay_ms(0.005); // 5 microsecond delay
    LATBCLR = 1; //Turn Off Pin RB0.  
}

double GetDistance(void){
/* FUNCTION: GetDisance
 * PURPOSE: Configure port RBO to digital input & monitor the amount of time 
 * sensor pin is held high. Object distance is calculated based on time pin is 
 * held high, the speed of sound, and a conversion factor.
 * 
 * OUTPUT: 
 *      - Return Object Distance in Inches.
 *      - Return sensor sensor status
 * NOTES / TODO's:
 */ 
  
        TRISBSET = 1;    // Configure RB0 as input.
        AD1PCFGSET = 1;  // Configure RB0 as digital pin.
        Reset_Timer4();  // Reset Timer 4.
        Ultra_Dist->status = OKAY;  // Load sensor status as OKAY.
        Start_Timer4();  // Start timer 4.

        // Wait Until Ultrasonic Sensor Pulse Is Generated.
        while (PORTBbits.RB0 == 0) {

            // TIMEOUT DIAGNOSTIC, PORT STUCK LO
            if (TMR4 >= TIMEOUT_LO){
                Ultra_Dist->status = STUCK_LO;
                break;
            }
        }

        Reset_Timer4();  // Reset Timer 4.
        Start_Timer4();  // Start Timer 4
        
        //Wait until ultrasonic pulse bounces back.
        while (PORTBbits.RB0 == 1){
            
            // TIMEOUT DIAGNOSTIC, PORT STUCK HI
            if (TMR4 >= TIMEOUT_HI){
                Ultra_Dist->status = STUCK_HI; // Set sensor status STUCK_Hi
                break;
            }
        }
        
        double dt = 0;   // Create local variable dt.
        
        // Check sensor status for failure. 
        if (Ultra_Dist->status == OKAY){
        // Calculate round trip ultrasonic pulse time.
        dt = Read_Timer4() / PBCLK_FREQ ;
        } 
        // OBJECT DISTANT * 2 = (ROUND TRIP TIME) * (SPEED OF SOUND) * (CF INCHES TO METETS)
        return (dt * C * CF) / 2; // Return object distance in inches.
}


double MeasureDistance(ultrasonic_t *ptr){
/* FUNCTION: MeasureDistance
 * PURPOSE: High Level function call to initiate and return distance using ping
 * ultrasonic sensor.
 * OUTPUT: 
 *      - load input structure with distance data.

 */  
    Ultrasonic_Init();
    TriggerMeasurement();
    distance = GetDistance(); 
    ptr->in = distance;              // Load distance in Inches.
    ptr->ft = distance * 0.0833;     // Load distance in feet.
    ptr->cm = distance * 2.54;       // Load distance in centimeters
    ptr->m  = distance * 0.0254;     // Load distance in meters.
    return distance;                 // TODO: Remove this after initial prototyping and V&V testing. 
}