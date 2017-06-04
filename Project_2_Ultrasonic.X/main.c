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
/* Global Variable Declaration                                                */
/******************************************************************************/
int i;
/* i.e. uint32_t <variable_name>; */
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void SetUpLEDPort(void){
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;
    PORTBbits.RB10 = 0;
    PORTBbits.RB11 = 0;
    PORTBbits.RB12 = 0;
    PORTBbits.RB13 = 0;
}


void SimpleCounterDelay(int CountLimit){
    int x;
    for (x = 0; x < CountLimit; x++){
    }  
}


void TurnOnLED(int LedNum){
 
    switch(LedNum){
        case 1:
            PORTBSET = 1 << 10;
            break;
        case 2: 
            PORTBSET = 1 << 11;
            break;
        case 3:
            PORTBSET = 1 << 12;
            break;
        case 4:
            PORTBSET = 1 << 13;   
            break;
    }            
}

void TurnOffLED(int LedNum){
    switch(LedNum){
        case 1:
            PORTBCLR = 1 << 10;
            break;
        case 2: 
            PORTBCLR = 1 << 11;
            break;
        case 3:
            PORTBCLR = 1 << 12;
            break;
        case 4:
            PORTBCLR = 1 << 13;  
            break;
    }            
}
int32_t count = 0;
int32_t Count_Value = 0;
int32_t Buff[300];
int32_t main(void)
{
//    PMCON = 0x0000; //Stop and clear the PMP module.
//    PMMODE = WAITE & (WAITM << 2) & (WAITB << 6) & (MODE << 8) & (MODE16 << 10) & (INCM << 11) & (IRQM << 13); //Setup PMMODE register
//    PMCONSET = ON; // Turn on the PMP Module.
    TRISB = 0x0000;
    PORTB = 0x0000;
    while (1){
        TRISBCLR = 1; //configures RB0 as output.
        LATBSET = 1; //Drive Pin RB0.
        SimpleCounterDelay(100000); // Simple Delay.
        TRISBSET = 1;    //configure RB0 as input.
        AD1PCFGSET = 1; //configure RB0 as digital pin.
        while (PORTB & 0x00000000) {}
        while (PORTB & 1){
            count++;
        }
        Count_Value = count;
        count = 0;
        Count_Value = 0;
        SimpleCounterDelay(100000);
    }
}
