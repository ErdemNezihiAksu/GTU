#include <stdio.h>

int main()
{
    int age, exp_year;

    printf("Please enter your age: ");
    scanf("%d", &age);
    printf("Please enter your years of experience: ");
    scanf("%d", &exp_year);

    if(age < 20)
    {
        if(exp_year < 10)
        printf("Your salary is 10,000$\n");
        else
        printf("Error\n");
    }
    else if(age >= 20 && age < 50)
    {
        if(exp_year < 10)
        printf("Your salary is 15,000$\n");
        else
        printf("Your salary is 20,000$\n");
    }
    else
    {
        if(exp_year < 10)
        printf("Your salary is 20,000$\n");
        else
        printf("Your salary is 25,000$\n");
    }
}