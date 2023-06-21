#ifndef QUEUE_H
#define QUEUE_H
typedef struct n
{
    char name[20];
    int age;
    char priority_group[20];
    int priority_lvl;
    struct n* next;
    struct n* prev;
}Customer;
Customer* Read_file(Customer *queue);
void Write_file(Customer *queue);
Customer *Insert(Customer *queue, Customer *temp);
Customer *Remove(Customer *queue, Customer *iter);
void Display(Customer *queue);
void Search(Customer *queue, char *name);
Customer* Change_priority(Customer *queue);
#endif
