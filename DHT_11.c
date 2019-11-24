#include "DHT_11.h"

char getByte() {
    char i;
    char byteReceived = 0;
    unsigned int timeOut;
    
    for(i = 0b1000000; i != 0x00; i = i >> 1) {
        timeOut = TIME_OUT;
        while(!DHT_DATA_IN) {
            if(--timeOut == 0) return 0;
        }
        __delay_us(30);
        if(DHT_DATA_IN & 1) {
            byteReceived = byteReceived | i;
            timeOut = TIME_OUT;
            while(DHT_DATA_IN & 1) {
                if(--timeOut == 0) return 0;
            }
        }
    }
    
    return byteReceived;
}

char readDHT() {
    char checkSum;
    unsigned int timeOut = TIME_OUT;
    DHT_DIRECTION = 0;
    DHT_DATA_OUT = 0;
    __delay_ms(20);
    
    DHT_DATA_OUT = 1;
    __delay_us(20);
    DHT_DIRECTION = 1;
    
    while(DHT_DATA_IN & 1) {
        LATDbits.LATD1 = 1;
        if(--timeOut == 0)
            return 0;
    }
    //LATDbits.LATD0 = 0;
    timeOut = TIME_OUT;
    while(!DHT_DATA_IN & 1) {
        LATDbits.LATD2 = 1;
        if(--timeOut == 0)
            return 0;
    }
    
    //LATDbits.LATD0 = 0;
    
    timeOut = TIME_OUT;
    while(DHT_DATA_IN & 1) {
        LATDbits.LATD3 = 1;
        if(--timeOut == 0)
            return 0;
    }
//    LATDbits.LATD2 = 0;
    LATDbits.LATD4 = 1;
    mCURSOR_LINE1;
    LCDPutStr("Fail");
    humidity_dht11[0] = getByte();
    humidity_dht11[1] = getByte();
    temperature_dht11[0] = getByte();
    temperature_dht11[1] = getByte();
    checkSum = getByte();

    if( (char)( humidity_dht11[0] + humidity_dht11[1] + temperature_dht11[0] + temperature_dht11[1] ) != checkSum )
    {
        mCURSOR_LINE1;
        LCDPutStr("Fail");
        return 0;
    }
    else
    {
        mCURSOR_LINE1;
        LCDPutStr("Temp;");
        mCURSOR_LINE1;
        LCDPutStr("Humid;");
    }

    return 1;
}

void readTempAndHumid(void) {
    if(!readDHT()) {
        temperature_value = ERROR_SENSOR_VAL;
        humidity_value = ERROR_SENSOR_VAL;
        return;
    }
    
    temperature_value = temperature_dht11[0];
    if (temperature_dht11[1] & 0x80) {
        temperature_value = -1 - temperature_value;
    }
    temperature_value += (temperature_dht11[3] & 0x0f) * 0.1;
    
    humidity_value = humidity_dht11[0]; //take 2 integral number
    //humidity_value = humidity_dht11[0] + humidity_dht11[1] * 0.1;
}
