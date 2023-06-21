#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"

void find_GCD()
{
    int n1,n2,r = -1,temp;

    printf("\n-----You are about to perform GCD operation-----\n");
    printf("Please enter your first number: ");
    scanf("%d", &n1);
    printf("Please enter your second number: ");
    scanf("%d", &n2);
    if(n2 > n1)                                         //
    {                                                   //
        temp = n1;                                      //   
        n1 = n2;                                        // this part makes n1 the bigger number for Euclidean algorithm
        n2 = temp;                                      //
    }                                                   //    
    if(n1 % n2 == 0)
    {
    printf("GCD of your numbers is %d\n",n2);
    return;
    }
    while(r != 0)                                        //
    {                                                    // 
        r = n1 % n2;                                     // 
        n1 = n2;                                         //       Euclidean algorithm keeps going until the reminder is zero
        n2 = r;                                          //
    }                                                    //
    printf("GCD of your numbers is %d\n", n1);
}

int digit_count(int n)
{
    int digit = 1, temp = n;                            // this function is used for finding how many digits does the numbers have
    while(temp >= 10)					//We use this func to print every digit of the results of addition and multipication
    {
        temp /= 10;
        digit++;
    }
    return digit;
}

int* print_the_numbers_and_operation_for_add_and_mult(char operation)	//This function prints the common parts of addition and multipication	
{									//which are "first number: , second number: , result: , first number +(*) second number"
    int *numbers =(int*)malloc(sizeof(int)*2);
    int n1,n2;
    label1:
    printf("Please enter your first number: ");
    scanf("%d", &n1);
    if(n1 > 999 && operation == '*')
    {
        printf("Your number must have at most 3 digits.\n");
        goto label1;							//this part makes sure multipication operation does not take inputs with more than 4 digits.
    }
    else if(n1 > 9999 && operation == '+')
    {
        printf("Your number must have at most 4 digits.\n");
        goto label1;							//this part makes sure addition operation does not take inputs with more than 4 digits.
    }
    label2:
    printf("Please enter your second number: ");
    scanf("%d", &n2);
    if(n2 > 999 && operation == '*')
    {
        printf("Your number must have at most 3 digits.\n");
        goto label2;
    }
    else if(n2 > 9999 && operation == '+')
    {
        printf("Your number must have at most 4 digits.\n");
        goto label2;
    }
    numbers[0] = n1;
    numbers[1] = n2;
    printf("\nFirst number: %d\nSecond number: %d\nResult:\n", n1,n2);
    for(int i = 0; i<= 12-digit_count(n1);i++)
    {
    printf(" ");
    }
    printf("%d\n",n1);
    for(int i = 0; i<= 12-digit_count(n2);i++)
    {
    printf(" ");
    }
    printf("%d\n",n2);
    if(operation == '+')
    {
        printf("      +\n");
    }
    else
    {
        printf("      *\n");
    }
    printf("      -------\n");

    return numbers;
}
void Addition()
{
    int *p=(int*)malloc(sizeof(int)*2);
    int n1,n2,result;

    printf("\n-----You are about to perform Addition Operation-----\n");
   
    p = print_the_numbers_and_operation_for_add_and_mult('+');
    n1 = p[0];
    n2 = p[1];
    result = n1 + n2;
    free(p);
    
    for(int i = 0; i<= 12-digit_count(result);i++)
    {
        printf(" ");
    }
    printf("%d\n",result);
}

void Multipication()
{
    int *p=(int*)malloc(sizeof(int)*2);
    int digits[3];
    int n1,n2,result;

    printf("\n-----You are about to perform Multipication Operation-----\n");
    p = print_the_numbers_and_operation_for_add_and_mult('*');
    n1 = p[0];
    n2 = p[1];

    if(digit_count(n2) > 1)				
    {
        int reminder = n2;				//
        for(int i = digit_count(n2)-1; i >= 0; i--)	//while we are multipying, we multipy n1 with every digit of n2 so this part take every digits of n2 in an array.
        {
            digits[i] = reminder / (int)pow(10,i);
            reminder = reminder % (int)pow(10,i);
        }
							//
        int space_count = 12;
        for(int i = 0 ; i < digit_count(n2); i++)				//
        {
            result = n1 * digits[i];
            for(int i = 0; i<= space_count - digit_count(result);i++)		// this parts moves one digit left for each digits of n2 during multipication.
            {
                printf(" ");
            }
            printf("%d\n",result);
            space_count--;
        }									//
        printf("      +\n");
        printf("      -------\n");
    }
    result = n1 * n2;
    for(int i = 0; i<= 12-digit_count(result);i++)
    {
        printf(" ");
    }
    printf("%d\n",result);
    free(p);
}

void greater_or_less()
{
    int n;
    printf("Please enter an number between 1-10: ");
    scanf("%d",&n);

    if(n > 10 || n < 1)
    {
        printf("Invalid input\n");
    }
    else if(n > 5 && n <= 10)
    {
        printf("The integer you entered is greater than 5\n");
    }
    else
    {
        printf("The integer you entered is less than or equal to 5\n");
    }
}    
