//#include <pic18f87k22.h>

#include "clock.h"

int start_timers()
{
    INTCONbits.TMR0IE = 1;
    //PIE1bits.TMR1IE = 1;
    return 0;
}

timestamp_t get_time(void)
{
    return timestamp;
}

int stop_timers()
{
    INTCONbits.TMR0IE = 0;
    PIE1bits.TMR1IE = 1;
    return 0;
}

int register_timer(timestamp_t delay , timestamp_t period , FUNCTION_PTR function)
{
    int timer_id = ADD_NODE( delay ,  period ,  function);
    if (timer_id != -1) return timer_id;
    else return -1;
}

int remove_timer(int id){
    int check = REMOVE_NODE(id);
    if (check == 1) return 1; //succes
    else return 0; //fail
}

void timer_ISR()
{
    if (no_q<NUM_Q && no_funcs != 0)UPDATE_TIMER();
}