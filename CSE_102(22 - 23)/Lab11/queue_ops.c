#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_ops.h"

Order* enqueue(Order  *  queue,  char  *  customerName,  int  orderID, char  *  items,  char  * orderTime)
{
    Order *temp, *iter;
    temp = (Order*)malloc(sizeof(Order));
    iter = queue;
    strcpy(temp->Customer_name,customerName);
    temp->order_ID = orderID;
    strcpy(temp->items_ordered,items);
    strcpy(temp->order_time,orderTime);
    temp->next = NULL;
    if(queue == NULL)
    {
        queue = temp;
        return queue;
    }
    while(iter->next != NULL)
        iter = iter->next;
    iter->next = temp;
    return queue;
}

Order* dequeue(Order *queue)
{
    if(queue == NULL)
    {
        printf("No element to dequeue!!\n");
        return queue;
    }
    Order *iter = queue;
    queue = queue->next;
    iter->next = NULL;
    free(iter);
    return queue;
}

void Display(Order *queue)
{
    Order *iter = queue;
    if(queue == NULL)
    {
        printf("There are no orders!!\n");
        return;
    }
    while(iter != NULL)
    {
        printf("Order ID: %d, Customer Name: %s, Items: %s\n",iter->order_ID,iter->Customer_name,iter->items_ordered);
        iter = iter->next;
    }
}

void Update_Order(Order *queue, int orderID, char* newItems)
{
    Order *iter = queue;
    while(iter != NULL && iter->order_ID != orderID)
        iter = iter->next;
    if(iter == NULL)
    {
        printf("Order does not exist!!\n");
        return;
    }
    memset(iter->items_ordered,sizeof(iter->items_ordered),0);
    strcpy(iter->items_ordered,newItems);
}