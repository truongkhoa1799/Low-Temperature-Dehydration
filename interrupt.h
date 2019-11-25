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
    int inc_but_1 = 0;
    int inc_but_2 = 0;

void __interrupt() INTERRUPT_InterruptManager (void);
void read_button();
void read_button_increase();

#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_H */

