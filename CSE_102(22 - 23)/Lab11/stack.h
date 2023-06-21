#ifndef STACK_H
#define STACK_H
typedef struct n
{
    char name[20];
    int number;
    float score;
    struct n* next;
}ExamPaper;
int isEmpty(ExamPaper *stack);
ExamPaper  *  push(ExamPaper  *  stack,  char  * studentName, int studentNumber, int score);
ExamPaper* pop(ExamPaper *stack);
int isEmpty(ExamPaper *stack);
void Display(ExamPaper *stack);
#endif