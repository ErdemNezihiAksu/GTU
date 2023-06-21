#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
Customer *Insert(Customer *queue, Customer *temp);

Customer *Read_file(Customer *queue)
{
    FILE *f = fopen("customer.txt", "r");
    Customer *iter, *temp;
    char buffer[100];
    char *token = (char *)malloc(sizeof(char) * 20);

    if (f == NULL)
    {
        printf("File can not be open!!\n");
        return queue;
    }
    fgets(buffer, sizeof(buffer), f);
    while (fgets(buffer, sizeof(buffer), f))
    {
        temp = (Customer *)malloc(sizeof(Customer));
        token = strtok(buffer, ",");
        strcpy(temp->name, token);
        token = strtok(NULL, ",");
        temp->age = atoi(token);
        token = strtok(NULL, ".");
        strcpy(temp->priority_group, token);
        if (strcmp(token, "NORMAL") == 0)
            temp->priority_lvl = 1;
        else if (strcmp(token, "VETERAN") == 0)
            temp->priority_lvl = 2;
        else if (strcmp(token, "OD") == 0)
            temp->priority_lvl = 3;
        else if (strcmp(token, "VIP") == 0)
            temp->priority_lvl = 4;

        queue = Insert(queue,temp);
    }
    fclose(f);
    return queue;
}

void Write_file(Customer *queue)
{
    FILE *f = fopen("customer.txt", "w");
    if (f == NULL)
    {
        printf("Error!!\n");
        return;
    }
    fprintf(f, "Name,Age,Prioraty Group");
    Customer *iter = queue;
    while (iter != NULL)
    {
        fprintf(f, "\n%s,%d,%s.", iter->name, iter->age, iter->priority_group);
        iter = iter->next;
    }
    fclose(f);
}

Customer *Insert(Customer *queue, Customer *temp)
{
    Customer *iter = queue;
    if (queue == NULL)
    {
        queue = temp;
        temp->prev = NULL;
        temp->next = NULL;
    }
    else if (queue->priority_lvl < temp->priority_lvl)
    {
        temp->next = queue;
        queue->prev = temp;
        queue = temp;
        temp->prev = NULL;
    }
    else
    {
        iter = queue;
        while (iter->next != NULL && iter->next->priority_lvl > temp->priority_lvl)
            iter = iter->next;
        temp->next = iter->next;
        temp->prev = iter;
        if (iter->next != NULL)
            iter->next->prev = temp;
        iter->next = temp;
    }
    Write_file(queue);
    return queue;
}

Customer *Remove(Customer *queue, Customer *iter)
{
    Customer *remove;
    if(iter == NULL)
    {
        printf("Customer can not be found!!\n");
        return queue;
    }
    remove = iter;
    remove->prev->next = remove->next;
    if(remove->next != NULL)
        remove->next->prev = remove->prev;
    free(remove);
    Write_file(queue);
    return queue; 
}
void Display(Customer *queue)
{
    if (queue == NULL)
    {
        printf("No customer to display!!\n");
        return;
    }
    Customer *iter = queue;
    while (iter != NULL)
    {
        printf("Name: %s - Age: %d - Priority group: %s - Priority level: %d\n", iter->name, iter->age, iter->priority_group, iter->priority_lvl);
        iter = iter->next;
    }
}

void Search(Customer *queue, char *name)
{
    if(queue == NULL)
    {
        printf("\nCustomer could not be found!!\n");
        return;
    }
    if(strcmp(queue->name,name) == 0)
    {
        printf("\nName: %s - Age: %d - Priority group: %s - Priority level: %d\n", queue->name, queue->age, queue->priority_group, queue->priority_lvl);
        return;
    }
    Search(queue->next,name);
}

Customer* Change_priority(Customer *queue)
{
    char name[20];
    Customer *iter, *temp;
    int lvl;

    if(queue == NULL)
    {
        printf("There is no customer!!\n");
        return queue;
    }
    printf("Enter the name: ");
    scanf("%[^\n]",name);
    printf("Enter new priority level: ");
    scanf("%d",&lvl);
    iter = queue;
    while(iter != NULL && strcmp(iter->name,name) != 0)
        iter = iter->next;
    if(iter == NULL)
    {
        printf("Customer can not be found!!\n");
        return queue;
    }

    temp = (Customer*)malloc(sizeof(Customer));
    strcpy(temp->name,iter->name);
    temp->age = iter->age;
    if(lvl == 1)
    {
        temp->priority_lvl = 1;
        strcpy(temp->priority_group,"NORMAL");
    }
    else if(lvl == 2)
    {
        temp->priority_lvl = 2;
        strcpy(temp->priority_group,"VETERAN");
    }
    else if(lvl == 3)
    {
        temp->priority_lvl = 3;
        strcpy(temp->priority_group,"OD");
    }
    else if(lvl == 4)
    {
        temp->priority_lvl = 4;
        strcpy(temp->priority_group,"VIP");
    }
    queue = Remove(queue,iter);
    queue = Insert(queue,temp);
    return queue;
}