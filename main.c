/*
 * File:   main.c
 * Author: Khoa
 *
 * Created on October 8, 2019, 11:26 AM
 */
#ifdef _18F8722
#pragma config  OSC = INTIO7
#pragma config 	FCMEN = OFF
#pragma config 	IESO = OFF
#pragma config 	PWRT = OFF
#pragma config 	BOREN = OFF
#pragma config 	WDT = OFF
#pragma config 	MCLRE = ON
#pragma config 	LVP = OFF
#pragma config 	XINST = OFF
#endif

#include "interrupt.h"
#include "BBSPI_LCD.h"
#include "dht11.h"
#include <xc.h>
#include "FUNCTIONS.h"
#define _XTAL_FREQ  10000000

void SYSTEM_INITIALIZATION()
{
    mOPEN_LCD;
    INTCONbits.GIE=1;
    //TRISDbits.TRISD1 = 1;
    //INTCONbits.PEIE = 1;
    OSCCON=0x73; //8MHz and scale 256
    OSCTUNE=0b00001111;
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB0 = 1;
    TRISDbits.TRISD1 = 0;
    ADCON1 = 0b00001111;
    LED = 0;
    MAX_TEMPERATURE = 0;
    MAX_HUMIDITY = 0;
    TMR0_INITIALIZATION();
    TMR1_INITIALIZATION();
    init_queue();
}

void main(void) {
    
    LINKED_LIST_INITIALIZATION();
    SYSTEM_INITIALIZATION();
    register_timer(0 , 500 , check_button); // 500 
    register_timer(1000 , 500 , heater_heatpumper);
    register_timer(1000 , 1000 , get_temp_humid);
    
    start_timers();
    while (1){
        if (no_q>0)
        {
            FUNCTION_PTR function = dequeue();
            (function)();
        }
    }
    
    return;
}
