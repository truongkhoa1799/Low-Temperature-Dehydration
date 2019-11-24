/* 
 * File:   linked_list.h
 * Author: Khoa
 *
 * Created on October 8, 2019, 3:36 PM
 */

#ifndef LINKED_LIST_H
#define	LINKED_LIST_H


#include <xc.h>
#include "variables.h"
#ifdef	__cplusplus
extern "C" {
#endif


int return_index();
void add(struct Node temp , int index);
void clean_node(int index);
struct Node create_node(timestamp_t delay , timestamp_t period , FUNCTION_PTR function);


void LINKED_LIST_INITIALIZATION();
int ADD_NODE(timestamp_t delay , timestamp_t period , FUNCTION_PTR function);
void UPDATE_TIMER();
int REMOVE_NODE(int id);

void init_queue();
FUNCTION_PTR dequeue();
void enqueue(FUNCTION_PTR function);


#ifdef	__cplusplus
}
#endif

#endif	/* LINKED_LIST_H */

