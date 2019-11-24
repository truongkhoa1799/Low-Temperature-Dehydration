/* 
 * File:   interrupt.h
 * Author: Khoa
 *
 * Created on October 8, 2019, 11:26 AM
 */

#ifndef INTERRUPT_H
#define	INTERRUPT_H

#include "clock.h"
#include "variables.h"
#ifdef	__cplusplus
extern "C" {
#endif
    
    int first_state = 0;
    int second_state = 0;
    int first_function = 0;
    int second_function = 0;

void __interrupt() INTERRUPT_InterruptManager (void);
void read_button();
void read_button1();

#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_H */

