#include "interrupt.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    if (INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1)
    {
        read_button();
        //read_button1();
        if (time_out_dht>0) time_out_dht--; 
        timer_ISR();
        TMR0_IRS();
    }
//    if (PIR1bits.TMR1IF == 1 && PIE1bits.TMR1IE == 1)
//    {
//        TMR1_IRS();
//    }
}

void read_button()
{
    first_state = second_state;
    second_state = BUTTON_STATE;
    if (first_state == second_state && BUTTON_STATE == pressed) state_pushed = 1;
    else state_pushed = 0;
}
void read_button1()
{
    first_function = second_function;
    second_function = BUTTON_FUNCTION;
    if (first_state == second_state && BUTTON_FUNCTION == pressed) function_pushed = 1;
    else function_pushed = 0;
}