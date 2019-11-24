#include "timer0.h"
//10ms
void TMR0_INITIALIZATION()
{
    T0CON = 0b11000111;
    TMR0 = 0xB2;
    INTCONbits.TMR0IF = 0;
}


void TMR0_IRS()
{
    INTCONbits.TMR0IF = 0;
    TMR0 = 0xB2;
}
