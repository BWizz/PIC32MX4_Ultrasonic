/* 
 * File:   pic32mx4_timers.h
 * Author: Brian
 *
 * Created on June 7, 2017, 11:29 AM
 */
#ifndef PIC32MX4_TIMERS_H
#define	PIC32MX4_TIMERS_H


void Timer1_16bit_Syn_Init(void);
void Start_Timer1(void);
void Reset_Timer1(void);
uint32_t Read_Timer1(void);


void Timer4_32bit_Syn_Init(void);
void Start_Timer4(void);
void Reset_Timer4(void);
uint32_t Read_Timer4(void);
void Timer4_Delay_ms(uint32_t DelayTime_ms);


#endif	/* PIC32MX4_TIMERS_H */

