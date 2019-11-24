/* 
 * File:   dht11.h
 * Author: Tuan
 *
 * Created on November 18, 2019, 10:25 AM
 */

#ifndef DHT11_H
#define	DHT11_H

#include <xc.h>
#define _XTAL_FREQ  10000000

#include "variables.h"
#include "BBSPI_LCD.h"
void get_temp_humid(void);
char readDHT();
char getByte();
void print_temp_humid();

#endif	/* DHT11_H */

