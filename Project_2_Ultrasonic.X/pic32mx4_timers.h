/*
 * Developer: Brian Wisniewski
 * Date: 7/05/16
 * Revision: 2
 * 
 * PURPOSE:
 * pic32mx4_timers.c contains 16bit & 32bit internal timer configurations and 
 * necessary functions for the PIC32MX4 microprocessor. 
 * 
 * RESOURCES:
 *  STARTERKIT: http://store.digilentinc.com/cerebot-32mx4-limited-time-see-chipkit-pro-mx4/ 
 *  PROCESSOR (PIC32MX460F512L): http://www.microchip.com/wwwproducts/en/PIC32MX460F512L
 *  COMPILER (XC32): http://ww1.microchip.com/downloads/en/DeviceDoc/50001686J.pdf 
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

