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

void Display_stack(ExamPaper *stack)
{
    ExamPaper *iter = stack;
    if(stack == NULL)
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

void serializeLIFO(ExamPaper *stack, const char* filename)
{
    FILE *f = fopen(filename,"wb");
    if(f == NULL)
    {
        printf("Failed to open file...\n");
        return;
    }
    ExamPaper *iter = stack;
    while (iter != NULL)
    {
        fwrite(iter,sizeof(ExamPaper),1,f);
        iter = iter->next;
    }
    fclose(f);
}

ExamPaper* deserializeLIFO(const char* filename)
{
    FILE *f = fopen(filename,"rb");
    if(f == NULL)
    {
        printf("Failed to open file...");
        return NULL;
    }
    ExamPaper *stack = NULL, *temp, *iter = stack;
    while(1)
    {
        temp = (ExamPaper*)malloc(sizeof(ExamPaper));
        size_t bytesread = fread(temp,sizeof(ExamPaper),1,f);
        if(bytesread == 1)
        {
            if(stack == NULL)
            {
                stack = temp;
                iter = stack;
            }
            else
            {
                iter->next = temp;
                iter = iter->next;
            }
        }
        else if(feof(f))
            break;
        else
        {
            printf("Error reading file...\n");
            return NULL;
        }
    }
    return stack;
}