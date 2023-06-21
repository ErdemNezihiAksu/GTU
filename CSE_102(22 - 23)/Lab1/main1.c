#include <stdio.h>

int main()
{
    int n;
    printf("Please enter an integer between 1-100: ");
    scanf("%d", &n);

    if(n % 3 == 0)
    {
        printf("Fizz");
    }
    if(n > 5 && n < 50)
    {
        printf("Buzz");
    }
}