#include <stdio.h>
#include <stdlib.h>
#include "queue_ops.h"

char Menu()
{
    char c;
label:
    printf("\nWelcome to GTU Restaurant\n1. Make new order\n2. Dequeue order\n3. Print orders\n4. Update order\n5. Exit\n> ");
    scanf(" %c", &c);
    if (c < '1' || c > '5')
    {
        printf("Invalid option!!\n");
        goto label;
    }
    return c;
}

int main()
{
    Order *queue = NULL;
    char c, customerName[20], items[50], time[6];
    int orderID;
    while (1)
    {
        c = Menu();
        switch (c)
        {
        case '1':
            while (getchar() != '\n');
            printf("Enter ID: ");
            scanf("%d", &orderID);
            getchar();
            printf("Enter Customer Name:  ");
            scanf("%[^\n]", customerName);
            getchar();
            printf("Enter items: ");
            scanf("%[^\n]", items);
            getchar();
            printf("Enter time: ");
            scanf("%s", time);
            queue = enqueue(queue, customerName, orderID, items, time);
            break;
        case '2':
            while (getchar() != '\n');
            queue = dequeue(queue);
            break;
        case '3':
            while (getchar() != '\n');
            Display(queue);
            break;
        case '4':
            while (getchar() != '\n');
            if (queue == NULL)
            {
                printf("No elements to update!!\n");
            }
            else
            {
                printf("Enter order ID: ");
                scanf("%d", &orderID);
                getchar();
                printf("Enter New items: ");
                scanf("%[^\n]", items);
                Update_Order(queue, orderID, items);
            }
            break;
        default:
            return 0;
        }
    }
}