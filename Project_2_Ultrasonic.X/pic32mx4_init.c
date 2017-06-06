#include "pic32mx4_init.h"

void clock_init(void){
 /******************************************************************************/
/* Clock Setup                                                                */
/******************************************************************************/
// Clock Configuration - Taken from the other board's notes
// Oscillator Settings
#pragma config FNOSC        = PRIPLL
#pragma config POSCMOD      = EC
#pragma config FPLLIDIV     = DIV_2
#pragma config FPLLMUL      = MUL_20
#pragma config FPLLODIV     = DIV_1
#pragma config FPBDIV       = DIV_8
#pragma config FSOSCEN      = OFF

//  Clock Control
#pragma config IESO         = OFF
#pragma config FCKSM        = CSDCMD
#pragma config OSCIOFNC     = OFF
// Lee made this one change.
}
