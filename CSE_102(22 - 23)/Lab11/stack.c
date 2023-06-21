#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

ExamPaper  *  push(ExamPaper  *  stack,  char  * studentName, int studentNumber, int score)
{
    ExamPaper* temp;
    temp = (ExamPaper*)malloc(sizeof(ExamPaper));
    strcpy(temp->name,studentName);
    temp->number = studentNumber;
    temp->score = score;
    temp->next = stack;
    stack = temp;
    return stack;
}

ExamPaper* pop(ExamPaper *stack)
{
    if(stack == NULL)
    {
        printf("No element to pop");
        return stack;
    }
    ExamPaper *iter;
    iter = stack;
    stack = stack->next;
    iter->next = NULL;
    free(iter);
    return stack;
}

int isEmpty(ExamPaper *stack)
{
    return stack == NULL;
}

void Display(ExamPaper *stack)
{
    ExamPaper *iter = stack;
    if(isEmpty(stack))
    {
        printf("no elements to display!!\n");
        return;
    }
    while(iter != NULL)
    {
        printf("Name: %s, ID: %d, Score: %.2f\n",iter->name,iter->number,iter->score);
        iter = iter->next;
    }
    
}