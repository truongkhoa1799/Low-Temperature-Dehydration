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
#define _XTAL_FREQ  10000000

void heater_heatpumper()
{
    static int check_off = 1;
    if (state == ON)
    {
        if (time_each_state>0)
        {
            if (FUNCTION == Heater) 
            {
                if (temperature_value < MAX_TEMPERATURE) printLCD_string(0,"Heating   F3:   ");
                else printLCD_string(0 , "Nothing   F3:   ");
                time_each_state--;
            }else if (FUNCTION == Heat_pumper)
            {
                printLCD_string(0,"Pump heat F3:   ");
                time_each_state--;
            }
        }
        else{
            time_each_state = TIME_EACH_STATE;
            if (FUNCTION == Heater) FUNCTION = Heat_pumper;
            else if (FUNCTION == Heat_pumper) FUNCTION = Heater;
        }
        
        if (turn_fan3 == 1) 
        {
            if (fan3 == '100') 
            {
                printLCD_char(0 , 13 , '1');
                printLCD_char(0 , 14 , '0');
                printLCD_char(0 , 15 , '0');
            }
            else
            {
                printLCD_char(0,13,fan3/10+'0');
                printLCD_char(0,14,fan3%10+'0');
                printLCD_char(0 , 15 , ' ');
            }
        }
        else
        {
            printLCD_char(0 , 13 , 'O');
            printLCD_char(0 , 14, 'F');
            printLCD_char(0 , 15 , 'F');
        }
        check_off = 1;
    }
    else if (state == OFF) {
        if (check_off==1)
        {
            printLCD_string(0,"OFF       F3:  ");
            printLCD_char(0 , 13 , 'O');
            printLCD_char(0 , 14, 'F');
            printLCD_char(0 , 15 , 'F');
            printLCD_char(1 , 5 , '0');
            printLCD_char(1 , 6 , '0');
            printLCD_char(1 , 14 ,'0');
            printLCD_char(1 , 15 ,'0');
            check_off =0;
        }
    }
}
void check_button()
{
    static int check_but_state = 0;
    //static int check_but_function = 0;
    if (state_pushed ==1 && check_but_state ==0)
    {
        if (state == ON) 
        {
            state = OFF;
            LED = 0;
        }
        else if (state == OFF)
        {
            state = ON;
            LED = 1;
        }
        check_but_state = 1;
    }
    else if (state_pushed == 0 && check_but_state ==1)
    {
        check_but_state = 0;
    }
}
void SYSTEM_INITIALIZATION()
{
    mOPEN_LCD;
    printLCD_string(1,"Temp:   Humid:");
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
    TMR0_INITIALIZATION();
    TMR1_INITIALIZATION();
    init_queue();
}

void main(void) {
    
    LINKED_LIST_INITIALIZATION();
    SYSTEM_INITIALIZATION();
    register_timer(0 , 500 , check_button);
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
