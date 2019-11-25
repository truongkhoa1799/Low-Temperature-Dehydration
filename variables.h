/* 
 * File:   variables.h
 * Author: Khoa
 *
 * Created on October 8, 2019, 2:02 PM
 */

#ifndef VARIABLES_H
#define	VARIABLES_H

#define NUM_FUNCS 20
#define NUM_Q 1000

#define ERROR_SENSOR_VAL 256
#define TIME_EACH_STATE 20 //10s

#define TIME_OUT_DHT 100
#define DHT_DATA_IN PORTDbits.RD0
#define DHT_DATA_OUT LATDbits.LATD0
#define DHT_DIRECTION TRISDbits.TRISD0
#define BUTTON_STATE PORTAbits.RA5
#define BUTTON_INCREASE PORTBbits.RB0
#define pressed 0
#define LED  LATDbits.LATD1



typedef void (*FUNCTION_PTR)();

typedef long int timestamp_t;
struct Node
{
	int next;
	long int delay;
	long int period;
    FUNCTION_PTR function;
};

int count =1;
int head = -1;
int no_funcs = 0;

struct Node array[NUM_FUNCS];
int check_index[NUM_FUNCS] = {0};

//variables for dht
unsigned int time_out_dht=0;
char humid[2];
char temper[2];
unsigned int temperature_value;
unsigned int humidity_value;
unsigned int MAX_TEMPERATURE;
unsigned int MAX_HUMIDITY; 
//variables for  heater and heat pumper
char fan3;
int turn_fan3 = 0;
enum {Heater , Heat_pumper , Nothing} FUNCTION;
enum { TEMP , HUMID , ON} state;

int time_each_state = TIME_EACH_STATE;
int state_but = 0;
int inc_but = 0;



FUNCTION_PTR queue[NUM_Q];
int front , rear , no_q;


#ifdef	__cplusplus
extern "C" {
#endif

    timestamp_t timestamp = 0;


#ifdef	__cplusplus
}
#endif

#endif	/* VARIABLES_H */

