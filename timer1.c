#include "timer1.h"
//10ms
void TMR1_INITIALIZATION()
{
    T1CON = 0b10000001;
    PIR1bits.TMR1IF = 0;
    TMR1H = 0xB1;
    TMR1L = 0xE0;
}
void TMR1_IRS()
{
    PIR1bits.TMR1IF = 0;
    TMR1H = 0xB1;
    TMR1L = 0xE0;
}
