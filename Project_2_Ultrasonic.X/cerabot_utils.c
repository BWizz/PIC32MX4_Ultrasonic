#include "cerebot_utils.h"
#include <xc.h>


void SimpleCounterDelay(int CountLimit){
/* FUNCTION: SimpleCounterDelay
 * PURPOSE: Software delay function. The function will run until the user 
 * specified number of counts is met, x > CountLimit.
 * 
 * INPUTS: 
 *      - CountLimit [int]: Number of counts required to reach before function 
 *        is returned
 * LOCALS: 
 *     - x [int]: Number of counts of for loop.
 */    
    int x;
    for (x = 0; x < CountLimit; x++){
    }  
}