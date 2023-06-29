#ifndef linked_list
#define linked_list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Node
{
    void *data;
    struct Node *next;
} Node;
typedef struct
{
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;
typedef struct 
{
    char type[20];
    int ivals[2];
    double svals[2];
}Asset2;
typedef struct 
{
    char type[20];
    char string1[50];
    char string2[50];
}Asset3;
typedef struct 
{
    char type[20];
    double value1;
    float value2;
    double value3;
}Asset4;
void Deallocte_list(Node** head);
void fillLinkedList(Node**  head);
void serializeLinkedList(Node *head);
void deserializeLinkedList(Node **head);
#endif