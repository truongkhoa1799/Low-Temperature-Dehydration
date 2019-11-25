#include "interrupt.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    if (INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1)
    {
        read_button();
        read_button_increase();
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
    if (first_state == second_state && BUTTON_STATE == pressed) state_but = 1;
    else state_but = 0;
}
void read_button_increase()
{
    inc_but_1 = inc_but_2;
    inc_but_2 = BUTTON_INCREASE;
    if (first_state == second_state && BUTTON_INCREASE == pressed) inc_but = 1;
    else inc_but = 0;
}