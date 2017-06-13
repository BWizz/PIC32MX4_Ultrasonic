#include "cerebot_utils.h"
#include <xc.h>


void SimpleCounterDelay(int CountLimit){
    int x = 0;
    for (x = 0; x < CountLimit; x++){
    }  
}

void Timer1_Setup(){
    
    T1CONbits.ON = 1;
}

void Timer1(void){
    
    
}
