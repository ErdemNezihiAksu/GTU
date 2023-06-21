#include <stdio.h>

int main()
{
    float x,y,z,max;
    printf("Please enter your first decimal number: ");
    scanf("%f", &x);
    printf("Please enter your second decimal number: ");
    scanf("%f", &y);

    if(y > x)
    {
        max = y;
    }
    else
    {
        max = x;
    }

    z = (x/y) + max/(x+y);
    printf("Result of the calculation is %f", z);
}