#ifndef STACK_H
#define STACK_H
typedef struct m
{
    char name[20];
    int number;
    float score;
    struct m* next;
}ExamPaper;
ExamPaper  *  push(ExamPaper  *  stack,  char  * studentName, int studentNumber, int score);
ExamPaper* pop(ExamPaper *stack);
void Display_stack(ExamPaper *stack);
void serializeLIFO(ExamPaper *stack, const char* filename);
ExamPaper* deserializeLIFO(const char* filename);
#endif