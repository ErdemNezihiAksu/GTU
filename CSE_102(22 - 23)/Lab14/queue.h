#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct n
{
    char Customer_name[20];
    int order_ID;
    char items_ordered[50];
    time_t order_time;
    struct n* next;
}Order;
Order* enqueue(Order  *  queue,  char  *  customerName,  int  orderID, char  *  items,  time_t orderTime);
Order* dequeue(Order *queue);
void Display_queue(Order *queue);
void  serializeFIFO(Order* queue, const char* filename);
Order* deserializeFIFO(const char* filename);
#endif