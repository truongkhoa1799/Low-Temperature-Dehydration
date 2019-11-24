/* 
 * File:   clock.h
 * Author: Khoa
 *
 * Created on October 8, 2019, 2:19 PM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include "timer0.h"
#include "timer1.h"
#include "linked_list.h"

#ifdef	__cplusplus
extern "C" {
#endif

    int start_timers();
    timestamp_t get_time(void);
    int stop_timers();
    int register_timer(timestamp_t delay , timestamp_t period , FUNCTION_PTR function);
    int remove_timer(int id);
    void timer_ISR();
    
#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

