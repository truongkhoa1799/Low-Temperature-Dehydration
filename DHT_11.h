/* 
 * File:   DHT_11.h
 * Author: Khoa
 *
 * Created on November 18, 2019, 9:42 AM
 */

#ifndef DHT_11_H
#define	DHT_11_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdio.h>
#include "variables.h"
#include "BBSPI_LCD.h"
    
#define _XTAL_FREQ  10000000 

char readDHT();
char getByte();
void readTempAndHumid(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DHT_11_H */

