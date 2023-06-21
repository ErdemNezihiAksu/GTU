#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

char Menu()
{
    char c;
    label:
    printf("\nExam operations\n1. Push\n2. Pop\n3. Is Empty\n4. Print\n5. Exit\n> ");
    scanf(" %c",&c);
    if(c < '1' || c > '5')
    {
        printf("Invalid option!!\n");
        goto label;
    }
    return c;
}

int main()
{
    ExamPaper *stack = NULL;
    char c, name[20];
    int ID;
    float score;

    while(1)
    {
        c = Menu();
        switch (c)
        {
        case '1':
            while(getchar()!='\n');
            printf("Enter Name: ");
            scanf("%[^\n]",name);
            printf("Enter ID: ");
            scanf("%d",&ID);
            printf("Enter Score: ");
            scanf("%f",&score);
            stack = push(stack,name,ID,score);
            break;
        case '2':
            while(getchar()!='\n');
            stack = pop(stack);
            break;
        case '3':
            printf("Stack is ");
            if(isEmpty(stack))
                printf("empty\n");
            else
                printf("not empty\n");
            break;
        case '4':
            Display(stack);
            break;
        default:
            return 0;
        }
    }
}