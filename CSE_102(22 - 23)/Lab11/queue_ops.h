#ifndef QUEUE_OPS_H
#define QUEUE_OPS_H
typedef struct n
{
    char Customer_name[20];
    int order_ID;
    char items_ordered[50];
    char order_time[10];
    struct n* next;
}Order;
Order* enqueue(Order  *  queue,  char  *  customerName,  int  orderID, char  *  items,  char  * orderTime);
Order* dequeue(Order *queue);
void Display(Order *queue);
void Update_Order(Order *queue, int orderID, char* newItems);
#endif