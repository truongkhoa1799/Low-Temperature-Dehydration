/* 
 * File:   FUNCTIONS.h
 * Author: Khoa
 *
 * Created on November 25, 2019, 8:43 AM
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include "variables.h"
#ifdef	__cplusplus
extern "C" {
#endif

    
void heater_heatpumper()
{
    static int check_off_temp = 1;
    if (state == ON)
    {
        if (time_each_state>0)
        {
            if (FUNCTION == Heater) 
            {
                if (temperature_value < MAX_TEMPERATURE) 
                    printLCD_string(0,"Heating   F3:   ");
                else time_each_state = 1;
                time_each_state--;
            }
            else if (FUNCTION == Heat_pumper)
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
        else if (turn_fan3 ==0)
        {
            printLCD_char(0 , 13 , 'O');
            printLCD_char(0 , 14, 'F');
            printLCD_char(0 , 15 , 'F');
        }
    }
    else if (state == TEMP) {
        if (check_off_temp==1)
        {
            mLCD_CLEAR;
            printLCD_string(0,"TEMP:");
            printLCD_char(0 , 6 , MAX_TEMPERATURE/10 + '0');
            printLCD_char(0 , 7 , MAX_TEMPERATURE%10 + '0');
            printLCD_string(1 , "INCR:B0  NEXT:A0");
            check_off_temp = 0;
        }
    }
}
void check_button()
{
    static int check_but_state = 0;
    static int check_but_inc = 0;
    //static int check_but_function = 0;
    if (state_but ==1 && check_but_state ==0)
    {
        if (state == TEMP) 
        {
            state = HUMID;
            mLCD_CLEAR;
            printLCD_string(0,"HUMID:");
            printLCD_char(0 , 7 , MAX_HUMIDITY/10 + '0');
            printLCD_char(0 , 8 , MAX_HUMIDITY%10 + '0');
            printLCD_string(1 , "INCR:B0  NEXT:A0");
            LED = 0;
        }
        else if (state == HUMID) 
        {
            state = ON;
            mLCD_CLEAR;
            printLCD_string(1,"Temp:   Humid:");
            LED = 1;
        }
        else if (state == ON) 
        {
            state = TEMP;
            mLCD_CLEAR;
            printLCD_string(0,"TEMP:");
            printLCD_char(0 , 6 , MAX_TEMPERATURE/10 + '0');
            printLCD_char(0 , 7 , MAX_TEMPERATURE%10 + '0');
            printLCD_string(1 , "INCR:B0  NEXT:A0");
            LED = 0;
        }
        check_but_state = 1;
    }
    else if (state_but == 0 && check_but_state ==1)
    {
        check_but_state = 0;
    }
    //-------------------------------------------------------
    if (inc_but ==1 && check_but_inc ==0)
    {
       if (state == TEMP)
        {
            mLCD_CLEAR;
            printLCD_string(0,"TEMP:");
            printLCD_char(0 , 6 , MAX_TEMPERATURE/10 + '0');
            printLCD_char(0 , 7 , MAX_TEMPERATURE%10 + '0');
            printLCD_string(1 , "INCR:B0  NEXT:A0");
            MAX_TEMPERATURE = (MAX_TEMPERATURE + 5) % 100; 
        }
        else if (state == HUMID)
        {
            mLCD_CLEAR;
            MAX_HUMIDITY = (MAX_HUMIDITY + 5) % 100; 
            printLCD_string(0,"HUMID:");
            printLCD_char(0 , 7 , MAX_HUMIDITY/10 + '0');
            printLCD_char(0 , 8 , MAX_HUMIDITY%10 + '0');
            printLCD_string(1 , "INCR:B0  NEXT:A0");
        }
        check_but_inc = 1;
    }
    else if (inc_but == 0 && check_but_inc ==1)
    {
        check_but_inc = 0;
    }
}



#ifdef	__cplusplus
}
#endif

#endif	/* FUNCTIONS_H */

