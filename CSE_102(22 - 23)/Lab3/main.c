#include <stdio.h>

void part1()
{
    printf("----Part1----\n");
    int n1,n2,n3,medium_n;
    printf("Enter 3 integers: ");
    scanf("%d %d %d",&n1,&n2,&n3);
    if(n1 >= n2)
    {
        if(n1 <= n3)
        {
            medium_n = n1;
        }
        else
        {
            if(n2 >= n3)
            {
                medium_n = n2;
            }
            else
            {
                medium_n = n3;
            }
        }
    }
    else
    {
        if(n2 <= n3)
        {
            medium_n = n2;
        }
        else
        {
            if(n1 >= n3)
            {
                medium_n = n1;
            }
            else
            {
                medium_n = n3;
            }
        }
    }
    printf("Medium number is %d\n",medium_n);
}

void part2()
{
    printf("----Part2----\n");
    int ex1,ex2,ex3;
    float avarage;
    printf("Enter your scores: ");
    scanf("%d %d %d",&ex1,&ex2,&ex3);
    printf("Your letter grades are ");
    switch (ex1/10)
    {
    case 10:
        printf("A+, ");
        break;
    case 9:
        printf("A+, ");
        break;
    case 8:
        printf("A, ");
        break;
    case 7:
        printf("B+, ");
        break;
    case 6:
        printf("B, ");
        break;
    case 5:
        printf("C, ");
        break;
    case 4:
        printf("D, ");
        break;
    default:
        printf("F, ");
        break;
    }
    switch (ex2/10)
    {
    case 10:
        printf("A+ ");
        break;
    case 9:
        printf("A+ ");
        break;
    case 8:
        printf("A ");
        break;
    case 7:
        printf("B+ ");
        break;
    case 6:
        printf("B ");
        break;
    case 5:
        printf("C ");
        break;
    case 4:
        printf("D ");
        break;
    default:
        printf("F ");
        break;
    }
    switch (ex3/10)
    {
    case 10:
        printf("And A+ ");
        break;
    case 9:
        printf("And A+ ");
        break;
    case 8:
        printf("And A ");
        break;
    case 7:
        printf("And B+ ");
        break;
    case 6:
        printf("And B ");
        break;
    case 5:
        printf("And C ");
        break;
    case 4:
        printf("And D ");
        break;
    default:
        printf("And F ");
        break;
    }
    avarage = (ex1 + ex2 + ex3)/3;
    printf("with an %.1f avarage\n",avarage);
}

void part3()
{
    printf("----Part3----\n");
    int n1,n2;
    float result,usr_result;
    char operation;
    printf("Enter arithmetic operation(+,-,*,/): ");
    scanf(" %c",&operation);
    printf("Enter 2 numbers: ");
    scanf("%d %d",&n1,&n2);
    printf("Result: ");
    scanf("%f",&usr_result);
    switch (operation)
    {
    case '+':
        result = n1 + n2;
        break;
    case '-':
        result = n1 - n2;
        break;
    case '*':
        result = n1 * n2;
        break;
    case '/':
        result = (float)n1 / (float)n2;
        break;
    default:
        printf("Invalid operation");
        break;
    }

    if(usr_result == result)
    {
        printf("Bravo, correct answer.");
    }
    else
    {
        printf("Wrong answer, try again.");
    }
}

int main()
{
    part1();
    part2();
    part3();
}