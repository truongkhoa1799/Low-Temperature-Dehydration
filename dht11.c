#include "dht11.h"

char getByte() {
    char i, j;
    for(j = 0; j < 8; j++){
        time_out_dht = TIME_OUT_DHT;
        while(!DHT_DATA_IN & 1) 
            if(time_out_dht == 0) return 0;
        __delay_us(30);
        if(!DHT_DATA_IN & 1)
            i&= ~(1<<(7 - j)); //Clear bit (7-b)
        else {
            i|= (1 << (7 - j)); //Set bit (7-b)
            time_out_dht = TIME_OUT_DHT;
        } 
        while(DHT_DATA_IN & 1) 
            if(time_out_dht == 0) return 0;
    }
    return i; 
}

char readDHT() {
    char check_sum;
    DHT_DIRECTION = 0;
    DHT_DATA_OUT = 0;
    __delay_ms(20);
    
    DHT_DATA_OUT = 1;
    __delay_us(20);
    DHT_DIRECTION = 1;
    
    time_out_dht = TIME_OUT_DHT;
    while(DHT_DATA_IN & 1) {
        if(time_out_dht == 0) return 0;
    }
     
    time_out_dht = TIME_OUT_DHT;
    while(!DHT_DATA_IN & 1) {
        if(time_out_dht == 0) return 0;
    }
    
    time_out_dht = TIME_OUT_DHT;
    while(DHT_DATA_IN & 1) {
        if(time_out_dht == 0) return 0;
    }
    humid[0] = getByte();
    humid[1] = getByte();
    temper[0] = getByte();
    temper[1] = getByte();
    check_sum = getByte();
    char temp = (humid[0] + humid[1] + temper[0] + temper[1] ) & 0xFF;
//    printLCD_char(0,0,temper[0]/10 +'0');
//    printLCD_char(0,1,temper[0]%10 +'0');
//    printLCD_char(0,2,temper[1]/10 +'0');
//    printLCD_char(0,3,temper[1]%10 +'0');
//    printLCD_char(0,5,humid[0]/10 +'0');
//    printLCD_char(0,6,humid[0]%10 +'0');
//    printLCD_char(0,7,humid[1]/10 +'0');
//    printLCD_char(0,8,humid[1]%10 +'0');
//    printLCD_char(0,10,check_sum/10 + '0');
//    printLCD_char(0,11,check_sum%10 + '0');
//    printLCD_char(0,13,temp/10 + '0');
//    printLCD_char(0,14,temp%10 + '0');
    if( temp  == check_sum ) return 1;
    else return 0;
}

void get_temp_humid(void) {
    if (state == ON)
    {
        if(!readDHT()) {
            temperature_value = ERROR_SENSOR_VAL;
            humidity_value = ERROR_SENSOR_VAL;
            return;
        }
        //if (state == OFF) mLCD_CLEAR;
        print_temp_humid();
        temperature_value = temper[0];
        humidity_value = humid[0];

        if (humidity_value>MAX_HUMIDITY)  turn_fan3 = 1;
        else turn_fan3 = 0;
        if (humidity_value >= 90) fan3 = 100;
        else fan3 = humid[0];
    }
}

void print_temp_humid()
{
    printLCD_char(1 , 5 , temper[0]/10 +'0');
    printLCD_char(1 , 6 , temper[0]%10 +'0');
    printLCD_char(1 , 14 , humid[0]/10 +'0');
    printLCD_char(1 , 15 , humid[0]%10 +'0');
}