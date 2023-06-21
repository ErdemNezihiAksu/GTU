#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int Menu()
{
    int c;
label:
    printf("\nWelcome to ABC bank\n\n1. Insert new costumer\n2. Remove Customer\n3. Display customers\n4. Search a customer\n5. Change priority settings\n6. Exit\n> ");
    scanf("%d", &c);
    if (c < 1 || c > 6)
    {
        printf("Invalid opt!!\n");
        goto label;
    }
}

int main()
{
    Customer *queue = NULL, *temp;
    queue = Read_file(queue);
    char name[20];

    while (1)
    {
        int c = Menu();
        switch (c)
        {
        case 1:
            while (getchar() != '\n');
            temp = (Customer*)malloc(sizeof(Customer));
            printf("Please enter name: ");
            scanf("%[^\n]", temp->name);
            printf("Please enter age: ");
            scanf("%d", &temp->age);
            printf("Please enter priority group: ");
            scanf("%s", temp->priority_group);
            if (strcmp(temp->priority_group, "NORMAL") == 0)
                temp->priority_lvl = 1;
            else if (strcmp(temp->priority_group, "VETERAN") == 0)
                temp->priority_lvl = 2;
            else if (strcmp(temp->priority_group, "OD") == 0)
                temp->priority_lvl = 3;
            else if (strcmp(temp->priority_group, "VIP") == 0)
                temp->priority_lvl = 4;
            queue = Insert(queue,temp);
            printf("Customer added succesfully...\n");
            break;
        case 2:
            while (getchar() != '\n');
            if(queue == NULL)
            {
                printf("There is no customer!!\n");
            }
            printf("Enter customers name: ");
            scanf("%[^\n]",name);
            temp = queue;
            while(temp != NULL)
            {
                if(strcmp(temp->name,name) == 0)
                    break;
                temp = temp->next;
            }
            queue = Remove(queue,temp);
            printf("Customer removed succesfully...\n");
            break;
        case 3:
            Display(queue);
            break;
        case 4:
            while (getchar() != '\n');
            printf("Enter the name of the customer: ");
            scanf("%[^\n]", name);
            Search(queue, name);
            break;
        case 5:
            while (getchar() != '\n');
            queue = Change_priority(queue);
            break;
        default:
            return 0;
        }
    }
}