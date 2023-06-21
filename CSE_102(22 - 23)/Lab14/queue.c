#include "queue.h"
#include <time.h>

Order *enqueue(Order *queue, char *customerName, int orderID, char *items, time_t orderTime)
{
    Order *temp, *iter;

    temp = (Order *)malloc(sizeof(Order));
    iter = queue;
    strcpy(temp->Customer_name, customerName);
    temp->order_ID = orderID;
    strcpy(temp->items_ordered, items);
    temp->order_time = orderTime;
    temp->next = NULL;
    if (queue == NULL)
    {
        queue = temp;
        return queue;
    }
    while (iter->next != NULL)
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

void Display_queue(Order *queue)
{
    Order *iter = queue;
    if (queue == NULL)
    {
        printf("There are no orders!!\n");
        return;
    }
    while (iter != NULL)
    {
        printf("Order ID: %d, Customer Name: %s, Items: %s, Order Time: %s\n", iter->order_ID, iter->Customer_name, iter->items_ordered, ctime(&iter->order_time));
        iter = iter->next;
    }
}

void serializeFIFO(Order *queue, const char *filename)
{
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
    {
        printf("Failed to open file...\n");
        return;
    }
    Order *iter = queue;
    while (iter != NULL)
    {
        fwrite(iter, sizeof(Order), 1, f);
        iter = iter->next;
    }
    fclose(f);
}

Order *deserializeFIFO(const char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        printf("Failed to open file...");
        return NULL;
    }
    Order *queue = NULL, *temp, *iter = queue;
    while (1)
    {
        temp = (Order *)malloc(sizeof(Order));
        size_t bytesread = fread(temp, sizeof(Order), 1, f);
        temp->next = NULL;
        if (bytesread == 1)
        {
            if (queue == NULL)
            {
                queue = temp;
                iter = queue;
            }
            else
            {
                iter->next = temp;
                iter = iter->next;
            }
        }
        else if (feof(f))
            break;
        else
        {
            printf("Error reading file...\n");
            return NULL;
        }
    }
    return queue;
}