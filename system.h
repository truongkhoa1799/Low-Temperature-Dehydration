/* 
 * File:   system.h
 * Author: Khoa
 *
 * Created on October 8, 2019, 11:25 AM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H


#include <stdint.h>
#include <stdbool.h>
#include "interrupt.h"
#include "linked_list.h"
#include "timer1.h"
#include "timer0.h"
#include "pin_manager.h"
#include "variables.h"


#ifdef	__cplusplus
extern "C" {
#endif

    void SYSTEM_INITIALIZATION();
    void OSCILLATOR_INITIALIZATION();
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

