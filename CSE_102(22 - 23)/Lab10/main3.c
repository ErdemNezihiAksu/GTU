#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int ID;
    int age;
    float GPA;
}Student;

float part3()
{
    Student* arr = (Student*)malloc(10000*sizeof(Student));
    float av_gpa = 0;

    srand(time(NULL));
    for(int i = 0; i< 10000; i++)
    {
        arr[i].age = rand() % 10 + 18;
        arr[i].ID = rand() % 1000 + 1000;
        arr[i].GPA = (rand() % 4 + 1) * drand48(); 
        av_gpa += arr[i].GPA;
    }
    av_gpa /= 10000;
    free(arr);
    return av_gpa;
}

int main()
{
    float av_GPA = 0;

    for(int i = 0; i < 10000; i++)
    {
        av_GPA += part3();
    }
    av_GPA /= 10000;
    printf("Average GPA of 10.000 x 10.000 students: %f\n",av_GPA);
}