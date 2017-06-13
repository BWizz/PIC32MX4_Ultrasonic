/* 
 * File:   ping_ultrasonic.h
 * Author: Brian
 *
 * Created on June 5, 2017, 11:26 PM
 */

#ifndef PING_ULTRASONIC_H
#define	PING_ULTRASONIC_H

void Ultrasonic_Init(void);
void TriggerMeasurement(void);
double GetDistance(void);
double GetDistance_v2(void);
double MeasureDistance(void);
double MeasureDistance_v2(void);

#endif	/* PING_ULTRASONIC_H */

