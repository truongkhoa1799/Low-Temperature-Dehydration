#include "linked_list.h"
void LINKED_LIST_INITIALIZATION()
{
    head = -1;
    no_funcs = 0;
	for (int i = 0; i < NUM_FUNCS; i++)
	{
		array[i].next = -1;
		array[i].delay = 0;
		array[i].period = 0;
		array[i].function = NULL;
	}
}

int ADD_NODE(timestamp_t delay , timestamp_t period , FUNCTION_PTR function )
{
    struct Node temp = create_node(delay , period , function);
    int index = return_index();
    if (index != -1)
    {
        if (head == -1)
        {
            head =index;
            add(temp , head);
            return index;
        }
        else 
        {
            int loc = head;
            int pre = head;
            int loop = 1;
            while (loop<no_funcs && temp.delay >= array[loc].delay)
            {
                pre = loc;
                loc = array[loc].next;
                loop ++;
                temp.delay = temp.delay - array[pre].delay;
            }
            if (loc == head)
            {
                add(temp , index);
                array[index].next = head;
                head = index;
                int next = array[index].next;
                array[next].delay = array[next].delay - array[index].delay;
            }
            else if (loc != -1){
                add(temp , index);
                array[pre].next = index;
                array[index].next = loc;
                array[loc].delay = array[loc].delay - array[index].delay;
                  
            }
            else if (loc == -1) //check if the loc is at the end of array
            {
                add(temp , index);
                array[pre].next = index;
                 
           }
        }
        return index;
    }
    else return -1;
}

void UPDATE_TIMER()
{
    if (array[head].delay != 0) array[head].delay = array[head].delay -10;
    else
    {
        while (array[head].delay ==0)
        {
            enqueue(array[head].function);
            timestamp_t delay = array[head].period;
            timestamp_t period = array[head].period;
            FUNCTION_PTR function = array[head].function;
            int temp_head = head;

            head = array[head].next;
            clean_node(temp_head); // initial this node , check_index[] = 0 no_funcs --

            ADD_NODE(delay , period , function);
        }
    }
}

int REMOVE_NODE(int id)
{
    if (check_index[id]==0) return 0;
    
    int loc = head;
    int pre = loc;
    while (loc != id)
    {
        pre = loc;
        loc = array[loc].next;
    }
    array[pre].next = array[loc].next;
    
    int delay = array[loc].delay;
    int next = array[loc].next;
    clean_node(loc);
    array[next].delay = array[next].delay + delay;
    return 1;
}

void add(struct Node temp , int index)
{
    array[index].next = temp.next;
	array[index].delay = temp.delay;
	array[index].period = temp.period;
	array[index].function = temp.function;
}

int return_index()
{
    for (int i = 0 ; i<NUM_FUNCS ; i++)
        if (check_index[i] ==0)
        {
            check_index[i]=1;
            no_funcs++;
            return i;
        }
    return -1;
}

void clean_node(int index)
{
    array[index].next=-1;
    array[index].delay = 0;
    array[index].period = 0;
    array[index].function = NULL;
    check_index[index] = 0;
    no_funcs --;
}

struct Node create_node(timestamp_t delay , timestamp_t period , FUNCTION_PTR function){
    struct Node temp;
    temp.next = -1;
    temp.delay = delay;
    temp.period = period;
    temp.function = function;
    return temp;
}

void init_queue()
{
    front = -1;
    rear = -1;
    no_q = 0;
    
    for (int i = 0; i<NUM_Q ; i++)
        queue[i] = NULL;
}
FUNCTION_PTR dequeue()
{
    FUNCTION_PTR temp = queue[front];
    no_q  --;
    if (no_q ==0) 
    {
        init_queue();
        return temp;
    }
    else {
        front = (front +1)%NUM_Q;
        return temp;
    }
}
void enqueue(FUNCTION_PTR function)
{
    if (front ==-1)
    {
        front =0;
        rear = 0;
        no_q ++;
        queue[front] = function;
    }
    else
    {
        rear = (rear +1)%NUM_Q;
        no_q ++;
        queue[rear] = function;
    }
}

